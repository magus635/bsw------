	.section ".sdk_text_asil_d","ax"

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
	.align	2
DsadcDemo_MainConvResult::	.space	20
	.endo	DsadcDemo_MainConvResult
	.section ".sdk_text_asil_d","ax"
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68256D..0::
	.section ".mcal_text_asil_d","ax"
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68256D..1::
..gh.f.a.1.e.0:
	.endo	..gh.f.a.1.e.0
	.global	Dsadc_Result2VoltageDiff..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
Dsadc_Result2VoltageDiff..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.:
Dsadc_Result2VoltageDiff:
.LDW01:
.LDW11:
	vmov	s1,r0
	vmov.f32	s2,#5.000000000000000000e-1
	vcvt.f32.s32	s1,s1
	vadd.f32	s1,s1,s2
	vldr	s3,.L73
	vdiv.f32	s0,s1,s3
.LDW21:
.L74:

	ret	
__ghs_eofn_Dsadc_Result2VoltageDiff:
	.endf	Dsadc_Result2VoltageDiff
	.endf	Dsadc_Result2VoltageDiff..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
;Volt	s1	local

;ResultVal	r0	param

	.section ".bss","awb"
.L55:
	.endo	.L55
	.section ".ghrettbl",""
	.align	4
.L75:	.data.w	.L74
	.endo	.L75
	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.1:
	.endo	..gh.f.a.1.e.1
	.global	Dsadc_Result2VoltageSingle..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
Dsadc_Result2VoltageSingle..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.:
Dsadc_Result2VoltageSingle:
.LDW31:
.LDW41:
	vmov	s1,r0
	vcvt.f32.s32	s1,s1
	vldr	s2,.L121
	vadd.f32	s1,s1,s2
	vldr	s3,.L122
	vdiv.f32	s0,s1,s3
.LDW51:
.L123:

	ret	
__ghs_eofn_Dsadc_Result2VoltageSingle:
	.endf	Dsadc_Result2VoltageSingle
	.endf	Dsadc_Result2VoltageSingle..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
;Volt	s1	local

;ResultVal	r0	param

	.section ".bss","awb"
.L103:
	.endo	.L103
	.section ".ghrettbl",""
.L124:	.data.w	.L123
	.endo	.L124
	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (DsadcDemo_MainConvResult - DsadcDemo_MainConvResult) +0 == 0
..gh.f.a.1.e.2:
	.endo	..gh.f.a.1.e.2
	.global	Dsadc_SingleAccessConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
Dsadc_SingleAccessConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.:
Dsadc_SingleAccessConversionDemo:
.LDW61:
	.need	__gh_float_printf
	push	{r4-r8,lr}
	ldr	r5,.L913
.LDW71:
	ldr	r0,.L914
.L922:

	bl	Pwm_Init
	mov	r0,20
.L924:

	bl	Timer_DelayMs
	movw	r0,0x01b7
.L926:

	bl	Intc_EnableInterrupt
	mov	r0,0x01b8
.L928:

	bl	Intc_EnableInterrupt
	mov	r1,r5
	mov	r0,0
.L930:

	bl	Dsadc_SetupResultBuffer
	cmp	r0,0
	bne	.L140
.L932:

	bl	Dsadc_StartConversion
	mov	r4,0
	strh	r4,[r5]
	mov	r0,100
	strh	r4,[r5,2]
.L934:

	bl	Timer_DelayMs
	ldr	r1,.L915
	mov	r0,r4
.L936:

	bl	TmcPrintf
.L131:
	mov	r1,0
	mov	r0,r1
.L938:

	bl	Dsadc_GetChannelStatus
	mov	r6,r0
	mov	r1,1
	mov	r0,0
.L940:

	bl	Dsadc_GetChannelStatus
	cmp	r6,3
	cmpeq	r0,3
	bne	.L132
	ldrsh	r7,[r5]
	mov	r0,0
	ldrsh	r8,[r5,2]
.L942:

	bl	Dsadc_GetTimestamp
	subs	r6,r0,0
	bne	.L141
.L132:
	add	r4,r4,1
	cmp	r4,0x03e8
	blo	.L131
.L140:
	ldr	r1,.L916
	b	.L142
.L141:
	ldr	r1,.L917
	mov	r2,r7
	mov	r0,0
.L944:

	bl	TmcPrintf
	mov	r0,r7
.L946:

	bl	Dsadc_Result2VoltageDiff
	vcvt.f64.f32	d0,s0
	ldr	r1,.L918
	mov	r0,0
	vmov	r2,r3,d0
.L948:

	bl	TmcPrintf
	ldr	r1,.L919
	mov	r2,r6
	mov	r0,0
.L950:

	bl	TmcPrintf
	ldr	r1,.L920
	mov	r2,r8
	mov	r0,0
.L952:

	bl	TmcPrintf
	ldr	r1,.L921
.L142:
	mov	r0,0
.L954:

	bl	TmcPrintf
	mov	r1,0
	mov	r0,r1
.L956:

	bl	Dsadc_GetChannelStatus
	mov	r6,r0
	mov	r1,1
	mov	r0,0
.L958:

	bl	Dsadc_GetChannelStatus
	cmp	r6,0
	cmpeq	r0,0
	movne	r0,0
.L960:

	blne	Dsadc_StopConversion
	movw	r0,0x01b7
.L962:

	bl	Intc_DisableInterrupt
	mov	r0,0x01b8
.L964:

	bl	Intc_DisableInterrupt
	pop	{r4-r8,lr}
.L966:

	b	Pwm_DeInit
.LDW81:
__ghs_eofn_Dsadc_SingleAccessConversionDemo:
	.endf	Dsadc_SingleAccessConversionDemo
	.endf	Dsadc_SingleAccessConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
;MainChStatus	r6	local
;AuxChStatus	r0	local
;TimestampValue	r6	local
;WaitLoop	r4	local

	.section ".rodata","a"
.L792:;	"\nDelay100ms\n"
	.data.b	10,68,101,108
	.data.b	97,121,49,48
	.data.b	48,109,115,10
	.data.b	0
	.endo	.L792
.L793:;	"\nTest Result = FAIL"
	.data.b	10,84,101,115
	.data.b	116,32,82,101
	.data.b	115,117,108,116
	.data.b	32,61,32,70
	.data.b	65,73,76,0
	.endo	.L793
.L794:;	"\n\nTest Result = PASS"
	.data.b	10,10,84,101
	.data.b	115,116,32,82
	.data.b	101,115,117,108
	.data.b	116,32,61,32
	.data.b	80,65,83,83
	.data.b	0
	.endo	.L794
.L795:;	"\nTimestamp value is: %d"
	.data.b	10,84,105,109
	.data.b	101,115,116,97
	.data.b	109,112,32,118
	.data.b	97,108,117,101
	.data.b	32,105,115,58
	.data.b	32,37,100,0
	.endo	.L795
.L796:;	"\nConvert to voltage is %fV"
	.data.b	10,67,111,110
	.data.b	118,101,114,116
	.data.b	32,116,111,32
	.data.b	118,111,108,116
	.data.b	97,103,101,32
	.data.b	105,115,32,37
	.data.b	102,86
	.data.b	0
	.endo	.L796
.L797:;	"\nMain conversion channel result: %d"
	.data.b	10,77,97,105
	.data.b	110,32,99,111
	.data.b	110,118,101,114
	.data.b	115,105,111,110
	.data.b	32,99,104,97
	.data.b	110,110,101,108
	.data.b	32,114,101,115
	.data.b	117,108,116,58
	.data.b	32,37,100,0
	.endo	.L797
.L798:;	"\nAuxiliary conversion channel result: %d"
	.data.b	10,65,117,120
	.data.b	105,108,105,97
	.data.b	114,121,32,99
	.data.b	111,110,118,101
	.data.b	114,115,105,111
	.data.b	110,32,99,104
	.data.b	97,110,110,101
	.data.b	108,32,114,101
	.data.b	115,117,108,116
	.data.b	58,32,37,100
	.data.b	0
	.endo	.L798
	.section ".ghcalltbl",""
	.align	4
.L923:	.data.w	.L922
	.endo	.L923
.L925:	.data.w	.L924
	.endo	.L925
.L927:	.data.w	.L926
	.endo	.L927
.L929:	.data.w	.L928
	.endo	.L929
.L931:	.data.w	.L930
	.endo	.L931
.L933:	.data.w	.L932
	.endo	.L933
.L935:	.data.w	.L934
	.endo	.L935
.L937:	.data.w	.L936
	.endo	.L937
.L939:	.data.w	.L938
	.endo	.L939
.L941:	.data.w	.L940
	.endo	.L941
.L943:	.data.w	.L942
	.endo	.L943
.L945:	.data.w	.L944
	.endo	.L945
.L947:	.data.w	.L946
	.endo	.L947
.L949:	.data.w	.L948
	.endo	.L949
.L951:	.data.w	.L950
	.endo	.L951
.L953:	.data.w	.L952
	.endo	.L953
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
	.section ".ghtailcalltbl",""
	.align	4
.L967:	.data.w	.L966
	.endo	.L967
	.data
	.global	__caller.Pwm_DeInit.v.v

	.global	__caller.Intc_DisableInterrupt.v.i

	.global	__caller.Intc_DisableInterrupt.v.i

	.global	__caller.Dsadc_StopConversion.i.i

	.global	__caller.Dsadc_GetChannelStatus.i.ii

	.global	__caller.Dsadc_GetChannelStatus.i.ii

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Dsadc_GetTimestamp.i.i

	.global	__caller.Dsadc_GetChannelStatus.i.ii

	.global	__caller.Dsadc_GetChannelStatus.i.ii

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.Dsadc_StartConversion.i.i

	.global	__caller.Dsadc_SetupResultBuffer.i.ip

	.global	__caller.Intc_EnableInterrupt.v.i

	.global	__caller.Intc_EnableInterrupt.v.i

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.Pwm_Init.v.p

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (DsadcDemo_MainConvResult - DsadcDemo_MainConvResult) +0 == 0
..gh.f.a.1.e.3:
	.endo	..gh.f.a.1.e.3
	.global	Dsadc_StreamingWithLinearBufferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
Dsadc_StreamingWithLinearBufferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.:
Dsadc_StreamingWithLinearBufferDemo:
.LDW91:
	.need	__gh_float_printf
	push	{r4-r6,lr}
	sub	sp,sp,16
.LDW02:
	movw	r0,0x01b9
.L1894:

	bl	Intc_EnableInterrupt
	movw	r0,0x01ba
.L1896:

	bl	Intc_EnableInterrupt
	mov	r0,0
.L973:
	ldr	r4,.L913
	lsl	r1,r0,1
	add	r0,r0,1
	mov	r2,0
	cmp	r0,5
	strh	r2,[r1,r4]
	blo	.L973
	mov	r1,r4
	mov	r0,1
.L1898:

	bl	Dsadc_SetupResultBuffer
	cmp	r0,0
	bne	.L984
	mov	r0,100
.L1900:

	bl	Timer_DelayMs
	ldr	r1,.L915
	mov	r0,0
.L1902:

	bl	TmcPrintf
	mov	r0,1
.L1904:

	bl	Dsadc_StartConversion
	mov	r5,0
.L978:
	mov	r0,1
.L1906:

	bl	Timer_DelayMs
	add	r1,sp,12
	mov	r0,1
.L1908:

	bl	Dsadc_GetStreamLastPointer
	cmp	r0,5
	bne	.L979
	ldr	r2,[sp,12]
	ldr	r1,.L1889
	mov	r0,0
	ldrsh	r2,[r2]
.L1910:

	bl	TmcPrintf
	ldr	r0,[sp,12]
	ldrsh	r0,[r0]
.L1912:

	bl	Dsadc_Result2VoltageSingle
	vcvt.f64.f32	d0,s0
	ldr	r1,.L1890
	mov	r0,0
	vmov	r2,r3,d0
.L1914:

	bl	TmcPrintf
	ldr	r1,.L1891
	mov	r0,0
.L1916:

	bl	TmcPrintf
	mov	r5,0
.L989:
	lsl	r0,r5,1
	ldrsh	r6,[r0,r4]
	mov	r0,r6
.L1918:

	bl	Dsadc_Result2VoltageSingle
	vcvt.f64.f32	d0,s0
	ldr	r1,.L1892
	mov	r2,r6
	mov	r0,0
	vstr	d0,[sp,0]
.L1920:

	bl	TmcPrintf
	add	r5,r5,1
	cmp	r5,5
	blo	.L989
	ldr	r1,.L1893
	b	.L990
.L979:
	add	r5,r5,1
	cmp	r5,0x03e8
	blo	.L978
.L984:
	ldr	r1,.L916
.L990:
	mov	r0,0
.L1922:

	bl	TmcPrintf
	mov	r1,0
	mov	r0,1
.L1924:

	bl	Dsadc_GetChannelStatus
	cmp	r0,0
	movne	r0,1
.L1926:

	blne	Dsadc_StopConversion
	movw	r0,0x01b9
.L1928:

	bl	Intc_DisableInterrupt
	movw	r0,0x01ba
.L1930:

	bl	Intc_DisableInterrupt
.LDW12:
	add	sp,sp,16
.L1932:

	pop	{r4-r6,pc}
__ghs_eofn_Dsadc_StreamingWithLinearBufferDemo:
	.endf	Dsadc_StreamingWithLinearBufferDemo
	.endf	Dsadc_StreamingWithLinearBufferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
;ResultPtr	[sp,12]	local
;WaitLoop	r5	local

	.section ".rodata","a"
.L1748:;	"%d->%.2fV  "
	.data.b	37,100,45,62
	.data.b	37,46,50,102
	.data.b	86,32,32,0
	.endo	.L1748
.L1749:;	"\nTest Result = PASS"
	.data.b	10,84,101,115
	.data.b	116,32,82,101
	.data.b	115,117,108,116
	.data.b	32,61,32,80
	.data.b	65,83,83,0
	.endo	.L1749
.L1750:;	"\nConvert to voltage is %.2fV"
	.data.b	10,67,111,110
	.data.b	118,101,114,116
	.data.b	32,116,111,32
	.data.b	118,111,108,116
	.data.b	97,103,101,32
	.data.b	105,115,32,37
	.data.b	46,50,102,86
	.data.b	0
	.endo	.L1750
.L1751:;	"\nLatest conversion result is: %d"
	.data.b	10,76,97,116
	.data.b	101,115,116,32
	.data.b	99,111,110,118
	.data.b	101,114,115,105
	.data.b	111,110,32,114
	.data.b	101,115,117,108
	.data.b	116,32,105,115
	.data.b	58,32,37,100
	.data.b	0
	.endo	.L1751
.L1752:;	"\nAll conversion results of main conversion channel: \n"
	.data.b	10,65,108,108
	.data.b	32,99,111,110
	.data.b	118,101,114,115
	.data.b	105,111,110,32
	.data.b	114,101,115,117
	.data.b	108,116,115,32
	.data.b	111,102,32,109
	.data.b	97,105,110,32
	.data.b	99,111,110,118
	.data.b	101,114,115,105
	.data.b	111,110,32,99
	.data.b	104,97,110,110
	.data.b	101,108,58,32
	.data.b	10,0
	.endo	.L1752
	.section ".ghcalltbl",""
.L1895:	.data.w	.L1894
	.endo	.L1895
.L1897:	.data.w	.L1896
	.endo	.L1897
.L1899:	.data.w	.L1898
	.endo	.L1899
.L1901:	.data.w	.L1900
	.endo	.L1901
.L1903:	.data.w	.L1902
	.endo	.L1903
.L1905:	.data.w	.L1904
	.endo	.L1905
.L1907:	.data.w	.L1906
	.endo	.L1907
.L1909:	.data.w	.L1908
	.endo	.L1909
.L1911:	.data.w	.L1910
	.endo	.L1911
.L1913:	.data.w	.L1912
	.endo	.L1913
.L1915:	.data.w	.L1914
	.endo	.L1915
.L1917:	.data.w	.L1916
	.endo	.L1917
.L1919:	.data.w	.L1918
	.endo	.L1919
.L1921:	.data.w	.L1920
	.endo	.L1921
.L1923:	.data.w	.L1922
	.endo	.L1923
.L1925:	.data.w	.L1924
	.endo	.L1925
.L1927:	.data.w	.L1926
	.endo	.L1927
.L1929:	.data.w	.L1928
	.endo	.L1929
.L1931:	.data.w	.L1930
	.endo	.L1931
	.section ".ghrettbl",""
.L1933:	.data.w	.L1932
	.endo	.L1933
	.data
	.global	__caller.Intc_DisableInterrupt.v.i

	.global	__caller.Intc_DisableInterrupt.v.i

	.global	__caller.Dsadc_StopConversion.i.i

	.global	__caller.Dsadc_GetChannelStatus.i.ii

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Dsadc_GetStreamLastPointer.i.ip

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.Dsadc_StartConversion.i.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.Dsadc_SetupResultBuffer.i.ip

	.global	__caller.Intc_EnableInterrupt.v.i

	.global	__caller.Intc_EnableInterrupt.v.i

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (Dsadc_DemoCircularBufferFullFlag - Dsadc_DemoCircularBufferFullFlag) +0 == 0
..gh.f.a.1.e.4:
	.endo	..gh.f.a.1.e.4
	.global	Dsadc_StreamingWithCircularBufferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
Dsadc_StreamingWithCircularBufferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.:
Dsadc_StreamingWithCircularBufferDemo:
.LDW22:
	push	{r4-r6,lr}
.LDW32:
	movw	r0,0x01bb
.L2751:

	bl	Intc_EnableInterrupt
	mov	r0,0x01bc
.L2753:

	bl	Intc_EnableInterrupt
	mov	r0,0
.L1939:
	ldr	r4,.L913
	lsl	r1,r0,1
	add	r0,r0,1
	mov	r2,0
	cmp	r0,2
	strh	r2,[r1,r4]
	blo	.L1939
	ldr	r5,.L2749
	mov	r1,r4
	mov	r0,2
	strb	r2,[r5]
.L2755:

	bl	Dsadc_SetupResultBuffer
	cmp	r0,0
	bne	.L1950
	mov	r0,2
.L2757:

	bl	Dsadc_EnableNotification
	mov	r0,100
.L2759:

	bl	Timer_DelayMs
	ldr	r1,.L915
	mov	r0,0
.L2761:

	bl	TmcPrintf
	mov	r0,2
.L2763:

	bl	Dsadc_StartConversion
	mov	r6,0
.L1944:
	mov	r0,1
.L2765:

	bl	Timer_DelayMs
	ldrb	r0,[r5]
	cmp	r0,1
	beq	.L1951
	add	r6,r6,1
	cmp	r6,0x03e8
	blo	.L1944
.L1950:
	ldr	r1,.L916
	b	.L1956

.L73:	.data.w	0x454ccb33
	.endo	.L73

.L121:	.data.w	0x46800000
	.endo	.L121

.L122:	.data.w	0x45cccb33
	.endo	.L122

.L913:	.data.w	DsadcDemo_MainConvResult
	.endo	.L913

.L914:	.data.w	Pwm_ConfigSet
	.endo	.L914

.L915:	.data.w	.L792
	.endo	.L915

.L916:	.data.w	.L793
	.endo	.L916

.L917:	.data.w	.L797
	.endo	.L917

.L918:	.data.w	.L796
	.endo	.L918

.L919:	.data.w	.L795
	.endo	.L919

.L920:	.data.w	.L798
	.endo	.L920

.L921:	.data.w	.L794
	.endo	.L921

.L1889:	.data.w	.L1751
	.endo	.L1889

.L1890:	.data.w	.L1750
	.endo	.L1890

.L1891:	.data.w	.L1752
	.endo	.L1891

.L1892:	.data.w	.L1748
	.endo	.L1892

.L1893:	.data.w	.L1749
	.endo	.L1893

.L2749:	.data.w	Dsadc_DemoCircularBufferFullFlag
	.endo	.L2749

.L2750:	.data.w	.L2634
	.endo	.L2750

.L1951:
;line475
..lin.d9d0e74b..28f4a7fd.1_1::
.LDWlin1:
	ldr	r1,.L1891
	mov	r0,0
.L2767:

	bl	TmcPrintf
	mov	r5,0
.L1955:
	lsl	r0,r5,1
	ldr	r1,.L2750
	ldrsh	r2,[r0,r4]
	mov	r0,0
.L2769:

	bl	TmcPrintf
	add	r5,r5,1
	cmp	r5,10
	blo	.L1955
	ldr	r1,.L921
.L1956:
	mov	r0,0
.L2771:

	bl	TmcPrintf
	mov	r0,2
.L2773:

	bl	Dsadc_DisableNotification
	movw	r0,0x01bb
.L2775:

	bl	Intc_DisableInterrupt
	mov	r0,0x01bc
	pop	{r4-r6,lr}
.L2777:

	b	Intc_DisableInterrupt
.LDW42:
__ghs_eofn_Dsadc_StreamingWithCircularBufferDemo:
	.endf	Dsadc_StreamingWithCircularBufferDemo
	.endf	Dsadc_StreamingWithCircularBufferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
;WaitLoop	r6	local

	.section ".mcal_bss_asil_d_unspecified_core0","awb"
Dsadc_DemoCircularBufferFullFlag..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.::
Dsadc_DemoCircularBufferFullFlag:	.space	1
	.endo	Dsadc_DemoCircularBufferFullFlag..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.endo	Dsadc_DemoCircularBufferFullFlag
	.section ".rodata","a"
.L2634:;	"%d  "
	.data.b	37,100,32,32
	.data.b	0
	.endo	.L2634
	.section ".ghcalltbl",""
.L2752:	.data.w	.L2751
	.endo	.L2752
.L2754:	.data.w	.L2753
	.endo	.L2754
.L2756:	.data.w	.L2755
	.endo	.L2756
.L2758:	.data.w	.L2757
	.endo	.L2758
.L2760:	.data.w	.L2759
	.endo	.L2760
.L2762:	.data.w	.L2761
	.endo	.L2762
.L2764:	.data.w	.L2763
	.endo	.L2764
.L2766:	.data.w	.L2765
	.endo	.L2766
.L2768:	.data.w	.L2767
	.endo	.L2768
.L2770:	.data.w	.L2769
	.endo	.L2770
.L2772:	.data.w	.L2771
	.endo	.L2772
.L2774:	.data.w	.L2773
	.endo	.L2774
.L2776:	.data.w	.L2775
	.endo	.L2776
	.section ".ghtailcalltbl",""
.L2778:	.data.w	.L2777
	.endo	.L2778
	.data
	.global	__caller.Intc_DisableInterrupt.v.i

	.global	__caller.Intc_DisableInterrupt.v.i

	.global	__caller.Dsadc_DisableNotification.v.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.Dsadc_StartConversion.i.i

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.Dsadc_EnableNotification.v.i

	.global	__caller.Dsadc_SetupResultBuffer.i.ip

	.global	__caller.Intc_EnableInterrupt.v.i

	.global	__caller.Intc_EnableInterrupt.v.i

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (DsadcDemo_MainConvResult - DsadcDemo_MainConvResult) +0 == 0
..gh.f.a.1.e.5:
	.endo	..gh.f.a.1.e.5
	.global	Dsadc_SingleAccessConversionWithDmaDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
Dsadc_SingleAccessConversionWithDmaDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.:
Dsadc_SingleAccessConversionWithDmaDemo:
.LDW52:
	push	{r4-r6,lr}
.LDW62:
	ldr	r0,.L3123
.L3125:

	bl	Dma_Init
	mov	r0,17
.L3127:

	bl	Dma_ChannelStart
	mov	r0,3
.L3129:

	bl	Dsadc_StartConversion
	mov	r0,0
.L2784:
	ldr	r4,.L913
	lsl	r1,r0,1
	add	r0,r0,1
	mvn	r2,0
	cmp	r0,10
	strh	r2,[r1,r4]
	blo	.L2784
	mov	r5,0
.L2787:
	mov	r0,1
.L3131:

	bl	Timer_DelayMs
	ldrsh	r0,[r4,18]
	cmn	r0,1
	bne	.L2794
	add	r5,r5,1
	cmp	r5,0x03e8
	blo	.L2787
	b	.L2793
.L2794:
	ldr	r1,.L3124
	mov	r0,0
.L3133:

	bl	TmcPrintf
	mov	r5,0
.L2798:
	lsl	r0,r5,1
	ldr	r1,.L2750
	ldrsh	r2,[r0,r4]
	mov	r0,0
.L3135:

	bl	TmcPrintf
	add	r5,r5,1
	cmp	r5,10
	blo	.L2798
	ldr	r1,.L921
	b	.L2799
.L2793:
	ldr	r1,.L916
.L2799:
	mov	r0,0
.L3137:

	bl	TmcPrintf
	mov	r1,0
	mov	r0,3
.L3139:

	bl	Dsadc_GetChannelStatus
	cmp	r0,0
	movne	r0,3
.L3141:

	blne	Dsadc_StopConversion
	mov	r1,0
	mov	r0,17
.L3143:

	bl	Dma_ChannelCancel
	pop	{r4-r6,lr}
.L3145:

	b	Dma_DeInit
.LDW72:
__ghs_eofn_Dsadc_SingleAccessConversionWithDmaDemo:
	.endf	Dsadc_SingleAccessConversionWithDmaDemo
	.endf	Dsadc_SingleAccessConversionWithDmaDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
;WaitLoop	r5	local

	.section ".rodata","a"
.L3012:;	"\nMain conversion channel result: \n"
	.data.b	10,77,97,105
	.data.b	110,32,99,111
	.data.b	110,118,101,114
	.data.b	115,105,111,110
	.data.b	32,99,104,97
	.data.b	110,110,101,108
	.data.b	32,114,101,115
	.data.b	117,108,116,58
	.data.b	32,10
	.data.b	0
	.endo	.L3012
	.section ".ghcalltbl",""
.L3126:	.data.w	.L3125
	.endo	.L3126
.L3128:	.data.w	.L3127
	.endo	.L3128
.L3130:	.data.w	.L3129
	.endo	.L3130
.L3132:	.data.w	.L3131
	.endo	.L3132
.L3134:	.data.w	.L3133
	.endo	.L3134
.L3136:	.data.w	.L3135
	.endo	.L3136
.L3138:	.data.w	.L3137
	.endo	.L3138
.L3140:	.data.w	.L3139
	.endo	.L3140
.L3142:	.data.w	.L3141
	.endo	.L3142
.L3144:	.data.w	.L3143
	.endo	.L3144
	.section ".ghtailcalltbl",""
.L3146:	.data.w	.L3145
	.endo	.L3146
	.data
	.global	__caller.Dma_DeInit.v.v

	.global	__caller.Dma_ChannelCancel.v.ii

	.global	__caller.Dsadc_StopConversion.i.i

	.global	__caller.Dsadc_GetChannelStatus.i.ii

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Timer_DelayMs.v.i

	.global	__caller.Dsadc_StartConversion.i.i

	.global	__caller.Dma_ChannelStart.v.i

	.global	__caller.Dma_Init.v.p

	.section ".mcal_text_asil_d","ax"
	.assert 0x0 + (DsadcDemo_MasterCoreInitFlag - DsadcDemo_MasterCoreInitFlag) +0 == 0
..gh.f.a.1.e.6:
	.endo	..gh.f.a.1.e.6
__callee.Dsadc_DemoEntry.v.v::
	.size	__callee.Dsadc_DemoEntry.v.v,0
Dsadc_DemoEntry::
.LDW82:
	push	{r4-r7,lr}
	sub	sp,sp,20
	ldr	r5,.L3571
.LDW92:
	ldr	r0,.L3572
.L3585:

	bl	Dsadc_Init
	mov	r0,1
	ldr	r4,.L3573
	strb	r0,[r5]
	mov	r6,0
	str	r0,[r4,8]
.L3151:
	add	r0,sp,8
.L3587:

	bl	Dsadc_GetVersionInfo
	ldr	r1,.L3574
	mov	r0,r6
.L3589:

	bl	TmcPrintf
	ldr	r1,.L3575
	mov	r0,r6
.L3591:

	bl	TmcPrintf
	ldrb	r0,[sp,14]
	str	r0,[sp]
	ldr	r1,.L3576
	ldrb	r2,[sp,12]
	mov	r0,r6
	ldrb	r3,[sp,13]
.L3593:

	bl	TmcPrintf
	ldr	r1,.L3577
	mov	r0,r6
.L3595:

	bl	TmcPrintf
	ldr	r1,.L3578
	mov	r0,r6
.L3597:

	bl	TmcPrintf
	ldr	r1,.L3579
	mov	r0,r6
.L3599:

	bl	TmcPrintf
	ldr	r1,.L3580
	mov	r0,r6
.L3601:

	bl	TmcPrintf
	ldr	r1,.L3581
	mov	r0,r6
.L3603:

	bl	TmcPrintf
	ldr	r1,.L3582
	mov	r0,r6
.L3605:

	bl	TmcPrintf
	ldr	r1,.L3583
	mov	r0,r6
.L3607:

	bl	TmcPrintf
.L3609:

	bl	getChar
	sub	r1,r0,48
	cmp	r1,10
	strlo	r6,[r4]
	strblo	r1,[r4,4]
	blo	.L3159
	sub	r1,r0,97
	cmp	r1,23
	strlo	r6,[r4]
	addlo	r0,r1,10
	strblo	r0,[r4,4]
	blo	.L3159
	sub	r1,r0,65
	cmp	r1,23
	strlo	r6,[r4]
	addlo	r0,r1,10
	strblo	r0,[r4,4]
	blo	.L3159
	cmp	r0,120
	cmpne	r0,88
	bne	.L3168
	mov	r7,0
	mvn	r0,0
	str	r7,[r4]
	strb	r0,[r4,4]
	mov	r6,1
	mov	r0,200
	str	r7,[r4,8]
.L3611:

	bl	Timer_DelayMs
.L3613:

	bl	Dsadc_DeInit
	strb	r7,[r5]
	b	.L3159
.L3168:
	ldr	r1,.L3584
	mov	r0,r6
.L3615:

	bl	TmcPrintf
.L3159:
	ldrb	r0,[r4,4]
	cmp	r0,255
	beq	.L3149
	ldr	r0,[r4]
	cmp	r0,0
.L3617:

	bleq	Dsadc_Demo
.L3176:
	ldrb	r0,[r4,4]
	cmp	r0,255
	bne	.L3176
.L3149:
	cmp	r6,0
	beq	.L3151
.LDW03:
	add	sp,sp,20
.L3619:

	pop	{r4-r7,pc}
__ghs_eofn_Dsadc_DemoEntry::
	.endf	Dsadc_DemoEntry
;Cmd	r0	local
;ExitFlag	r6	local
;Dsadc_ver	[sp,8]	local

	.section ".mcal_bss_asil_d_unspecified_uncached","awb"
DsadcDemo_MasterCoreInitFlag..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.::
DsadcDemo_MasterCoreInitFlag:	.space	1
	.endo	DsadcDemo_MasterCoreInitFlag..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.endo	DsadcDemo_MasterCoreInitFlag
	.section ".rodata","a"
.L3418:;	"\n\n\n"
	.data.b	10,10,10,0
	.endo	.L3418
	.section ".mcal_data_asil_d_unspecified_uncached","aw"
	.align	4
Dsadc_DemoCoreExeFlag..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.::
Dsadc_DemoCoreExeFlag:	.space	4
	.data.b	255,0,0,0
	.space	4
	.endo	Dsadc_DemoCoreExeFlag..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.endo	Dsadc_DemoCoreExeFlag
	.section ".rodata","a"
.L3419:;	"\n\n  INVALID OPTION\n"
	.data.b	10,10,32,32
	.data.b	73,78,86,65
	.data.b	76,73,68,32
	.data.b	79,80,84,73
	.data.b	79,78,10,0
	.endo	.L3419
.L3420:;	"\n  ENTER YOUR OPTION   : "
	.data.b	10,32,32,69
	.data.b	78,84,69,82
	.data.b	32,89,79,85
	.data.b	82,32,79,80
	.data.b	84,73,79,78
	.data.b	32,32,32,58
	.data.b	32,0
	.endo	.L3420
.L3421:;	"\n  <x> : Go back to Main Menu. \n"
	.data.b	10,32,32,60
	.data.b	120,62,32,58
	.data.b	32,71,111,32
	.data.b	98,97,99,107
	.data.b	32,116,111,32
	.data.b	77,97,105,110
	.data.b	32,77,101,110
	.data.b	117,46,32,10
	.data.b	0
	.endo	.L3421
.L3422:;	"\n                                                         "
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
	.endo	.L3422
.L3423:;	"\n/*********************************************************/"
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
	.endo	.L3423
.L3424:;	"\n           DSADC DRIVER DEMO MENU V%02d.%02d.%02d            "
	.data.b	10,32,32,32
	.data.b	32,32,32,32
	.data.b	32,32,32,32
	.data.b	68,83,65,68
	.data.b	67,32,68,82
	.data.b	73,86,69,82
	.data.b	32,68,69,77
	.data.b	79,32,77,69
	.data.b	78,85,32,86
	.data.b	37,48,50,100
	.data.b	46,37,48,50
	.data.b	100,46,37,48
	.data.b	50,100,32,32
	.data.b	32,32,32,32
	.data.b	32,32,32,32
	.data.b	32,32
	.data.b	0
	.endo	.L3424
.L3425:;	"\n  <1> : (DSADC0)Start to conversion: single access mode, GTM trigger..."
	.data.b	10,32,32,60
	.data.b	49,62,32,58
	.data.b	32,40,68,83
	.data.b	65,68,67,48
	.data.b	41,83,116,97
	.data.b	114,116,32,116
	.data.b	111,32,99,111
	.data.b	110,118,101,114
	.data.b	115,105,111,110
	.data.b	58,32,115,105
	.data.b	110,103,108,101
	.data.b	32,97,99,99
	.data.b	101,115,115,32
	.data.b	109,111,100,101
	.data.b	44,32,71,84
	.data.b	77,32,116,114
	.data.b	105,103,103,101
	.data.b	114,48,40,80
	.data.b	87,77,41,32
	.data.b	116,114,105,103
	.data.b	103,101,114,46
	.data.b	0
	.endo	.L3425
.L3426:;	"\n  <2> : (DSADC1)Start to conversion: streaming access mode, linear b..."
	.data.b	10,32,32,60
	.data.b	50,62,32,58
	.data.b	32,40,68,83
	.data.b	65,68,67,49
	.data.b	41,83,116,97
	.data.b	114,116,32,116
	.data.b	111,32,99,111
	.data.b	110,118,101,114
	.data.b	115,105,111,110
	.data.b	58,32,115,116
	.data.b	114,101,97,109
	.data.b	105,110,103,32
	.data.b	97,99,99,101
	.data.b	115,115,32,109
	.data.b	111,100,101,44
	.data.b	32,108,105,110
	.data.b	101,97,114,32
	.data.b	98,117,102,102
	.data.b	101,114,44,32
	.data.b	83,111,102,116
	.data.b	119,97,114,101
	.data.b	32,116,114,105
	.data.b	103,103,101,114
	.data.b	46,0
	.endo	.L3426
.L3427:;	"\n  <3> : (DSADC2)Start to conversion: streaming access mode, circular..."
	.data.b	10,32,32,60
	.data.b	51,62,32,58
	.data.b	32,40,68,83
	.data.b	65,68,67,50
	.data.b	41,83,116,97
	.data.b	114,116,32,116
	.data.b	111,32,99,111
	.data.b	110,118,101,114
	.data.b	115,105,111,110
	.data.b	58,32,115,116
	.data.b	114,101,97,109
	.data.b	105,110,103,32
	.data.b	97,99,99,101
	.data.b	115,115,32,109
	.data.b	111,100,101,44
	.data.b	32,99,105,114
	.data.b	99,117,108,97
	.data.b	114,32,98,117
	.data.b	102,102,101,114
	.data.b	44,32,83,111
	.data.b	102,116,119,97
	.data.b	114,101,32,116
	.data.b	114,105,103,103
	.data.b	101,114,46,32
	.data.b	0
	.endo	.L3427
.L3428:;	"\n  <4> : (DSADC3)Start to conversion: streaming access mode, linear b..."
	.data.b	10,32,32,60
	.data.b	52,62,32,58
	.data.b	32,40,68,83
	.data.b	65,68,67,51
	.data.b	41,83,116,97
	.data.b	114,116,32,116
	.data.b	111,32,99,111
	.data.b	110,118,101,114
	.data.b	115,105,111,110
	.data.b	58,32,115,116
	.data.b	114,101,97,109
	.data.b	105,110,103,32
	.data.b	97,99,99,101
	.data.b	115,115,32,109
	.data.b	111,100,101,44
	.data.b	32,108,105,110
	.data.b	101,97,114,32
	.data.b	98,117,102,102
	.data.b	101,114,44,32
	.data.b	68,77,65,32
	.data.b	114,101,115,117
	.data.b	108,116,32,104
	.data.b	97,110,100,108
	.data.b	105,110,103,44
	.data.b	32,72,97,114
	.data.b	100,119,97,114
	.data.b	101,32,116,114
	.data.b	105,103,103,101
	.data.b	114,46
	.data.b	0
	.endo	.L3428
	.section ".ghcalltbl",""
.L3586:	.data.w	.L3585
	.endo	.L3586
.L3588:	.data.w	.L3587
	.endo	.L3588
.L3590:	.data.w	.L3589
	.endo	.L3590
.L3592:	.data.w	.L3591
	.endo	.L3592
.L3594:	.data.w	.L3593
	.endo	.L3594
.L3596:	.data.w	.L3595
	.endo	.L3596
.L3598:	.data.w	.L3597
	.endo	.L3598
.L3600:	.data.w	.L3599
	.endo	.L3600
.L3602:	.data.w	.L3601
	.endo	.L3602
.L3604:	.data.w	.L3603
	.endo	.L3604
.L3606:	.data.w	.L3605
	.endo	.L3606
.L3608:	.data.w	.L3607
	.endo	.L3608
.L3610:	.data.w	.L3609
	.endo	.L3610
.L3612:	.data.w	.L3611
	.endo	.L3612
.L3614:	.data.w	.L3613
	.endo	.L3614
.L3616:	.data.w	.L3615
	.endo	.L3616
.L3618:	.data.w	.L3617
	.endo	.L3618
	.section ".ghrettbl",""
.L3620:	.data.w	.L3619
	.endo	.L3620
	.data
	.global	__caller.Dsadc_Demo.v.v

	.global	__caller.TmcPrintf.i.ppe

	.global	__caller.Dsadc_DeInit.v.v

	.global	__caller.Timer_DelayMs.v.i

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

	.global	__caller.Dsadc_GetVersionInfo.v.p

	.global	__caller.Dsadc_Init.v.p

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.7:
	.endo	..gh.f.a.1.e.7
__callee.Dsadc_Demo.v.v::
	.size	__callee.Dsadc_Demo.v.v,0
Dsadc_Demo::
.LDW13:
	push	{r4-r6,lr}
.LDW23:
	b	.L4024

.L3123:	.data.w	Dma_ConfigSet
	.endo	.L3123

.L3124:	.data.w	.L3012
	.endo	.L3124

.L3571:	.data.w	DsadcDemo_MasterCoreInitFlag
	.endo	.L3571

.L3572:	.data.w	Dsadc_ConfigSet
	.endo	.L3572

.L3573:	.data.w	Dsadc_DemoCoreExeFlag
	.endo	.L3573

.L3574:	.data.w	.L3418
	.endo	.L3574

.L3575:	.data.w	.L3423
	.endo	.L3575

.L3576:	.data.w	.L3424
	.endo	.L3576

.L3577:	.data.w	.L3422
	.endo	.L3577

.L3578:	.data.w	.L3425
	.endo	.L3578

.L3579:	.data.w	.L3426
	.endo	.L3579

.L3580:	.data.w	.L3427
	.endo	.L3580

.L3581:	.data.w	.L3428
	.endo	.L3581

.L3582:	.data.w	.L3421
	.endo	.L3582

.L3583:	.data.w	.L3420
	.endo	.L3583

.L3584:	.data.w	.L3419
	.endo	.L3584

.L4024:

;line724
..lin.d9d0e74b..20e16828.1_2::
.LDWlin2:
..gh.beginasm.8:
	.endo	..gh.beginasm.8
 mrc p15, 0, r1, c0, c0, 5
 and r0, r1, #0xFF        
 and r1, r1, #0xFF00      
 lsr r1, r1, #7           
 uxtab r0, r0, r1         

..gh.endasm.9:
	.endo	..gh.endasm.9

	ldr	r1,.L4025
;line726
..lin.d9d0e74b..20e16828.1_3::
.LDWlin3:
	ldr	r5,.L4026
	ldr	r6,[r1,r0 lsl 2]
	ldr	r1,[r5,8]
	mov	r4,r0
	ldrb	r0,[r6]
	cmp	r1,1
	bne	.L3627
	cmp	r0,0
	ldreq	r0,.L4027
	ldrbeq	r0,[r0]
	cmpeq	r0,1
	bne	.L3634
	cmp	r4,0
	beq	.L3634
	ldr	r0,.L4028
.L4029:

	bl	Dsadc_Init
	mov	r0,1
	b	.L3721
.L3627:
	cmp	r0,1
	bne	.L3634
.L4031:

	bl	Dsadc_DeInit
	mov	r0,0
.L3721:
	strb	r0,[r6]
.L3634:
	ldr	r0,[r5]
	cmp	r0,r4
.L4033:

	popne	{r4-r6,pc}
	ldrb	r0,[r5,4]
	cmp	r0,255
.L4035:

	popeq	{r4-r6,pc}
	ldrb	r0,[r5,4]
	subs	r0,r0,1
	blo	.L3647
	beq	.L3641
	subs	r0,r0,2
	blo	.L3642
	beq	.L3643
	cmp	r0,1
	bne	.L3647
.L4037:

	bl	Dsadc_SingleAccessConversionWithDmaDemo
	b	.L3647
.L3641:
.L4039:

	bl	Dsadc_SingleAccessConversionDemo
	b	.L3647
.L3642:
.L4041:

	bl	Dsadc_StreamingWithLinearBufferDemo
	b	.L3647
.L3643:
.L4043:

	bl	Dsadc_StreamingWithCircularBufferDemo
.L3647:
	ldrb	r0,[r5,4]
	cmp	r0,254
	mvnlo	r0,0
	strblo	r0,[r5,4]
	movlo	r0,0
	strlo	r0,[r5]
.LDW33:
.L4045:

	pop	{r4-r6,pc}
__ghs_eofn_Dsadc_Demo::
	.endf	Dsadc_Demo
;CoreId	r4	local

	.section ".mcal_const_asil_d_unspecified","a"
	.align	4
Dsadc_DemoCoreInitStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.::
Dsadc_DemoCoreInitStatus:
	.data.w	Dsadc_DemoInitStatusCore0
	.data.w	Dsadc_DemoInitStatusCore1
	.space	8
	.endo	Dsadc_DemoCoreInitStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.endo	Dsadc_DemoCoreInitStatus
	.section ".ghcalltbl",""
.L4030:	.data.w	.L4029
	.endo	.L4030
.L4032:	.data.w	.L4031
	.endo	.L4032
	.section ".ghrettbl",""
.L4034:	.data.w	.L4033
	.endo	.L4034
.L4036:	.data.w	.L4035
	.endo	.L4036
	.section ".ghcalltbl",""
.L4038:	.data.w	.L4037
	.endo	.L4038
.L4040:	.data.w	.L4039
	.endo	.L4040
.L4042:	.data.w	.L4041
	.endo	.L4042
.L4044:	.data.w	.L4043
	.endo	.L4044
	.section ".ghrettbl",""
.L4046:	.data.w	.L4045
	.endo	.L4046
	.section ".mcal_bss_asil_d_unspecified_core0","awb"
Dsadc_DemoInitStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.::
Dsadc_DemoInitStatusCore0:	.space	1
	.endo	Dsadc_DemoInitStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.endo	Dsadc_DemoInitStatusCore0
	.section ".mcal_bss_asil_d_unspecified_core1","awb"
Dsadc_DemoInitStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.::
Dsadc_DemoInitStatusCore1:	.space	1
	.endo	Dsadc_DemoInitStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.endo	Dsadc_DemoInitStatusCore1
	.data
	.global	__caller.Dsadc_DeInit.v.v

	.global	__caller.Dsadc_Init.v.p

	.section ".mcal_text_asil_d","ax"
..gh.f.a.1.e.10:
	.endo	..gh.f.a.1.e.10
__callee.DsadcDemo_CircularBufferFull.v.v::
	.size	__callee.DsadcDemo_CircularBufferFull.v.v,0
DsadcDemo_CircularBufferFull::
.LDW43:
	ldr	r1,.L4123
	str	lr,[sp,-8]!
	mov	r0,1
.LDW53:
	strb	r0,[r1]
	mov	r1,0
	mov	r0,2
.L4124:

	bl	Dsadc_GetChannelStatus
	cmp	r0,3
	moveq	r0,2
.L4126:

	bleq	Dsadc_StopConversion
.LDW63:
.L4128:

	ldr	pc,[sp],8
__ghs_eofn_DsadcDemo_CircularBufferFull::
	.endf	DsadcDemo_CircularBufferFull

	.section ".ghcalltbl",""
.L4125:	.data.w	.L4124
	.endo	.L4125
.L4127:	.data.w	.L4126
	.endo	.L4127
	.section ".ghrettbl",""
.L4129:	.data.w	.L4128
	.endo	.L4129
	.data
	.global	__caller.Dsadc_StopConversion.i.i

	.global	__caller.Dsadc_GetChannelStatus.i.ii

	.section ".mcal_text_asil_d","ax"

.L4025:	.data.w	Dsadc_DemoCoreInitStatus
	.endo	.L4025

.L4026:	.data.w	Dsadc_DemoCoreExeFlag
	.endo	.L4026

.L4027:	.data.w	DsadcDemo_MasterCoreInitFlag
	.endo	.L4027

.L4028:	.data.w	Dsadc_ConfigSet
	.endo	.L4028

.L4123:	.data.w	Dsadc_DemoCircularBufferFullFlag
	.endo	.L4123

	.text
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68256D..2::
	.global	__global.use.Dsadc_ConfigSet.a1_C11.struct.256

;Dsadc_ConfigSet	Dsadc_ConfigSet	import
	.global	__global.use.Pwm_ConfigSet.a1_C11.struct.224

;Pwm_ConfigSet	Pwm_ConfigSet	import
	.global	__global.use.Dma_ConfigSet.a1_C11.struct.224

;Dma_ConfigSet	Dma_ConfigSet	import
;Dsadc_DemoInitStatusCore0	Dsadc_DemoInitStatusCore0	static
;Dsadc_DemoCircularBufferFullFlag	Dsadc_DemoCircularBufferFullFlag	static
;Dsadc_DemoInitStatusCore1	Dsadc_DemoInitStatusCore1	static
;Dsadc_DemoCoreExeFlag	Dsadc_DemoCoreExeFlag	static
	.global	__global.com.DsadcDemo_MainConvResult.a10_Ss

;DsadcDemo_MasterCoreInitFlag	DsadcDemo_MasterCoreInitFlag	static
;Dsadc_DemoCoreInitStatus	Dsadc_DemoCoreInitStatus	static

	.global	Dsadc_ConfigSet

	.global	Pwm_ConfigSet

	.global	Dma_ConfigSet

	.ghsnote info, 29, 8195, 131712
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68256D..2::
	.section ".sdk_text_asil_d","ax"
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68256D..0::
	.section ".mcal_text_asil_d","ax"
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68256D..1::
	.text
	.section	.debug_abbrev		;off: 0
.Ldw_abbr_begin:
	.section	.debug_str		;off: 0
.Ldw_str_begin:
	.section	.debug_info		;off: 0
.Ldw_begin:
	.data.b	1,43,0,0
	.data.b	2,0
	.data.w	.Ldw_abbr_begin
	.data.b	4
	.data.b	2
	.section	.debug_str		;off: 0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,68,101,109,111,95,68,115,97,100,99,47,68,115,97,100,99,95,68,101,109,111,46,99,0
	.section	.debug_info		;off: 12
	.data.w	.Ldw_str_begin
	.section	.debug_str		;off: 35
	.data.b	68,58,92,65,117,116,111,95,84,111,111,108,65,110,100,70,105,114,109,119,97,114,101,92,49,50,95,77,67,65,76,92,48,52,95,84,72,65,54,52,49,50,92,48,52,95,82,101,108,101,97,115,101,92,84,77,67,95,84,72
	.data.b	65,54,95,83,101,114,105,101,115,95,77,67,65,76,95,65,83,52,52,48,95,70,117,83,97,95,86,49,46,50,46,48,92,48,50,95,67,111,100,101,92,84,72,65,54,88,88,88,95,77,67,95,65,83,52,52,48,92,68,101
	.data.b	109,111,87,111,114,107,115,112,97,99,101,92,67,111,100,101,80,114,111,106,101,99,116,0
	.section	.debug_info		;off: 16
	.data.w	.Ldw_str_begin+35
	.section	.debug_str		;off: 179
	.data.b	71,72,83,32,67,32,50,48,50,51,46,49,46,52,32,91,100,117,97,108,93,0
	.section	.debug_info		;off: 20
	.data.w	.Ldw_str_begin+179
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
	.data.b	112,16,0,0
	.data.b	2,0
	.data.b	167,13,0,0
	.data.b	1
	.data.b	0
	.data.b	0
	.data.b	4
	.data.b	10
	.data.b	0,1,1
	.data.b	1,1,0
	.data.b	0,0,1
	.data.b	0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,68,101,109,111,95,68,115,97,100,99,47,68,115,97,100,99,95,68,101,109,111,46,99,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,68,101,109,111,95,68,115,97,100,99,47,68,115,97,100,99,95,68,101,109,111,46,104,0
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
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,68,115,97,100,99,92,105,110,99,108,117,100,101,92,68,115,97,100,99,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,68,115,97,100,99,92,105,110,99,108,117,100,101,92,68,115,97,100,99,95,71,101,110,101,114,97,108,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,68,115,97,100,99,95,67,102,103,46,104,0
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
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,80,119,109,92,105,110,99,108,117,100,101,92,80,119,109,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,80,119,109,95,67,102,103,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,80,119,109,92,105,110,99,108,117,100,101,92,80,119,109,95,71,101,110,101,114,97,108,84,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,103,116,109,92,112,119,109,92,103,116,109,95,112,119,109,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,103,116,109,92,115,116,100,92,116,111,109,92,103,116,109,95,116,111,109,95,115,116,100,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,103,116,109,92,99,111,109,109,111,110,92,103,116,109,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,103,116,109,92,99,111,109,109,111,110,92,103,116,109,95,114,101,103,105,115,116,101,114,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,71,116,109,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,103,116,109,92,115,116,100,92,97,116,111,109,92,103,116,109,95,97,116,111,109,95,115,116,100,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,77,101,109,109,97,112,92,80,119,109,95,77,101,109,77,97,112,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,77,99,97,108,92,67,111,100,101,92,80,119,109,92,105,110,99,108,117,100,101,92,80,119,109,95,86,101,114,115,105,111,110,46,104,0
	.data.b	0,0,0
	.data.b	46,92,68,101,109,111,77,99,97,108,92,67,111,110,102,105,103,92,84,72,65,54,52,49,50,95,66,71,65,53,49,54,92,105,110,99,108,117,100,101,92,80,119,109,95,80,66,99,102,103,46,104,0
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
	.data.w	.Ldw_begin+1393
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
	.section	.debug_str		;off: 201
	.data.b	117,110,115,105,103,110,101,100,32,99,104,97,114,0
	.section	.debug_info		;off: 43
	.data.w	.Ldw_str_begin+201
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
	.section	.debug_str		;off: 215
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,0
	.section	.debug_info		;off: 50
	.data.w	.Ldw_str_begin+215
	.data.b	7
	.data.b	4

	.data.b	42
	.section	.debug_str		;off: 229
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,32,108,111,110,103,0
	.section	.debug_info		;off: 57
	.data.w	.Ldw_str_begin+229
	.data.b	7
	.data.b	8

	.data.b	42
	.section	.debug_str		;off: 248
	.data.b	117,110,115,105,103,110,101,100,32,115,104,111,114,116,0
	.section	.debug_info		;off: 64
	.data.w	.Ldw_str_begin+248
	.data.b	7
	.data.b	2

	.data.b	42
	.section	.debug_str		;off: 263
	.data.b	102,108,111,97,116,0
	.section	.debug_info		;off: 71
	.data.w	.Ldw_str_begin+263
	.data.b	4
	.data.b	4

	.data.b	42
	.section	.debug_str		;off: 269
	.data.b	115,104,111,114,116,0
	.section	.debug_info		;off: 78
	.data.w	.Ldw_str_begin+269
	.data.b	5
	.data.b	2

	.data.b	74
	.data.w	.Ldw_begin+1214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1166
	.data.b	0

	.section	.debug_abbrev		;off: 39
	.data.b	23
	.data.b	5
	.data.b	0
	.data.b	73,16
	.data.b	75,12
	.data.b	0,0

	.section	.debug_info		;off: 96
	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1214
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1166
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.section	.debug_abbrev		;off: 48
	.data.b	75
	.data.b	21
	.data.b	1
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 112
	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 275
	.data.b	105,110,116,0
	.section	.debug_info		;off: 114
	.data.w	.Ldw_str_begin+275
	.data.b	5
	.data.b	4

	.data.b	64
	.data.b	0
	.data.b	4
	.data.w	.Ldw_begin+3619

	.section	.debug_abbrev		;off: 55
	.data.b	64
	.data.b	1
	.data.b	1
	.data.b	9,11
	.data.b	11,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 127
	.data.b	56
	.data.w	.Ldw_begin+113
	.data.b	4
	.data.b	0
	.data.b	1

	.section	.debug_abbrev		;off: 66
	.data.b	56
	.data.b	33
	.data.b	0
	.data.b	73,16
	.data.b	11,15
	.data.b	34,13
	.data.b	47,13
	.data.b	0,0

	.section	.debug_info		;off: 135
	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+3619

	.section	.debug_abbrev		;off: 79
	.data.b	53
	.data.b	15
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 144
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
	.section	.debug_str		;off: 279
	.data.b	99,104,97,114,0
	.section	.debug_info		;off: 154
	.data.w	.Ldw_str_begin+279
	.data.b	8
	.data.b	1

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	42
	.section	.debug_str		;off: 284
	.data.b	100,111,117,98,108,101,0
	.section	.debug_info		;off: 167
	.data.w	.Ldw_str_begin+284
	.data.b	4
	.data.b	8

	.data.b	42
	.section	.debug_str		;off: 291
	.data.b	117,110,115,105,103,110,101,100,32,105,110,116,0
	.section	.debug_info		;off: 174
	.data.w	.Ldw_str_begin+291
	.data.b	7
	.data.b	4

	.data.b	47
	.data.w	.Ldw_begin+2547

	.section	.debug_abbrev		;off: 86
	.data.b	47
	.data.b	38
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 185
	.data.b	53
	.data.w	.Ldw_begin+180

	.data.b	47
	.data.w	.Ldw_begin+2602

	.data.b	53
	.data.w	.Ldw_begin+190

	.data.b	47
	.data.w	.Ldw_begin+2708

	.data.b	53
	.data.w	.Ldw_begin+200

	.data.b	47
	.data.w	.Ldw_begin+2835

	.data.b	53
	.data.w	.Ldw_begin+210

	.data.b	47
	.data.w	.Ldw_begin+3060

	.data.b	53
	.data.w	.Ldw_begin+220

	.data.b	47
	.data.w	.Ldw_begin+3149

	.data.b	53
	.data.w	.Ldw_begin+230

	.data.b	47
	.data.w	.Ldw_begin+2780

	.data.b	53
	.data.w	.Ldw_begin+240

	.data.b	47
	.data.w	.Ldw_begin+3187

	.data.b	53
	.data.w	.Ldw_begin+250

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3879
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+260

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+274

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3837
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+3619
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+282

	.data.b	47
	.data.w	.Ldw_begin+3594

	.data.b	53
	.data.w	.Ldw_begin+302

	.data.b	47
	.data.w	.Ldw_begin+3450

	.data.b	53
	.data.w	.Ldw_begin+312

	.data.b	47
	.data.w	.Ldw_begin+4261

	.data.b	53
	.data.w	.Ldw_begin+322

	.data.b	47
	.data.w	.Ldw_begin+3539

	.data.b	53
	.data.w	.Ldw_begin+332

	.data.b	47
	.data.w	.Ldw_begin+4316

	.data.b	53
	.data.w	.Ldw_begin+342

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+347

	.data.b	56
	.data.w	.Ldw_begin+113
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+4388

	.data.b	53
	.data.w	.Ldw_begin+368

	.data.b	47
	.data.w	.Ldw_begin+3951

	.data.b	53
	.data.w	.Ldw_begin+378

	.data.b	47
	.data.w	.Ldw_begin+1154

	.data.b	53
	.data.w	.Ldw_begin+388

	.data.b	53
	.data.w	.Ldw_begin+153

	.data.b	53
	.data.w	.Ldw_begin+1154

	.data.b	49
	.data.w	.Ldw_begin+4560

	.section	.debug_abbrev		;off: 93
	.data.b	49
	.data.b	53
	.data.b	0
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 413
	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+413

	.data.b	47
	.data.w	.Ldw_begin+5862

	.data.b	53
	.data.w	.Ldw_begin+421

	.data.b	47
	.data.w	.Ldw_begin+5972

	.data.b	53
	.data.w	.Ldw_begin+431

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+436

	.data.b	56
	.data.w	.Ldw_begin+113
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+5917

	.data.b	53
	.data.w	.Ldw_begin+457

	.data.b	64
	.data.b	0
	.data.b	8
	.data.w	.Ldw_begin+393

	.data.b	56
	.data.w	.Ldw_begin+113
	.data.b	4
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	49
	.data.w	.Ldw_begin+6057

	.data.b	49
	.data.w	.Ldw_begin+6098

	.data.b	49
	.data.w	.Ldw_begin+6139

	.data.b	49
	.data.w	.Ldw_begin+6220

	.data.b	49
	.data.w	.Ldw_begin+6501

	.data.b	47
	.data.w	.Ldw_begin+8249

	.data.b	53
	.data.w	.Ldw_begin+508

	.data.b	47
	.data.w	.Ldw_begin+8688

	.data.b	53
	.data.w	.Ldw_begin+518

	.data.b	53
	.data.w	.Ldw_begin+8321

	.data.b	47
	.data.w	.Ldw_begin+8017

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+8237
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+8476
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+538

	.data.b	47
	.data.w	.Ldw_begin+8237

	.data.b	53
	.data.w	.Ldw_begin+558

	.data.b	47
	.data.w	.Ldw_begin+7856

	.data.b	47
	.data.w	.Ldw_begin+8798

	.data.b	53
	.data.w	.Ldw_begin+573

	.data.b	47
	.data.w	.Ldw_begin+8743

	.data.b	53
	.data.w	.Ldw_begin+583

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+8237
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+8412
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+593

	.data.b	47
	.data.w	.Ldw_begin+9014

	.data.b	53
	.data.w	.Ldw_begin+613

	.data.b	47
	.data.w	.Ldw_begin+8225

	.data.b	53
	.data.w	.Ldw_begin+623

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+563

	.data.b	56
	.data.w	.Ldw_begin+113
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+8908

	.data.b	53
	.data.w	.Ldw_begin+649

	.data.b	47
	.data.w	.Ldw_begin+9222

	.data.b	53
	.data.w	.Ldw_begin+659

	.data.b	47
	.data.w	.Ldw_begin+8853

	.data.b	53
	.data.w	.Ldw_begin+669

	.data.b	47
	.data.w	.Ldw_begin+8106

	.data.b	53
	.data.w	.Ldw_begin+679

	.data.b	47
	.data.w	.Ldw_begin+7945

	.data.b	53
	.data.w	.Ldw_begin+689

	.data.b	47
	.data.w	.Ldw_begin+9383

	.data.b	53
	.data.w	.Ldw_begin+699

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+704

	.data.b	56
	.data.w	.Ldw_begin+113
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+9455

	.data.b	53
	.data.w	.Ldw_begin+725

	.data.b	47
	.data.w	.Ldw_begin+8633

	.data.b	53
	.data.w	.Ldw_begin+735

	.data.b	47
	.data.w	.Ldw_begin+9294

	.data.b	53
	.data.w	.Ldw_begin+745

	.data.b	47
	.data.w	.Ldw_begin+4494

	.data.b	64
	.data.b	0
	.data.b	32
	.data.w	.Ldw_begin+755

	.data.b	56
	.data.w	.Ldw_begin+113
	.data.b	4
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+6044

	.data.b	64
	.data.b	0
	.data.b	28
	.data.w	.Ldw_begin+776

	.data.b	56
	.data.w	.Ldw_begin+113
	.data.b	4
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+9544

	.data.b	64
	.data.b	0
	.data.b	28
	.data.w	.Ldw_begin+797

	.data.b	56
	.data.w	.Ldw_begin+113
	.data.b	4
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	20
	.data.w	.Ldw_begin+3619

	.data.b	56
	.data.w	.Ldw_begin+113
	.data.b	4
	.data.b	0
	.data.b	9

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+403

	.data.b	64
	.data.b	0
	.data.b	16
	.data.w	.Ldw_begin+834

	.data.b	56
	.data.w	.Ldw_begin+113
	.data.b	4
	.data.b	0
	.data.b	3

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+755

	.data.b	47
	.data.w	.Ldw_begin+855

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+860
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	47
	.data.w	.Ldw_begin+139

	.data.b	74
	.data.w	.Ldw_begin+1226
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3607
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+877
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1226
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3607
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1226
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3607
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+139

	.data.b	47
	.data.w	.Ldw_begin+927

	.data.b	74
	.data.w	.Ldw_begin+3643
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3607
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+932
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+3714
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3607
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+3879
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+3631
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3607
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3607
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+3607
	.data.b	0

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+1325

	.data.b	47
	.data.w	.Ldw_begin+1006

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1011
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+4507
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+4507
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1190
	.data.b	0

	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+1154
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+398
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+393
	.data.b	0

	.data.b	76

	.section	.debug_abbrev		;off: 100
	.data.b	76
	.data.b	24
	.data.b	0
	.data.b	0,0

	.section	.debug_info		;off: 1071
	.data.b	0

	.data.b	74
	.data.w	.Ldw_begin+153
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+776

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1079
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	53
	.data.w	.Ldw_begin+797

	.data.b	47
	.data.w	.Ldw_begin+1096

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+1101
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+8237
	.data.b	0

	.data.b	0

	.data.b	75
	.data.b	1

	.data.b	23
	.data.w	.Ldw_begin+8237
	.data.b	0

	.data.b	23
	.data.w	.Ldw_begin+8362
	.data.b	0

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 304
	.data.b	98,111,111,108,101,97,110,0
	.section	.debug_info		;off: 1143
	.data.w	.Ldw_str_begin+304
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

	.section	.debug_info		;off: 1154
	.data.b	45
	.section	.debug_str		;off: 312
	.data.b	117,105,110,116,56,0
	.section	.debug_info		;off: 1155
	.data.w	.Ldw_str_begin+312
	.data.b	56
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+42

	.data.b	45
	.section	.debug_str		;off: 318
	.data.b	115,105,110,116,49,54,0
	.section	.debug_info		;off: 1167
	.data.w	.Ldw_str_begin+318
	.data.b	58
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+77

	.data.b	45
	.section	.debug_str		;off: 325
	.data.b	117,105,110,116,49,54,0
	.section	.debug_info		;off: 1179
	.data.w	.Ldw_str_begin+325
	.data.b	60
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+63

	.data.b	45
	.section	.debug_str		;off: 332
	.data.b	117,105,110,116,51,50,0
	.section	.debug_info		;off: 1191
	.data.w	.Ldw_str_begin+332
	.data.b	64
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+49

	.data.b	45
	.section	.debug_str		;off: 339
	.data.b	117,105,110,116,54,52,0
	.section	.debug_info		;off: 1203
	.data.w	.Ldw_str_begin+339
	.data.b	68
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+56

	.data.b	45
	.section	.debug_str		;off: 346
	.data.b	102,108,111,97,116,51,50,0
	.section	.debug_info		;off: 1215
	.data.w	.Ldw_str_begin+346
	.data.b	83
	.data.b	29
	.data.b	8
	.data.w	.Ldw_begin+70

	.data.b	45
	.section	.debug_str		;off: 354
	.data.b	83,116,100,95,82,101,116,117,114,110,84,121,112,101,0
	.section	.debug_info		;off: 1227
	.data.w	.Ldw_str_begin+354
	.data.b	39
	.data.b	15
	.data.b	3
	.data.w	.Ldw_begin+1154

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

	.section	.debug_info		;off: 1244
	.data.b	40
	.section	.debug_str		;off: 369
	.data.b	118,101,110,100,111,114,73,68,0
	.section	.debug_info		;off: 1245
	.data.w	.Ldw_str_begin+369
	.data.b	63
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1178
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

	.section	.debug_info		;off: 1260
	.data.b	40
	.section	.debug_str		;off: 378
	.data.b	109,111,100,117,108,101,73,68,0
	.section	.debug_info		;off: 1261
	.data.w	.Ldw_str_begin+378
	.data.b	64
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1178
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 387
	.data.b	115,119,95,109,97,106,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1277
	.data.w	.Ldw_str_begin+387
	.data.b	65
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 404
	.data.b	115,119,95,109,105,110,111,114,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1293
	.data.w	.Ldw_str_begin+404
	.data.b	66
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 421
	.data.b	115,119,95,112,97,116,99,104,95,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 1309
	.data.w	.Ldw_str_begin+421
	.data.b	67
	.data.b	13
	.data.b	3
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 438
	.data.b	83,116,100,95,86,101,114,115,105,111,110,73,110,102,111,84,121,112,101,0
	.section	.debug_info		;off: 1326
	.data.w	.Ldw_str_begin+438
	.data.b	68
	.data.b	2
	.data.b	3
	.data.w	.Ldw_begin+1238

	.data.b	52
	.section	.debug_str		;off: 458
	.data.b	0
	.section	.debug_info		;off: 1338
	.data.w	.Ldw_str_begin+458
	.data.b	36
	.data.b	1
	.data.b	15
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

	.section	.debug_info		;off: 1347
	.data.b	51
	.section	.debug_str		;off: 459
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,48,0
	.section	.debug_info		;off: 1348
	.data.w	.Ldw_str_begin+459
	.data.b	37
	.data.b	5
	.data.b	15
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

	.section	.debug_info		;off: 1356
	.data.b	51
	.section	.debug_str		;off: 476
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,49,0
	.section	.debug_info		;off: 1357
	.data.w	.Ldw_str_begin+476
	.data.b	38
	.data.b	5
	.data.b	15
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 493
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,50,0
	.section	.debug_info		;off: 1366
	.data.w	.Ldw_str_begin+493
	.data.b	39
	.data.b	5
	.data.b	15
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 510
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,51,0
	.section	.debug_info		;off: 1375
	.data.w	.Ldw_str_begin+510
	.data.b	40
	.data.b	5
	.data.b	15
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 527
	.data.b	77,85,76,84,73,67,79,82,69,73,68,95,78,79,78,69,0
	.section	.debug_info		;off: 1384
	.data.w	.Ldw_str_begin+527
	.data.b	41
	.data.b	5
	.data.b	15
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 544
	.data.b	77,117,108,116,105,67,111,114,101,73,68,0
	.section	.debug_info		;off: 1394
	.data.w	.Ldw_str_begin+544
	.data.b	42
	.data.b	3
	.data.b	15
	.data.w	.Ldw_begin+1337

	.data.b	45
	.section	.debug_str		;off: 556
	.data.b	77,99,97,108,95,67,111,114,101,84,121,112,101,0
	.section	.debug_info		;off: 1406
	.data.w	.Ldw_str_begin+556
	.data.b	32
	.data.b	21
	.data.b	14
	.data.w	.Ldw_begin+1393

	.data.b	52
	.section	.debug_str		;off: 570
	.data.b	0
	.section	.debug_info		;off: 1418
	.data.w	.Ldw_str_begin+570
	.data.b	70
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 571
	.data.b	68,83,65,68,67,95,73,78,80,85,84,77,85,76,84,73,80,76,69,88,69,82,84,82,73,71,71,69,82,77,79,68,69,95,83,79,70,84,87,65,82,69,0
	.section	.debug_info		;off: 1428
	.data.w	.Ldw_str_begin+571
	.data.b	71
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 614
	.data.b	68,83,65,68,67,95,73,78,80,85,84,77,85,76,84,73,80,76,69,88,69,82,84,82,73,71,71,69,82,77,79,68,69,95,82,73,83,73,78,71,0
	.section	.debug_info		;off: 1437
	.data.w	.Ldw_str_begin+614
	.data.b	72
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 655
	.data.b	68,83,65,68,67,95,73,78,80,85,84,77,85,76,84,73,80,76,69,88,69,82,84,82,73,71,71,69,82,77,79,68,69,95,70,65,76,76,73,78,71,0
	.section	.debug_info		;off: 1446
	.data.w	.Ldw_str_begin+655
	.data.b	73
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 697
	.data.b	68,83,65,68,67,95,73,78,80,85,84,77,85,76,84,73,80,76,69,88,69,82,84,82,73,71,71,69,82,77,79,68,69,95,66,79,84,72,0
	.section	.debug_info		;off: 1455
	.data.w	.Ldw_str_begin+697
	.data.b	74
	.data.b	5
	.data.b	36
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 736
	.data.b	68,115,97,100,99,95,73,110,112,117,116,77,117,108,116,105,112,108,101,120,101,114,84,114,105,103,103,101,114,77,111,100,101,0
	.section	.debug_info		;off: 1465
	.data.w	.Ldw_str_begin+736
	.data.b	75
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1417

	.data.b	52
	.section	.debug_str		;off: 770
	.data.b	0
	.section	.debug_info		;off: 1477
	.data.w	.Ldw_str_begin+770
	.data.b	79
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 771
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,65,0
	.section	.debug_info		;off: 1487
	.data.w	.Ldw_str_begin+771
	.data.b	80
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 793
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,66,0
	.section	.debug_info		;off: 1496
	.data.w	.Ldw_str_begin+793
	.data.b	81
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 815
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,67,0
	.section	.debug_info		;off: 1505
	.data.w	.Ldw_str_begin+815
	.data.b	82
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 837
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,68,0
	.section	.debug_info		;off: 1514
	.data.w	.Ldw_str_begin+837
	.data.b	83
	.data.b	5
	.data.b	36
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 859
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,69,0
	.section	.debug_info		;off: 1523
	.data.w	.Ldw_str_begin+859
	.data.b	84
	.data.b	5
	.data.b	36
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 881
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,70,0
	.section	.debug_info		;off: 1532
	.data.w	.Ldw_str_begin+881
	.data.b	85
	.data.b	5
	.data.b	36
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 903
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,71,0
	.section	.debug_info		;off: 1541
	.data.w	.Ldw_str_begin+903
	.data.b	86
	.data.b	5
	.data.b	36
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 925
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,72,0
	.section	.debug_info		;off: 1550
	.data.w	.Ldw_str_begin+925
	.data.b	87
	.data.b	5
	.data.b	36
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 947
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,73,0
	.section	.debug_info		;off: 1559
	.data.w	.Ldw_str_begin+947
	.data.b	88
	.data.b	5
	.data.b	36
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 969
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,74,0
	.section	.debug_info		;off: 1568
	.data.w	.Ldw_str_begin+969
	.data.b	89
	.data.b	5
	.data.b	36
	.data.b	9

	.data.b	51
	.section	.debug_str		;off: 991
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,75,0
	.section	.debug_info		;off: 1577
	.data.w	.Ldw_str_begin+991
	.data.b	90
	.data.b	5
	.data.b	36
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 1013
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,76,0
	.section	.debug_info		;off: 1586
	.data.w	.Ldw_str_begin+1013
	.data.b	91
	.data.b	5
	.data.b	36
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 1035
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,77,0
	.section	.debug_info		;off: 1595
	.data.w	.Ldw_str_begin+1035
	.data.b	92
	.data.b	5
	.data.b	36
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 1057
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,78,0
	.section	.debug_info		;off: 1604
	.data.w	.Ldw_str_begin+1057
	.data.b	93
	.data.b	5
	.data.b	36
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 1079
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,79,0
	.section	.debug_info		;off: 1613
	.data.w	.Ldw_str_begin+1079
	.data.b	94
	.data.b	5
	.data.b	36
	.data.b	14

	.data.b	51
	.section	.debug_str		;off: 1101
	.data.b	68,83,65,68,67,95,84,82,73,71,71,69,82,83,79,85,82,67,69,95,80,0
	.section	.debug_info		;off: 1622
	.data.w	.Ldw_str_begin+1101
	.data.b	95
	.data.b	5
	.data.b	36
	.data.b	15

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1123
	.data.b	68,115,97,100,99,95,84,114,105,103,103,101,114,83,111,117,114,99,101,0
	.section	.debug_info		;off: 1632
	.data.w	.Ldw_str_begin+1123
	.data.b	96
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1476

	.data.b	52
	.section	.debug_str		;off: 1143
	.data.b	0
	.section	.debug_info		;off: 1644
	.data.w	.Ldw_str_begin+1143
	.data.b	100
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1144
	.data.b	68,83,65,68,67,95,84,73,77,69,83,84,65,77,80,84,82,73,71,71,69,82,77,79,68,69,95,78,79,78,69,0
	.section	.debug_info		;off: 1654
	.data.w	.Ldw_str_begin+1144
	.data.b	101
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1176
	.data.b	68,83,65,68,67,95,84,73,77,69,83,84,65,77,80,84,82,73,71,71,69,82,77,79,68,69,95,82,73,83,73,78,71,0
	.section	.debug_info		;off: 1663
	.data.w	.Ldw_str_begin+1176
	.data.b	102
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1210
	.data.b	68,83,65,68,67,95,84,73,77,69,83,84,65,77,80,84,82,73,71,71,69,82,77,79,68,69,95,70,65,76,76,73,78,71,0
	.section	.debug_info		;off: 1672
	.data.w	.Ldw_str_begin+1210
	.data.b	103
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1245
	.data.b	68,83,65,68,67,95,84,73,77,69,83,84,65,77,80,84,82,73,71,71,69,82,77,79,68,69,95,66,79,84,72,0
	.section	.debug_info		;off: 1681
	.data.w	.Ldw_str_begin+1245
	.data.b	104
	.data.b	5
	.data.b	36
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1277
	.data.b	68,115,97,100,99,95,84,105,109,101,83,116,97,109,112,84,114,105,103,103,101,114,77,111,100,101,0
	.section	.debug_info		;off: 1691
	.data.w	.Ldw_str_begin+1277
	.data.b	105
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1643

	.data.b	52
	.section	.debug_str		;off: 1304
	.data.b	0
	.section	.debug_info		;off: 1703
	.data.w	.Ldw_str_begin+1304
	.data.b	109
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1305
	.data.b	68,83,65,68,67,95,67,73,67,80,65,82,65,76,76,69,76,83,69,76,69,67,84,73,79,78,95,49,0
	.section	.debug_info		;off: 1713
	.data.w	.Ldw_str_begin+1305
	.data.b	110
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1334
	.data.b	68,83,65,68,67,95,67,73,67,80,65,82,65,76,76,69,76,83,69,76,69,67,84,73,79,78,95,50,0
	.section	.debug_info		;off: 1722
	.data.w	.Ldw_str_begin+1334
	.data.b	111
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1363
	.data.b	68,83,65,68,67,95,67,73,67,80,65,82,65,76,76,69,76,83,69,76,69,67,84,73,79,78,95,51,0
	.section	.debug_info		;off: 1731
	.data.w	.Ldw_str_begin+1363
	.data.b	112
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1392
	.data.b	68,83,65,68,67,95,67,73,67,80,65,82,65,76,76,69,76,83,69,76,69,67,84,73,79,78,95,52,0
	.section	.debug_info		;off: 1740
	.data.w	.Ldw_str_begin+1392
	.data.b	113
	.data.b	5
	.data.b	36
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1421
	.data.b	68,115,97,100,99,95,67,105,99,80,97,114,97,108,108,101,108,83,101,108,101,99,116,105,111,110,0
	.section	.debug_info		;off: 1750
	.data.w	.Ldw_str_begin+1421
	.data.b	114
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1702

	.data.b	52
	.section	.debug_str		;off: 1448
	.data.b	0
	.section	.debug_info		;off: 1762
	.data.w	.Ldw_str_begin+1448
	.data.b	146,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1449
	.data.b	68,83,65,68,67,95,83,69,82,86,73,67,69,82,69,81,85,69,83,84,95,78,79,78,69,0
	.section	.debug_info		;off: 1773
	.data.w	.Ldw_str_begin+1449
	.data.b	147,1
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1475
	.data.b	68,83,65,68,67,95,83,69,82,86,73,67,69,82,69,81,85,69,83,84,95,72,73,71,72,0
	.section	.debug_info		;off: 1783
	.data.w	.Ldw_str_begin+1475
	.data.b	148,1
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1501
	.data.b	68,83,65,68,67,95,83,69,82,86,73,67,69,82,69,81,85,69,83,84,95,76,79,87,0
	.section	.debug_info		;off: 1793
	.data.w	.Ldw_str_begin+1501
	.data.b	149,1
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1526
	.data.b	68,83,65,68,67,95,83,69,82,86,73,67,69,82,69,81,85,69,83,84,95,70,73,70,79,84,72,82,69,83,72,79,76,68,0
	.section	.debug_info		;off: 1803
	.data.w	.Ldw_str_begin+1526
	.data.b	150,1
	.data.b	5
	.data.b	36
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1561
	.data.b	68,115,97,100,99,95,83,101,114,118,105,99,101,82,101,113,117,101,115,116,0
	.section	.debug_info		;off: 1814
	.data.w	.Ldw_str_begin+1561
	.data.b	151,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1761

	.data.b	52
	.section	.debug_str		;off: 1582
	.data.b	0
	.section	.debug_info		;off: 1827
	.data.w	.Ldw_str_begin+1582
	.data.b	155,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1583
	.data.b	68,83,65,68,67,95,65,76,65,82,77,67,79,78,68,73,84,73,79,78,95,78,69,87,82,69,83,85,76,84,0
	.section	.debug_info		;off: 1838
	.data.w	.Ldw_str_begin+1583
	.data.b	156,1
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1614
	.data.b	68,83,65,68,67,95,65,76,65,82,77,67,79,78,68,73,84,73,79,78,95,82,69,83,85,76,84,73,78,82,65,78,71,69,0
	.section	.debug_info		;off: 1848
	.data.w	.Ldw_str_begin+1614
	.data.b	157,1
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1649
	.data.b	68,83,65,68,67,95,65,76,65,82,77,67,79,78,68,73,84,73,79,78,95,82,69,83,85,76,84,79,85,84,82,65,78,71,69,0
	.section	.debug_info		;off: 1858
	.data.w	.Ldw_str_begin+1649
	.data.b	158,1
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1685
	.data.b	68,115,97,100,99,95,77,97,105,110,65,108,97,114,109,67,111,110,100,105,116,105,111,110,0
	.section	.debug_info		;off: 1869
	.data.w	.Ldw_str_begin+1685
	.data.b	159,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1826

	.data.b	52
	.section	.debug_str		;off: 1710
	.data.b	0
	.section	.debug_info		;off: 1882
	.data.w	.Ldw_str_begin+1710
	.data.b	163,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1711
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,85,84,80,85,84,83,72,73,70,84,95,48,0
	.section	.debug_info		;off: 1893
	.data.w	.Ldw_str_begin+1711
	.data.b	164,1
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1737
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,85,84,80,85,84,83,72,73,70,84,95,49,0
	.section	.debug_info		;off: 1903
	.data.w	.Ldw_str_begin+1737
	.data.b	165,1
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1763
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,85,84,80,85,84,83,72,73,70,84,95,50,0
	.section	.debug_info		;off: 1913
	.data.w	.Ldw_str_begin+1763
	.data.b	166,1
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1789
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,85,84,80,85,84,83,72,73,70,84,95,51,0
	.section	.debug_info		;off: 1923
	.data.w	.Ldw_str_begin+1789
	.data.b	167,1
	.data.b	5
	.data.b	36
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 1815
	.data.b	68,115,97,100,99,95,70,105,114,79,102,102,115,101,116,0
	.section	.debug_info		;off: 1934
	.data.w	.Ldw_str_begin+1815
	.data.b	168,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1881

	.data.b	52
	.section	.debug_str		;off: 1831
	.data.b	0
	.section	.debug_info		;off: 1947
	.data.w	.Ldw_str_begin+1831
	.data.b	172,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1832
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,70,70,83,69,84,67,79,77,80,69,78,83,65,84,73,79,78,95,48,0
	.section	.debug_info		;off: 1958
	.data.w	.Ldw_str_begin+1832
	.data.b	173,1
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 1865
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,70,70,83,69,84,67,79,77,80,69,78,83,65,84,73,79,78,95,49,0
	.section	.debug_info		;off: 1968
	.data.w	.Ldw_str_begin+1865
	.data.b	174,1
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 1898
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,70,70,83,69,84,67,79,77,80,69,78,83,65,84,73,79,78,95,50,0
	.section	.debug_info		;off: 1978
	.data.w	.Ldw_str_begin+1898
	.data.b	175,1
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 1931
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,70,70,83,69,84,67,79,77,80,69,78,83,65,84,73,79,78,95,51,0
	.section	.debug_info		;off: 1988
	.data.w	.Ldw_str_begin+1931
	.data.b	176,1
	.data.b	5
	.data.b	36
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 1964
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,70,70,83,69,84,67,79,77,80,69,78,83,65,84,73,79,78,95,52,0
	.section	.debug_info		;off: 1998
	.data.w	.Ldw_str_begin+1964
	.data.b	177,1
	.data.b	5
	.data.b	36
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 1997
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,70,70,83,69,84,67,79,77,80,69,78,83,65,84,73,79,78,95,53,0
	.section	.debug_info		;off: 2008
	.data.w	.Ldw_str_begin+1997
	.data.b	178,1
	.data.b	5
	.data.b	36
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 2030
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,70,70,83,69,84,67,79,77,80,69,78,83,65,84,73,79,78,95,54,0
	.section	.debug_info		;off: 2018
	.data.w	.Ldw_str_begin+2030
	.data.b	179,1
	.data.b	5
	.data.b	36
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 2063
	.data.b	68,83,65,68,67,95,70,73,76,84,69,82,79,70,70,83,69,84,67,79,77,80,69,78,83,65,84,73,79,78,95,55,0
	.section	.debug_info		;off: 2028
	.data.w	.Ldw_str_begin+2063
	.data.b	180,1
	.data.b	5
	.data.b	36
	.data.b	7

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2096
	.data.b	68,115,97,100,99,95,70,105,108,116,101,114,79,102,102,115,101,116,67,111,109,112,101,110,115,97,116,105,111,110,0
	.section	.debug_info		;off: 2039
	.data.w	.Ldw_str_begin+2096
	.data.b	181,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+1946

	.data.b	52
	.section	.debug_str		;off: 2127
	.data.b	0
	.section	.debug_info		;off: 2052
	.data.w	.Ldw_str_begin+2127
	.data.b	185,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2128
	.data.b	68,83,65,68,67,95,87,65,86,69,83,69,76,69,67,84,95,78,79,78,69,0
	.section	.debug_info		;off: 2063
	.data.w	.Ldw_str_begin+2128
	.data.b	186,1
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2150
	.data.b	68,83,65,68,67,95,87,65,86,69,83,69,76,69,67,84,95,83,73,78,69,0
	.section	.debug_info		;off: 2073
	.data.w	.Ldw_str_begin+2150
	.data.b	187,1
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2172
	.data.b	68,83,65,68,67,95,87,65,86,69,83,69,76,69,67,84,95,84,82,73,65,78,71,85,76,65,82,0
	.section	.debug_info		;off: 2083
	.data.w	.Ldw_str_begin+2172
	.data.b	188,1
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 2200
	.data.b	68,83,65,68,67,95,87,65,86,69,83,69,76,69,67,84,95,83,81,85,65,82,69,0
	.section	.debug_info		;off: 2093
	.data.w	.Ldw_str_begin+2200
	.data.b	189,1
	.data.b	5
	.data.b	36
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2224
	.data.b	68,115,97,100,99,95,87,97,118,101,77,111,100,101,0
	.section	.debug_info		;off: 2104
	.data.w	.Ldw_str_begin+2224
	.data.b	190,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2051

	.data.b	52
	.section	.debug_str		;off: 2239
	.data.b	0
	.section	.debug_info		;off: 2117
	.data.w	.Ldw_str_begin+2239
	.data.b	194,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2240
	.data.b	68,83,65,68,67,95,70,73,70,79,84,72,82,69,83,72,79,76,68,95,49,0
	.section	.debug_info		;off: 2128
	.data.w	.Ldw_str_begin+2240
	.data.b	195,1
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2262
	.data.b	68,83,65,68,67,95,70,73,70,79,84,72,82,69,83,72,79,76,68,95,50,0
	.section	.debug_info		;off: 2138
	.data.w	.Ldw_str_begin+2262
	.data.b	196,1
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2284
	.data.b	68,83,65,68,67,95,70,73,70,79,84,72,82,69,83,72,79,76,68,95,51,0
	.section	.debug_info		;off: 2148
	.data.w	.Ldw_str_begin+2284
	.data.b	197,1
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 2306
	.data.b	68,83,65,68,67,95,70,73,70,79,84,72,82,69,83,72,79,76,68,95,52,0
	.section	.debug_info		;off: 2158
	.data.w	.Ldw_str_begin+2306
	.data.b	198,1
	.data.b	5
	.data.b	36
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2328
	.data.b	68,115,97,100,99,95,70,105,102,111,84,104,114,101,115,104,111,108,100,0
	.section	.debug_info		;off: 2169
	.data.w	.Ldw_str_begin+2328
	.data.b	199,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2116

	.data.b	52
	.section	.debug_str		;off: 2348
	.data.b	0
	.section	.debug_info		;off: 2182
	.data.w	.Ldw_str_begin+2348
	.data.b	203,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2349
	.data.b	68,83,65,68,67,95,80,71,65,71,65,73,78,95,48,68,66,0
	.section	.debug_info		;off: 2193
	.data.w	.Ldw_str_begin+2349
	.data.b	204,1
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2367
	.data.b	68,83,65,68,67,95,80,71,65,71,65,73,78,95,54,68,66,0
	.section	.debug_info		;off: 2203
	.data.w	.Ldw_str_begin+2367
	.data.b	205,1
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2385
	.data.b	68,83,65,68,67,95,80,71,65,71,65,73,78,95,49,50,68,66,0
	.section	.debug_info		;off: 2213
	.data.w	.Ldw_str_begin+2385
	.data.b	206,1
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2404
	.data.b	68,115,97,100,99,95,80,103,97,71,97,105,110,0
	.section	.debug_info		;off: 2224
	.data.w	.Ldw_str_begin+2404
	.data.b	207,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2181

	.data.b	52
	.section	.debug_str		;off: 2418
	.data.b	0
	.section	.debug_info		;off: 2237
	.data.w	.Ldw_str_begin+2418
	.data.b	211,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2419
	.data.b	68,83,65,68,67,95,84,73,77,69,83,84,65,77,80,67,76,79,67,75,68,73,86,73,68,69,82,95,49,0
	.section	.debug_info		;off: 2248
	.data.w	.Ldw_str_begin+2419
	.data.b	212,1
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2449
	.data.b	68,83,65,68,67,95,84,73,77,69,83,84,65,77,80,67,76,79,67,75,68,73,86,73,68,69,82,95,50,0
	.section	.debug_info		;off: 2258
	.data.w	.Ldw_str_begin+2449
	.data.b	213,1
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2479
	.data.b	68,83,65,68,67,95,84,73,77,69,83,84,65,77,80,67,76,79,67,75,68,73,86,73,68,69,82,95,52,0
	.section	.debug_info		;off: 2268
	.data.w	.Ldw_str_begin+2479
	.data.b	214,1
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 2509
	.data.b	68,83,65,68,67,95,84,73,77,69,83,84,65,77,80,67,76,79,67,75,68,73,86,73,68,69,82,95,56,0
	.section	.debug_info		;off: 2278
	.data.w	.Ldw_str_begin+2509
	.data.b	215,1
	.data.b	5
	.data.b	36
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2539
	.data.b	68,115,97,100,99,95,84,105,109,101,83,116,97,109,112,67,108,111,99,107,68,105,118,105,100,101,114,0
	.section	.debug_info		;off: 2289
	.data.w	.Ldw_str_begin+2539
	.data.b	216,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2236

	.data.b	52
	.section	.debug_str		;off: 2567
	.data.b	0
	.section	.debug_info		;off: 2302
	.data.w	.Ldw_str_begin+2567
	.data.b	220,1
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2568
	.data.b	68,83,65,68,67,95,77,69,65,78,83,72,73,70,84,76,69,78,71,84,72,95,50,0
	.section	.debug_info		;off: 2313
	.data.w	.Ldw_str_begin+2568
	.data.b	221,1
	.data.b	5
	.data.b	36
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 2592
	.data.b	68,83,65,68,67,95,77,69,65,78,83,72,73,70,84,76,69,78,71,84,72,95,52,0
	.section	.debug_info		;off: 2323
	.data.w	.Ldw_str_begin+2592
	.data.b	222,1
	.data.b	5
	.data.b	36
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 2616
	.data.b	68,83,65,68,67,95,77,69,65,78,83,72,73,70,84,76,69,78,71,84,72,95,56,0
	.section	.debug_info		;off: 2333
	.data.w	.Ldw_str_begin+2616
	.data.b	223,1
	.data.b	5
	.data.b	36
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 2640
	.data.b	68,83,65,68,67,95,77,69,65,78,83,72,73,70,84,76,69,78,71,84,72,95,49,54,0
	.section	.debug_info		;off: 2343
	.data.w	.Ldw_str_begin+2640
	.data.b	224,1
	.data.b	5
	.data.b	36
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 2665
	.data.b	68,83,65,68,67,95,77,69,65,78,83,72,73,70,84,76,69,78,71,84,72,95,51,50,0
	.section	.debug_info		;off: 2353
	.data.w	.Ldw_str_begin+2665
	.data.b	225,1
	.data.b	5
	.data.b	36
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 2690
	.data.b	68,83,65,68,67,95,77,69,65,78,83,72,73,70,84,76,69,78,71,84,72,95,54,52,0
	.section	.debug_info		;off: 2363
	.data.w	.Ldw_str_begin+2690
	.data.b	226,1
	.data.b	5
	.data.b	36
	.data.b	5

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2715
	.data.b	68,115,97,100,99,95,77,101,97,110,83,104,105,102,116,76,101,110,103,116,104,0
	.section	.debug_info		;off: 2374
	.data.w	.Ldw_str_begin+2715
	.data.b	227,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2301

	.data.b	71
	.data.b	235,1
	.data.b	1
	.data.b	36
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2737
	.data.b	112,111,115,105,116,105,118,101,73,110,112,117,116,69,110,97,98,108,101,0
	.section	.debug_info		;off: 2394
	.data.w	.Ldw_str_begin+2737
	.data.b	236,1
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2757
	.data.b	110,101,103,97,116,105,118,101,73,110,112,117,116,69,110,97,98,108,101,0
	.section	.debug_info		;off: 2411
	.data.w	.Ldw_str_begin+2757
	.data.b	237,1
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2777
	.data.b	112,111,115,105,116,105,118,101,73,110,112,117,116,76,105,110,101,0
	.section	.debug_info		;off: 2428
	.data.w	.Ldw_str_begin+2777
	.data.b	238,1
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2795
	.data.b	110,101,103,97,116,105,118,101,73,110,112,117,116,76,105,110,101,0
	.section	.debug_info		;off: 2445
	.data.w	.Ldw_str_begin+2795
	.data.b	239,1
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2813
	.data.b	105,110,112,117,116,80,105,110,0
	.section	.debug_info		;off: 2462
	.data.w	.Ldw_str_begin+2813
	.data.b	240,1
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2822
	.data.b	105,110,112,117,116,77,117,108,116,105,112,108,101,120,101,114,77,111,100,101,0
	.section	.debug_info		;off: 2479
	.data.w	.Ldw_str_begin+2822
	.data.b	241,1
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2843
	.data.b	97,117,116,111,80,111,119,101,114,67,111,110,116,114,111,108,0
	.section	.debug_info		;off: 2496
	.data.w	.Ldw_str_begin+2843
	.data.b	242,1
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2860
	.data.b	112,103,97,71,97,105,110,0
	.section	.debug_info		;off: 2513
	.data.w	.Ldw_str_begin+2860
	.data.b	243,1
	.data.b	19
	.data.b	36
	.data.w	.Ldw_begin+2223
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2868
	.data.b	105,110,112,117,116,77,117,108,116,105,112,108,101,120,101,114,84,114,105,103,103,101,114,77,111,100,101,0
	.section	.debug_info		;off: 2530
	.data.w	.Ldw_str_begin+2868
	.data.b	244,1
	.data.b	39
	.data.b	36
	.data.w	.Ldw_begin+1464
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2896
	.data.b	68,115,97,100,99,95,77,111,100,117,108,97,116,111,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 2548
	.data.w	.Ldw_str_begin+2896
	.data.b	245,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2386

	.data.b	71
	.data.b	251,1
	.data.b	1
	.data.b	36
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2918
	.data.b	114,101,115,117,108,116,68,105,115,112,108,97,121,77,111,100,101,0
	.section	.debug_info		;off: 2568
	.data.w	.Ldw_str_begin+2918
	.data.b	252,1
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2936
	.data.b	116,114,105,103,103,101,114,83,111,117,114,99,101,0
	.section	.debug_info		;off: 2585
	.data.w	.Ldw_str_begin+2936
	.data.b	253,1
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+1631
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 2950
	.data.b	68,115,97,100,99,95,68,101,109,111,100,117,108,97,116,111,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 2603
	.data.w	.Ldw_str_begin+2950
	.data.b	254,1
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2560

	.data.b	71
	.data.b	132,2
	.data.b	1
	.data.b	36
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2974
	.data.b	115,116,97,114,116,0
	.section	.debug_info		;off: 2623
	.data.w	.Ldw_str_begin+2974
	.data.b	133,2
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 2980
	.data.b	109,117,108,116,105,112,108,101,120,101,114,67,111,112,121,69,110,97,98,108,101,0
	.section	.debug_info		;off: 2640
	.data.w	.Ldw_str_begin+2980
	.data.b	134,2
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3002
	.data.b	116,105,109,101,83,116,97,109,112,70,114,101,113,117,101,110,99,121,0
	.section	.debug_info		;off: 2657
	.data.w	.Ldw_str_begin+3002
	.data.b	135,2
	.data.b	11
	.data.b	36
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3021
	.data.b	100,105,118,105,100,101,114,0
	.section	.debug_info		;off: 2674
	.data.w	.Ldw_str_begin+3021
	.data.b	136,2
	.data.b	33
	.data.b	36
	.data.w	.Ldw_begin+2288
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3029
	.data.b	109,111,100,101,0
	.section	.debug_info		;off: 2691
	.data.w	.Ldw_str_begin+3029
	.data.b	137,2
	.data.b	32
	.data.b	36
	.data.w	.Ldw_begin+1690
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3034
	.data.b	68,115,97,100,99,95,84,105,109,101,83,116,97,109,112,67,111,110,102,105,103,0
	.section	.debug_info		;off: 2709
	.data.w	.Ldw_str_begin+3034
	.data.b	138,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2615

	.data.b	71
	.data.b	144,2
	.data.b	1
	.data.b	36
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3056
	.data.b	109,101,97,110,77,111,100,101,0
	.section	.debug_info		;off: 2729
	.data.w	.Ldw_str_begin+3056
	.data.b	145,2
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3065
	.data.b	109,101,97,110,80,111,105,110,116,0
	.section	.debug_info		;off: 2746
	.data.w	.Ldw_str_begin+3065
	.data.b	146,2
	.data.b	11
	.data.b	36
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3075
	.data.b	115,104,105,102,116,76,101,110,103,116,104,0
	.section	.debug_info		;off: 2763
	.data.w	.Ldw_str_begin+3075
	.data.b	147,2
	.data.b	27
	.data.b	36
	.data.w	.Ldw_begin+2373
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3087
	.data.b	68,115,97,100,99,95,77,101,97,110,67,111,110,102,105,103,0
	.section	.debug_info		;off: 2781
	.data.w	.Ldw_str_begin+3087
	.data.b	148,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2721

	.data.b	71
	.data.b	154,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3104
	.data.b	116,104,114,101,115,104,111,108,100,76,111,119,101,114,0
	.section	.debug_info		;off: 2801
	.data.w	.Ldw_str_begin+3104
	.data.b	155,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1178
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3119
	.data.b	116,104,114,101,115,104,111,108,100,85,112,112,101,114,0
	.section	.debug_info		;off: 2818
	.data.w	.Ldw_str_begin+3119
	.data.b	156,2
	.data.b	12
	.data.b	36
	.data.w	.Ldw_begin+1178
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3134
	.data.b	68,115,97,100,99,95,84,104,114,101,115,104,111,108,100,67,111,110,102,105,103,0
	.section	.debug_info		;off: 2836
	.data.w	.Ldw_str_begin+3134
	.data.b	157,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2793

	.data.b	71
	.data.b	163,2
	.data.b	1
	.data.b	36
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3156
	.data.b	99,105,99,70,105,108,116,101,114,69,110,97,98,108,101,0
	.section	.debug_info		;off: 2856
	.data.w	.Ldw_str_begin+3156
	.data.b	164,2
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3172
	.data.b	100,101,99,105,109,97,116,105,111,110,82,97,116,101,48,0
	.section	.debug_info		;off: 2873
	.data.w	.Ldw_str_begin+3172
	.data.b	165,2
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3188
	.data.b	100,101,99,105,109,97,116,105,111,110,82,97,116,101,49,0
	.section	.debug_info		;off: 2890
	.data.w	.Ldw_str_begin+3188
	.data.b	166,2
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3204
	.data.b	102,105,114,48,69,110,97,98,108,101,0
	.section	.debug_info		;off: 2907
	.data.w	.Ldw_str_begin+3204
	.data.b	167,2
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3215
	.data.b	102,105,114,49,69,110,97,98,108,101,0
	.section	.debug_info		;off: 2924
	.data.w	.Ldw_str_begin+3215
	.data.b	168,2
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3226
	.data.b	102,105,114,79,102,102,115,101,116,48,0
	.section	.debug_info		;off: 2941
	.data.w	.Ldw_str_begin+3226
	.data.b	169,2
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3237
	.data.b	99,105,99,70,105,108,116,101,114,83,97,109,112,108,105,110,103,0
	.section	.debug_info		;off: 2958
	.data.w	.Ldw_str_begin+3237
	.data.b	170,2
	.data.b	11
	.data.b	36
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3255
	.data.b	112,97,114,97,108,108,101,108,0
	.section	.debug_info		;off: 2975
	.data.w	.Ldw_str_begin+3255
	.data.b	171,2
	.data.b	32
	.data.b	36
	.data.w	.Ldw_begin+1749
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3264
	.data.b	114,101,113,117,101,115,116,0
	.section	.debug_info		;off: 2992
	.data.w	.Ldw_str_begin+3264
	.data.b	172,2
	.data.b	26
	.data.b	36
	.data.w	.Ldw_begin+1813
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3272
	.data.b	99,111,110,100,105,116,105,111,110,0
	.section	.debug_info		;off: 3009
	.data.w	.Ldw_str_begin+3272
	.data.b	173,2
	.data.b	30
	.data.b	36
	.data.w	.Ldw_begin+1868
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3282
	.data.b	102,105,114,79,102,102,115,101,116,49,0
	.section	.debug_info		;off: 3026
	.data.w	.Ldw_str_begin+3282
	.data.b	174,2
	.data.b	21
	.data.b	36
	.data.w	.Ldw_begin+1933
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3293
	.data.b	111,102,102,115,101,116,67,111,109,112,101,110,115,97,116,105,111,110,0
	.section	.debug_info		;off: 3043
	.data.w	.Ldw_str_begin+3293
	.data.b	175,2
	.data.b	36
	.data.b	36
	.data.w	.Ldw_begin+2038
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3312
	.data.b	68,115,97,100,99,95,77,97,105,110,70,105,108,116,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3061
	.data.w	.Ldw_str_begin+3312
	.data.b	176,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+2848

	.data.b	71
	.data.b	182,2
	.data.b	1
	.data.b	36
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3335
	.data.b	114,101,113,117,101,115,116,0
	.section	.debug_info		;off: 3081
	.data.w	.Ldw_str_begin+3335
	.data.b	183,2
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3343
	.data.b	99,105,99,70,105,108,116,101,114,69,110,97,98,108,101,0
	.section	.debug_info		;off: 3098
	.data.w	.Ldw_str_begin+3343
	.data.b	184,2
	.data.b	13
	.data.b	36
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3359
	.data.b	97,117,120,105,108,105,97,114,121,67,105,99,70,105,108,116,101,114,83,97,109,112,108,105,110,103,0
	.section	.debug_info		;off: 3115
	.data.w	.Ldw_str_begin+3359
	.data.b	185,2
	.data.b	11
	.data.b	36
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3386
	.data.b	112,97,114,97,108,108,101,108,0
	.section	.debug_info		;off: 3132
	.data.w	.Ldw_str_begin+3386
	.data.b	186,2
	.data.b	32
	.data.b	36
	.data.w	.Ldw_begin+1749
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3395
	.data.b	68,115,97,100,99,95,65,117,120,105,108,105,97,114,121,70,105,108,116,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3150
	.data.w	.Ldw_str_begin+3395
	.data.b	187,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+3073

	.data.b	71
	.data.b	193,2
	.data.b	1
	.data.b	36
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3423
	.data.b	102,105,102,111,84,104,114,101,115,104,111,108,100,0
	.section	.debug_info		;off: 3170
	.data.w	.Ldw_str_begin+3423
	.data.b	194,2
	.data.b	25
	.data.b	36
	.data.w	.Ldw_begin+2168
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3437
	.data.b	68,115,97,100,99,95,70,105,102,111,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3188
	.data.w	.Ldw_str_begin+3437
	.data.b	195,2
	.data.b	3
	.data.b	36
	.data.w	.Ldw_begin+3162

	.data.b	52
	.section	.debug_str		;off: 3454
	.data.b	0
	.section	.debug_info		;off: 3201
	.data.w	.Ldw_str_begin+3454
	.data.b	112
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 3455
	.data.b	68,83,65,68,67,95,77,65,73,78,67,72,65,78,78,69,76,0
	.section	.debug_info		;off: 3211
	.data.w	.Ldw_str_begin+3455
	.data.b	113
	.data.b	5
	.data.b	34
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 3473
	.data.b	68,83,65,68,67,95,65,85,88,73,76,73,65,82,89,67,72,65,78,78,69,76,0
	.section	.debug_info		;off: 3220
	.data.w	.Ldw_str_begin+3473
	.data.b	114
	.data.b	5
	.data.b	34
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3496
	.data.b	68,115,97,100,99,95,67,104,97,110,110,101,108,83,101,108,101,99,116,0
	.section	.debug_info		;off: 3230
	.data.w	.Ldw_str_begin+3496
	.data.b	115
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+3200

	.data.b	52
	.section	.debug_str		;off: 3516
	.data.b	0
	.section	.debug_info		;off: 3242
	.data.w	.Ldw_str_begin+3516
	.data.b	152,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 3517
	.data.b	68,83,65,68,67,95,66,73,65,83,86,79,76,84,65,71,69,95,48,0
	.section	.debug_info		;off: 3253
	.data.w	.Ldw_str_begin+3517
	.data.b	153,1
	.data.b	5
	.data.b	34
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 3537
	.data.b	68,83,65,68,67,95,66,73,65,83,86,79,76,84,65,71,69,95,49,0
	.section	.debug_info		;off: 3263
	.data.w	.Ldw_str_begin+3537
	.data.b	154,1
	.data.b	5
	.data.b	34
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 3557
	.data.b	68,83,65,68,67,95,66,73,65,83,86,79,76,84,65,71,69,95,50,0
	.section	.debug_info		;off: 3273
	.data.w	.Ldw_str_begin+3557
	.data.b	155,1
	.data.b	5
	.data.b	34
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 3577
	.data.b	68,83,65,68,67,95,66,73,65,83,86,79,76,84,65,71,69,95,51,0
	.section	.debug_info		;off: 3283
	.data.w	.Ldw_str_begin+3577
	.data.b	156,1
	.data.b	5
	.data.b	34
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3597
	.data.b	68,115,97,100,99,95,66,105,97,115,86,111,108,116,97,103,101,83,101,108,101,99,116,0
	.section	.debug_info		;off: 3294
	.data.w	.Ldw_str_begin+3597
	.data.b	157,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+3241

	.data.b	71
	.data.b	180,1
	.data.b	1
	.data.b	34
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3621
	.data.b	112,77,111,100,117,108,97,116,111,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3314
	.data.w	.Ldw_str_begin+3621
	.data.b	181,1
	.data.b	34
	.data.b	34
	.data.w	.Ldw_begin+185
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3638
	.data.b	112,68,101,109,111,100,117,108,97,116,111,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3331
	.data.w	.Ldw_str_begin+3638
	.data.b	182,1
	.data.b	36
	.data.b	34
	.data.w	.Ldw_begin+195
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3657
	.data.b	112,84,105,109,101,83,116,97,109,112,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3348
	.data.w	.Ldw_str_begin+3657
	.data.b	183,1
	.data.b	34
	.data.b	34
	.data.w	.Ldw_begin+205
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3674
	.data.b	112,84,104,114,101,115,104,111,108,100,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3365
	.data.w	.Ldw_str_begin+3674
	.data.b	184,1
	.data.b	34
	.data.b	34
	.data.w	.Ldw_begin+215
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3691
	.data.b	112,77,97,105,110,70,105,108,116,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3382
	.data.w	.Ldw_str_begin+3691
	.data.b	185,1
	.data.b	35
	.data.b	34
	.data.w	.Ldw_begin+225
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3709
	.data.b	112,65,117,120,105,108,105,97,114,121,70,105,108,116,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3399
	.data.w	.Ldw_str_begin+3709
	.data.b	186,1
	.data.b	40
	.data.b	34
	.data.w	.Ldw_begin+235
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3732
	.data.b	112,77,101,97,110,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3416
	.data.w	.Ldw_str_begin+3732
	.data.b	187,1
	.data.b	29
	.data.b	34
	.data.w	.Ldw_begin+245
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3744
	.data.b	112,70,105,102,111,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3433
	.data.w	.Ldw_str_begin+3744
	.data.b	188,1
	.data.b	29
	.data.b	34
	.data.w	.Ldw_begin+255
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3756
	.data.b	68,115,97,100,99,95,77,111,100,117,108,101,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3451
	.data.w	.Ldw_str_begin+3756
	.data.b	189,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+3306

	.data.b	71
	.data.b	195,1
	.data.b	1
	.data.b	34
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3775
	.data.b	101,120,99,105,116,97,116,105,111,110,69,110,97,98,108,101,0
	.section	.debug_info		;off: 3471
	.data.w	.Ldw_str_begin+3775
	.data.b	196,1
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3792
	.data.b	112,99,109,69,110,97,98,108,101,0
	.section	.debug_info		;off: 3488
	.data.w	.Ldw_str_begin+3792
	.data.b	197,1
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3802
	.data.b	99,97,114,114,105,101,114,87,97,118,101,0
	.section	.debug_info		;off: 3505
	.data.w	.Ldw_str_begin+3802
	.data.b	198,1
	.data.b	13
	.data.b	34
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3814
	.data.b	109,111,100,101,0
	.section	.debug_info		;off: 3522
	.data.w	.Ldw_str_begin+3814
	.data.b	199,1
	.data.b	20
	.data.b	34
	.data.w	.Ldw_begin+2103
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3819
	.data.b	68,115,97,100,99,95,67,97,114,114,105,101,114,87,97,118,101,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3540
	.data.w	.Ldw_str_begin+3819
	.data.b	200,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+3463

	.data.b	71
	.data.b	215,1
	.data.b	1
	.data.b	34
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3843
	.data.b	100,99,79,102,102,115,101,116,0
	.section	.debug_info		;off: 3560
	.data.w	.Ldw_str_begin+3843
	.data.b	216,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1178
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 3852
	.data.b	103,99,79,102,102,115,101,116,0
	.section	.debug_info		;off: 3577
	.data.w	.Ldw_str_begin+3852
	.data.b	217,1
	.data.b	12
	.data.b	34
	.data.w	.Ldw_begin+1178
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 3861
	.data.b	68,115,97,100,99,95,67,111,109,112,101,110,115,97,116,105,111,110,67,111,110,102,105,103,0
	.section	.debug_info		;off: 3595
	.data.w	.Ldw_str_begin+3861
	.data.b	218,1
	.data.b	3
	.data.b	34
	.data.w	.Ldw_begin+3552

	.data.b	45
	.section	.debug_str		;off: 3886
	.data.b	68,115,97,100,99,95,67,104,97,110,110,101,108,84,121,112,101,0
	.section	.debug_info		;off: 3608
	.data.w	.Ldw_str_begin+3886
	.data.b	49
	.data.b	15
	.data.b	10
	.data.w	.Ldw_begin+1154

	.data.b	45
	.section	.debug_str		;off: 3904
	.data.b	68,115,97,100,99,95,82,101,115,117,108,116,84,121,112,101,0
	.section	.debug_info		;off: 3620
	.data.w	.Ldw_str_begin+3904
	.data.b	51
	.data.b	16
	.data.b	10
	.data.w	.Ldw_begin+1166

	.data.b	45
	.section	.debug_str		;off: 3921
	.data.b	68,115,97,100,99,95,84,105,109,101,115,116,97,109,112,84,121,112,101,0
	.section	.debug_info		;off: 3632
	.data.w	.Ldw_str_begin+3921
	.data.b	53
	.data.b	16
	.data.b	10
	.data.w	.Ldw_begin+1178

	.data.b	45
	.section	.debug_str		;off: 3941
	.data.b	68,115,97,100,99,95,78,117,109,83,97,109,112,108,101,84,121,112,101,0
	.section	.debug_info		;off: 3644
	.data.w	.Ldw_str_begin+3941
	.data.b	55
	.data.b	15
	.data.b	10
	.data.w	.Ldw_begin+1154

	.data.b	45
	.section	.debug_str		;off: 3961
	.data.b	68,115,97,100,99,95,72,87,85,110,105,116,84,121,112,101,0
	.section	.debug_info		;off: 3656
	.data.w	.Ldw_str_begin+3961
	.data.b	57
	.data.b	27
	.data.b	10
	.data.w	.Ldw_begin+3607

	.data.b	52
	.section	.debug_str		;off: 3978
	.data.b	0
	.section	.debug_info		;off: 3668
	.data.w	.Ldw_str_begin+3978
	.data.b	77
	.data.b	1
	.data.b	10
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 3979
	.data.b	68,83,65,68,67,95,73,68,76,69,0
	.section	.debug_info		;off: 3678
	.data.w	.Ldw_str_begin+3979
	.data.b	80
	.data.b	5
	.data.b	10
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 3990
	.data.b	68,83,65,68,67,95,66,85,83,89,0
	.section	.debug_info		;off: 3687
	.data.w	.Ldw_str_begin+3990
	.data.b	83
	.data.b	5
	.data.b	10
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4001
	.data.b	68,83,65,68,67,95,67,79,77,80,76,69,84,69,68,0
	.section	.debug_info		;off: 3696
	.data.w	.Ldw_str_begin+4001
	.data.b	86
	.data.b	5
	.data.b	10
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 4017
	.data.b	68,83,65,68,67,95,83,84,82,69,65,77,95,67,79,77,80,76,69,84,69,68,0
	.section	.debug_info		;off: 3705
	.data.w	.Ldw_str_begin+4017
	.data.b	90
	.data.b	5
	.data.b	10
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4040
	.data.b	68,115,97,100,99,95,83,116,97,116,117,115,84,121,112,101,0
	.section	.debug_info		;off: 3715
	.data.w	.Ldw_str_begin+4040
	.data.b	91
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+3667

	.data.b	52
	.section	.debug_str		;off: 4057
	.data.b	0
	.section	.debug_info		;off: 3727
	.data.w	.Ldw_str_begin+4057
	.data.b	95
	.data.b	1
	.data.b	10
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4058
	.data.b	68,83,65,68,67,95,65,67,67,69,83,83,95,77,79,68,69,95,83,73,78,71,76,69,0
	.section	.debug_info		;off: 3737
	.data.w	.Ldw_str_begin+4058
	.data.b	97
	.data.b	5
	.data.b	10
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 4083
	.data.b	68,83,65,68,67,95,65,67,67,69,83,83,95,77,79,68,69,95,83,84,82,69,65,77,73,78,71,0
	.section	.debug_info		;off: 3746
	.data.w	.Ldw_str_begin+4083
	.data.b	99
	.data.b	5
	.data.b	10
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4111
	.data.b	68,115,97,100,99,95,65,99,99,101,115,115,84,121,112,101,0
	.section	.debug_info		;off: 3756
	.data.w	.Ldw_str_begin+4111
	.data.b	100
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+3726

	.data.b	52
	.section	.debug_str		;off: 4128
	.data.b	0
	.section	.debug_info		;off: 3768
	.data.w	.Ldw_str_begin+4128
	.data.b	104
	.data.b	1
	.data.b	10
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4129
	.data.b	68,83,65,68,67,95,83,84,82,69,65,77,95,66,85,70,70,69,82,95,76,69,65,78,69,82,0
	.section	.debug_info		;off: 3778
	.data.w	.Ldw_str_begin+4129
	.data.b	107
	.data.b	5
	.data.b	10
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 4156
	.data.b	68,83,65,68,67,95,83,84,82,69,65,77,95,66,85,70,70,69,82,95,67,73,82,67,85,76,65,82,0
	.section	.debug_info		;off: 3787
	.data.w	.Ldw_str_begin+4156
	.data.b	110
	.data.b	5
	.data.b	10
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4185
	.data.b	68,115,97,100,99,95,83,116,114,101,97,109,66,117,102,84,121,112,101,0
	.section	.debug_info		;off: 3797
	.data.w	.Ldw_str_begin+4185
	.data.b	111
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+3767

	.data.b	52
	.section	.debug_str		;off: 4205
	.data.b	0
	.section	.debug_info		;off: 3809
	.data.w	.Ldw_str_begin+4205
	.data.b	115
	.data.b	1
	.data.b	10
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4206
	.data.b	68,83,65,68,67,95,82,69,83,85,76,84,95,65,66,79,86,69,95,85,80,80,69,82,95,76,73,77,73,84,0
	.section	.debug_info		;off: 3819
	.data.w	.Ldw_str_begin+4206
	.data.b	117
	.data.b	5
	.data.b	10
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 4237
	.data.b	68,83,65,68,67,95,82,69,83,85,76,84,95,66,69,76,79,87,95,76,79,87,69,82,95,76,73,77,73,84,0
	.section	.debug_info		;off: 3828
	.data.w	.Ldw_str_begin+4237
	.data.b	119
	.data.b	5
	.data.b	10
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4268
	.data.b	68,115,97,100,99,95,76,105,109,105,116,67,104,101,99,107,105,110,103,69,118,101,110,116,84,121,112,101,0
	.section	.debug_info		;off: 3838
	.data.w	.Ldw_str_begin+4268
	.data.b	120
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+3808

	.data.b	52
	.section	.debug_str		;off: 4297
	.data.b	0
	.section	.debug_info		;off: 3850
	.data.w	.Ldw_str_begin+4297
	.data.b	124
	.data.b	1
	.data.b	10
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4298
	.data.b	68,83,65,68,67,95,67,79,78,86,95,67,72,65,78,78,69,76,95,77,65,73,78,0
	.section	.debug_info		;off: 3860
	.data.w	.Ldw_str_begin+4298
	.data.b	126
	.data.b	5
	.data.b	10
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 4322
	.data.b	68,83,65,68,67,95,67,79,78,86,95,67,72,65,78,78,69,76,95,65,85,88,0
	.section	.debug_info		;off: 3869
	.data.w	.Ldw_str_begin+4322
	.data.b	128,1
	.data.b	5
	.data.b	10
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4345
	.data.b	68,115,97,100,99,95,67,111,110,118,67,104,97,110,110,101,108,84,121,112,101,0
	.section	.debug_info		;off: 3880
	.data.w	.Ldw_str_begin+4345
	.data.b	129,1
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+3849

	.data.b	71
	.data.b	139,1
	.data.b	1
	.data.b	10
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4367
	.data.b	67,111,114,101,67,104,97,110,110,101,108,73,100,120,0
	.section	.debug_info		;off: 3900
	.data.w	.Ldw_str_begin+4367
	.data.b	141,1
	.data.b	40
	.data.b	10
	.data.w	.Ldw_begin+3607
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4382
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 3917
	.data.w	.Ldw_str_begin+4382
	.data.b	143,1
	.data.b	40
	.data.b	10
	.data.w	.Ldw_begin+3655
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4391
	.data.b	67,104,97,110,110,101,108,77,97,112,67,111,114,101,73,100,0
	.section	.debug_info		;off: 3934
	.data.w	.Ldw_str_begin+4391
	.data.b	145,1
	.data.b	40
	.data.b	10
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4408
	.data.b	68,115,97,100,99,95,67,104,97,110,110,101,108,67,111,114,101,77,97,112,84,121,112,101,0
	.section	.debug_info		;off: 3952
	.data.w	.Ldw_str_begin+4408
	.data.b	146,1
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+3892

	.data.b	71
	.data.b	177,1
	.data.b	1
	.data.b	10
	.data.b	44
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4433
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 3972
	.data.w	.Ldw_str_begin+4433
	.data.b	179,1
	.data.b	42
	.data.b	10
	.data.w	.Ldw_begin+3655
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4442
	.data.b	76,103,99,67,104,73,100,0
	.section	.debug_info		;off: 3989
	.data.w	.Ldw_str_begin+4442
	.data.b	181,1
	.data.b	42
	.data.b	10
	.data.w	.Ldw_begin+3607
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4450
	.data.b	73,115,77,100,108,68,105,116,104,101,114,105,110,103,69,110,0
	.section	.debug_info		;off: 4006
	.data.w	.Ldw_str_begin+4450
	.data.b	183,1
	.data.b	42
	.data.b	10
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4467
	.data.b	73,115,67,111,109,109,111,110,77,111,100,101,86,111,108,116,69,110,0
	.section	.debug_info		;off: 4023
	.data.w	.Ldw_str_begin+4467
	.data.b	185,1
	.data.b	42
	.data.b	10
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4486
	.data.b	67,111,109,109,111,110,77,111,100,101,86,111,108,116,76,101,118,101,108,0
	.section	.debug_info		;off: 4040
	.data.w	.Ldw_str_begin+4486
	.data.b	187,1
	.data.b	42
	.data.b	10
	.data.w	.Ldw_begin+3293
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4506
	.data.b	73,115,65,117,120,67,104,82,115,108,116,65,99,113,69,110,0
	.section	.debug_info		;off: 4057
	.data.w	.Ldw_str_begin+4506
	.data.b	190,1
	.data.b	42
	.data.b	10
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4523
	.data.b	84,105,109,101,115,116,97,109,112,69,110,0
	.section	.debug_info		;off: 4074
	.data.w	.Ldw_str_begin+4523
	.data.b	194,1
	.data.b	42
	.data.b	10
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	9
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4535
	.data.b	82,115,108,116,72,108,100,77,116,104,100,0
	.section	.debug_info		;off: 4091
	.data.w	.Ldw_str_begin+4535
	.data.b	197,1
	.data.b	42
	.data.b	10
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	10
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4547
	.data.b	78,117,109,83,97,109,112,108,101,115,0
	.section	.debug_info		;off: 4108
	.data.w	.Ldw_str_begin+4547
	.data.b	199,1
	.data.b	42
	.data.b	10
	.data.w	.Ldw_begin+3643
	.data.b	2,35
	.data.b	11
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4558
	.data.b	82,115,108,116,65,99,99,101,115,115,77,111,100,0
	.section	.debug_info		;off: 4125
	.data.w	.Ldw_str_begin+4558
	.data.b	201,1
	.data.b	42
	.data.b	10
	.data.w	.Ldw_begin+3755
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4572
	.data.b	83,116,114,101,97,109,66,117,102,77,111,100,0
	.section	.debug_info		;off: 4142
	.data.w	.Ldw_str_begin+4572
	.data.b	203,1
	.data.b	42
	.data.b	10
	.data.w	.Ldw_begin+3796
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4585
	.data.b	78,101,119,82,115,108,116,78,111,116,105,102,70,117,110,99,80,116,114,0
	.section	.debug_info		;off: 4159
	.data.w	.Ldw_str_begin+4585
	.data.b	206,1
	.data.b	12
	.data.b	10
	.data.w	.Ldw_begin+269
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4605
	.data.b	66,117,102,70,117,108,108,78,111,116,105,102,70,117,110,99,80,116,114,0
	.section	.debug_info		;off: 4176
	.data.w	.Ldw_str_begin+4605
	.data.b	208,1
	.data.b	12
	.data.b	10
	.data.w	.Ldw_begin+277
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4625
	.data.b	76,105,109,105,116,67,104,107,78,111,116,105,102,70,117,110,99,80,116,114,0
	.section	.debug_info		;off: 4193
	.data.w	.Ldw_str_begin+4625
	.data.b	210,1
	.data.b	12
	.data.b	10
	.data.w	.Ldw_begin+297
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4646
	.data.b	76,105,109,105,116,67,104,101,99,107,69,118,116,66,105,116,115,0
	.section	.debug_info		;off: 4210
	.data.w	.Ldw_str_begin+4646
	.data.b	214,1
	.data.b	42
	.data.b	10
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4664
	.data.b	67,97,108,105,98,67,111,109,112,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 4227
	.data.w	.Ldw_str_begin+4664
	.data.b	217,1
	.data.b	43
	.data.b	10
	.data.w	.Ldw_begin+307
	.data.b	2,35
	.data.b	36
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4683
	.data.b	72,119,67,102,103,80,116,114,0
	.section	.debug_info		;off: 4244
	.data.w	.Ldw_str_begin+4683
	.data.b	219,1
	.data.b	43
	.data.b	10
	.data.w	.Ldw_begin+317
	.data.b	2,35
	.data.b	40
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4692
	.data.b	68,115,97,100,99,95,67,104,97,110,110,101,108,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 4262
	.data.w	.Ldw_str_begin+4692
	.data.b	220,1
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+3964

	.data.b	71
	.data.b	226,1
	.data.b	1
	.data.b	10
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4716
	.data.b	77,97,120,67,111,114,101,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 4282
	.data.w	.Ldw_str_begin+4716
	.data.b	228,1
	.data.b	42
	.data.b	10
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4731
	.data.b	67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 4299
	.data.w	.Ldw_str_begin+4731
	.data.b	230,1
	.data.b	43
	.data.b	10
	.data.w	.Ldw_begin+327
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4748
	.data.b	68,115,97,100,99,95,67,111,114,101,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 4317
	.data.w	.Ldw_str_begin+4748
	.data.b	231,1
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+4274

	.data.b	71
	.data.b	237,1
	.data.b	1
	.data.b	10
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4769
	.data.b	72,87,85,110,105,116,69,110,66,105,116,115,0
	.section	.debug_info		;off: 4337
	.data.w	.Ldw_str_begin+4769
	.data.b	239,1
	.data.b	42
	.data.b	10
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4782
	.data.b	65,117,120,70,108,116,114,72,119,85,110,105,116,69,110,66,105,116,115,0
	.section	.debug_info		;off: 4354
	.data.w	.Ldw_str_begin+4782
	.data.b	242,1
	.data.b	42
	.data.b	10
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4802
	.data.b	67,97,114,114,105,101,114,67,102,103,80,116,114,0
	.section	.debug_info		;off: 4371
	.data.w	.Ldw_str_begin+4802
	.data.b	245,1
	.data.b	43
	.data.b	10
	.data.w	.Ldw_begin+337
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4816
	.data.b	68,115,97,100,99,95,71,108,111,98,97,108,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 4389
	.data.w	.Ldw_str_begin+4816
	.data.b	246,1
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+4329

	.data.b	71
	.data.b	251,1
	.data.b	1
	.data.b	10
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4839
	.data.b	67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 4409
	.data.w	.Ldw_str_begin+4839
	.data.b	253,1
	.data.b	43
	.data.b	10
	.data.w	.Ldw_begin+352
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4853
	.data.b	71,108,111,98,97,108,67,102,103,80,116,114,0
	.section	.debug_info		;off: 4426
	.data.w	.Ldw_str_begin+4853
	.data.b	255,1
	.data.b	43
	.data.b	10
	.data.w	.Ldw_begin+373
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4866
	.data.b	67,104,97,110,110,101,108,77,97,112,80,116,114,0
	.section	.debug_info		;off: 4443
	.data.w	.Ldw_str_begin+4866
	.data.b	129,2
	.data.b	43
	.data.b	10
	.data.w	.Ldw_begin+383
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4880
	.data.b	72,119,85,110,105,116,84,111,67,104,97,110,110,101,108,73,100,80,116,114,0
	.section	.debug_info		;off: 4460
	.data.w	.Ldw_str_begin+4880
	.data.b	131,2
	.data.b	43
	.data.b	10
	.data.w	.Ldw_begin+393
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4901
	.data.b	68,115,97,100,99,49,73,110,112,117,116,80,105,110,0
	.section	.debug_info		;off: 4477
	.data.w	.Ldw_str_begin+4901
	.data.b	133,2
	.data.b	42
	.data.b	10
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4916
	.data.b	68,115,97,100,99,95,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 4495
	.data.w	.Ldw_str_begin+4916
	.data.b	135,2
	.data.b	3
	.data.b	10
	.data.w	.Ldw_begin+4401

	.data.b	45
	.section	.debug_str		;off: 4933
	.data.b	73,110,116,99,95,73,110,116,83,114,99,84,121,112,101,0
	.section	.debug_info		;off: 4508
	.data.w	.Ldw_str_begin+4933
	.data.b	48
	.data.b	16
	.data.b	42
	.data.w	.Ldw_begin+1178

	.data.b	52
	.section	.debug_str		;off: 4949
	.data.b	0
	.section	.debug_info		;off: 4520
	.data.w	.Ldw_str_begin+4949
	.data.b	94
	.data.b	1
	.data.b	48
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 4950
	.data.b	68,69,77,79,95,73,68,76,69,0
	.section	.debug_info		;off: 4530
	.data.w	.Ldw_str_begin+4950
	.data.b	95
	.data.b	5
	.data.b	48
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 4960
	.data.b	68,69,77,79,95,83,84,65,82,84,69,68,0
	.section	.debug_info		;off: 4539
	.data.w	.Ldw_str_begin+4960
	.data.b	96
	.data.b	5
	.data.b	48
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 4973
	.data.b	68,101,109,111,95,83,116,97,114,116,117,112,84,121,112,101,0
	.section	.debug_info		;off: 4549
	.data.w	.Ldw_str_begin+4973
	.data.b	97
	.data.b	3
	.data.b	48
	.data.w	.Ldw_begin+4519

	.data.b	71
	.data.b	119
	.data.b	1
	.data.b	48
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 4990
	.data.b	69,120,101,67,109,100,67,111,114,101,0
	.section	.debug_info		;off: 4567
	.data.w	.Ldw_str_begin+4990
	.data.b	121
	.data.b	22
	.data.b	48
	.data.w	.Ldw_begin+1405
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5001
	.data.b	69,120,101,67,109,100,73,100,0
	.section	.debug_info		;off: 4583
	.data.w	.Ldw_str_begin+5001
	.data.b	123
	.data.b	22
	.data.b	48
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5010
	.data.b	68,101,109,111,83,116,97,114,116,117,112,70,108,103,0
	.section	.debug_info		;off: 4599
	.data.w	.Ldw_str_begin+5010
	.data.b	125
	.data.b	22
	.data.b	48
	.data.w	.Ldw_begin+4548
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5025
	.data.b	68,101,109,111,95,67,111,114,101,69,120,101,84,121,112,101,0
	.section	.debug_info		;off: 4616
	.data.w	.Ldw_str_begin+5025
	.data.b	126
	.data.b	3
	.data.b	48
	.data.w	.Ldw_begin+408

	.data.b	52
	.section	.debug_str		;off: 5042
	.data.b	0
	.section	.debug_info		;off: 4628
	.data.w	.Ldw_str_begin+5042
	.data.b	150,1
	.data.b	1
	.data.b	69
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5043
	.data.b	71,84,77,95,73,82,81,77,79,68,69,95,76,69,86,69,76,0
	.section	.debug_info		;off: 4639
	.data.w	.Ldw_str_begin+5043
	.data.b	151,1
	.data.b	5
	.data.b	69
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5061
	.data.b	71,84,77,95,73,82,81,77,79,68,69,95,80,85,76,83,69,0
	.section	.debug_info		;off: 4649
	.data.w	.Ldw_str_begin+5061
	.data.b	152,1
	.data.b	5
	.data.b	69
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5079
	.data.b	71,84,77,95,73,82,81,77,79,68,69,95,80,85,76,83,69,78,79,84,73,70,89,0
	.section	.debug_info		;off: 4659
	.data.w	.Ldw_str_begin+5079
	.data.b	153,1
	.data.b	5
	.data.b	69
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 5103
	.data.b	71,84,77,95,73,82,81,77,79,68,69,95,83,73,78,71,76,69,80,85,76,83,69,0
	.section	.debug_info		;off: 4669
	.data.w	.Ldw_str_begin+5103
	.data.b	154,1
	.data.b	5
	.data.b	69
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5127
	.data.b	71,116,109,95,73,114,113,77,111,100,101,0
	.section	.debug_info		;off: 4680
	.data.w	.Ldw_str_begin+5127
	.data.b	155,1
	.data.b	3
	.data.b	69
	.data.w	.Ldw_begin+4627

	.data.b	52
	.section	.debug_str		;off: 5139
	.data.b	0
	.section	.debug_info		;off: 4693
	.data.w	.Ldw_str_begin+5139
	.data.b	159,1
	.data.b	1
	.data.b	69
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5140
	.data.b	71,84,77,95,83,73,71,78,65,76,83,84,65,84,69,95,76,79,87,0
	.section	.debug_info		;off: 4704
	.data.w	.Ldw_str_begin+5140
	.data.b	160,1
	.data.b	5
	.data.b	69
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5160
	.data.b	71,84,77,95,83,73,71,78,65,76,83,84,65,84,69,95,72,73,71,72,0
	.section	.debug_info		;off: 4714
	.data.w	.Ldw_str_begin+5160
	.data.b	161,1
	.data.b	5
	.data.b	69
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5181
	.data.b	71,116,109,95,83,105,103,110,97,108,83,116,97,116,101,0
	.section	.debug_info		;off: 4725
	.data.w	.Ldw_str_begin+5181
	.data.b	162,1
	.data.b	3
	.data.b	69
	.data.w	.Ldw_begin+4692

	.data.b	52
	.section	.debug_str		;off: 5197
	.data.b	0
	.section	.debug_info		;off: 4738
	.data.w	.Ldw_str_begin+5197
	.data.b	166,1
	.data.b	1
	.data.b	69
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5198
	.data.b	71,84,77,95,79,77,95,73,82,81,84,89,80,69,95,78,79,78,69,0
	.section	.debug_info		;off: 4749
	.data.w	.Ldw_str_begin+5198
	.data.b	167,1
	.data.b	5
	.data.b	69
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5218
	.data.b	71,84,77,95,79,77,95,73,82,81,84,89,80,69,95,67,67,85,48,0
	.section	.debug_info		;off: 4759
	.data.w	.Ldw_str_begin+5218
	.data.b	168,1
	.data.b	5
	.data.b	69
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5238
	.data.b	71,84,77,95,79,77,95,73,82,81,84,89,80,69,95,67,67,85,49,0
	.section	.debug_info		;off: 4769
	.data.w	.Ldw_str_begin+5238
	.data.b	169,1
	.data.b	5
	.data.b	69
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 5258
	.data.b	71,84,77,95,79,77,95,73,82,81,84,89,80,69,95,65,76,76,0
	.section	.debug_info		;off: 4779
	.data.w	.Ldw_str_begin+5258
	.data.b	170,1
	.data.b	5
	.data.b	69
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5277
	.data.b	71,116,109,95,79,109,95,73,114,113,84,121,112,101,0
	.section	.debug_info		;off: 4790
	.data.w	.Ldw_str_begin+5277
	.data.b	171,1
	.data.b	3
	.data.b	69
	.data.w	.Ldw_begin+4737

	.data.b	71
	.data.b	185,1
	.data.b	1
	.data.b	69
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5292
	.data.b	109,111,100,117,108,101,0
	.section	.debug_info		;off: 4810
	.data.w	.Ldw_str_begin+5292
	.data.b	186,1
	.data.b	14
	.data.b	69
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5299
	.data.b	109,111,100,117,108,101,73,110,100,101,120,0
	.section	.debug_info		;off: 4827
	.data.w	.Ldw_str_begin+5299
	.data.b	187,1
	.data.b	14
	.data.b	69
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5311
	.data.b	103,114,111,117,112,0
	.section	.debug_info		;off: 4844
	.data.w	.Ldw_str_begin+5311
	.data.b	188,1
	.data.b	14
	.data.b	69
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5317
	.data.b	99,104,97,110,110,101,108,0
	.section	.debug_info		;off: 4861
	.data.w	.Ldw_str_begin+5317
	.data.b	189,1
	.data.b	14
	.data.b	69
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5325
	.data.b	71,116,109,95,79,117,116,112,117,116,95,68,114,105,118,101,114,0
	.section	.debug_info		;off: 4879
	.data.w	.Ldw_str_begin+5325
	.data.b	190,1
	.data.b	3
	.data.b	69
	.data.w	.Ldw_begin+4802

	.data.b	52
	.section	.debug_str		;off: 5343
	.data.b	0
	.section	.debug_info		;off: 4892
	.data.w	.Ldw_str_begin+5343
	.data.b	89
	.data.b	1
	.data.b	67
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5344
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,70,88,67,76,75,48,0
	.section	.debug_info		;off: 4902
	.data.w	.Ldw_str_begin+5344
	.data.b	90
	.data.b	5
	.data.b	67
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5368
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,70,88,67,76,75,49,0
	.section	.debug_info		;off: 4911
	.data.w	.Ldw_str_begin+5368
	.data.b	91
	.data.b	5
	.data.b	67
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5392
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,70,88,67,76,75,50,0
	.section	.debug_info		;off: 4920
	.data.w	.Ldw_str_begin+5392
	.data.b	92
	.data.b	5
	.data.b	67
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 5416
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,70,88,67,76,75,51,0
	.section	.debug_info		;off: 4929
	.data.w	.Ldw_str_begin+5416
	.data.b	93
	.data.b	5
	.data.b	67
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 5440
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,70,88,67,76,75,52,0
	.section	.debug_info		;off: 4938
	.data.w	.Ldw_str_begin+5440
	.data.b	94
	.data.b	5
	.data.b	67
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 5464
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,67,76,75,48,0
	.section	.debug_info		;off: 4947
	.data.w	.Ldw_str_begin+5464
	.data.b	95
	.data.b	5
	.data.b	67
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5486
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,67,76,75,49,0
	.section	.debug_info		;off: 4956
	.data.w	.Ldw_str_begin+5486
	.data.b	96
	.data.b	5
	.data.b	67
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5508
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,67,76,75,50,0
	.section	.debug_info		;off: 4965
	.data.w	.Ldw_str_begin+5508
	.data.b	97
	.data.b	5
	.data.b	67
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 5530
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,67,76,75,51,0
	.section	.debug_info		;off: 4974
	.data.w	.Ldw_str_begin+5530
	.data.b	98
	.data.b	5
	.data.b	67
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 5552
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,67,76,75,52,0
	.section	.debug_info		;off: 4983
	.data.w	.Ldw_str_begin+5552
	.data.b	99
	.data.b	5
	.data.b	67
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 5574
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,67,76,75,53,0
	.section	.debug_info		;off: 4992
	.data.w	.Ldw_str_begin+5574
	.data.b	100
	.data.b	5
	.data.b	67
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 5596
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,67,76,75,54,0
	.section	.debug_info		;off: 5001
	.data.w	.Ldw_str_begin+5596
	.data.b	101
	.data.b	5
	.data.b	67
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 5618
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,67,77,85,67,76,75,55,0
	.section	.debug_info		;off: 5010
	.data.w	.Ldw_str_begin+5618
	.data.b	102
	.data.b	5
	.data.b	67
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 5640
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,83,84,79,80,0
	.section	.debug_info		;off: 5019
	.data.w	.Ldw_str_begin+5640
	.data.b	105
	.data.b	5
	.data.b	67
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 5659
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,84,82,73,71,79,85,84,0
	.section	.debug_info		;off: 5028
	.data.w	.Ldw_str_begin+5659
	.data.b	106
	.data.b	5
	.data.b	67
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 5681
	.data.b	71,84,77,95,80,87,77,95,67,76,79,67,75,95,69,88,84,84,82,73,71,73,78,0
	.section	.debug_info		;off: 5037
	.data.w	.Ldw_str_begin+5681
	.data.b	107
	.data.b	5
	.data.b	67
	.data.b	14

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5705
	.data.b	71,116,109,95,80,119,109,95,67,108,111,99,107,0
	.section	.debug_info		;off: 5047
	.data.w	.Ldw_str_begin+5705
	.data.b	108
	.data.b	3
	.data.b	67
	.data.w	.Ldw_begin+4891

	.data.b	52
	.section	.debug_str		;off: 5719
	.data.b	0
	.section	.debug_info		;off: 5059
	.data.w	.Ldw_str_begin+5719
	.data.b	112
	.data.b	1
	.data.b	67
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5720
	.data.b	71,84,77,95,80,87,77,95,82,69,83,69,84,69,86,69,78,84,95,79,78,67,77,48,0
	.section	.debug_info		;off: 5069
	.data.w	.Ldw_str_begin+5720
	.data.b	113
	.data.b	5
	.data.b	67
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5745
	.data.b	71,84,77,95,80,87,77,95,82,69,83,69,84,69,86,69,78,84,95,79,78,84,82,73,71,71,69,82,0
	.section	.debug_info		;off: 5078
	.data.w	.Ldw_str_begin+5745
	.data.b	114
	.data.b	5
	.data.b	67
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5774
	.data.b	71,116,109,95,80,119,109,95,82,101,115,101,116,69,118,101,110,116,0
	.section	.debug_info		;off: 5088
	.data.w	.Ldw_str_begin+5774
	.data.b	115
	.data.b	3
	.data.b	67
	.data.w	.Ldw_begin+5058

	.data.b	52
	.section	.debug_str		;off: 5793
	.data.b	0
	.section	.debug_info		;off: 5100
	.data.w	.Ldw_str_begin+5793
	.data.b	119
	.data.b	1
	.data.b	67
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5794
	.data.b	71,84,77,95,80,87,77,95,84,82,73,71,79,85,84,95,70,79,82,87,65,82,68,0
	.section	.debug_info		;off: 5110
	.data.w	.Ldw_str_begin+5794
	.data.b	120
	.data.b	5
	.data.b	67
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5818
	.data.b	71,84,77,95,80,87,77,95,84,82,73,71,79,85,84,95,71,69,78,69,82,65,84,69,0
	.section	.debug_info		;off: 5119
	.data.w	.Ldw_str_begin+5818
	.data.b	121
	.data.b	5
	.data.b	67
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5843
	.data.b	71,116,109,95,80,119,109,95,84,114,105,103,79,117,116,0
	.section	.debug_info		;off: 5129
	.data.w	.Ldw_str_begin+5843
	.data.b	122
	.data.b	3
	.data.b	67
	.data.w	.Ldw_begin+5099

	.data.b	52
	.section	.debug_str		;off: 5859
	.data.b	0
	.section	.debug_info		;off: 5141
	.data.w	.Ldw_str_begin+5859
	.data.b	135,1
	.data.b	1
	.data.b	67
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5860
	.data.b	71,84,77,95,80,87,77,95,67,79,85,78,84,77,79,68,69,95,85,80,0
	.section	.debug_info		;off: 5152
	.data.w	.Ldw_str_begin+5860
	.data.b	136,1
	.data.b	5
	.data.b	67
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 5881
	.data.b	71,84,77,95,80,87,77,95,67,79,85,78,84,77,79,68,69,95,85,80,68,79,87,78,95,49,0
	.section	.debug_info		;off: 5162
	.data.w	.Ldw_str_begin+5881
	.data.b	137,1
	.data.b	5
	.data.b	67
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 5908
	.data.b	71,84,77,95,80,87,77,95,67,79,85,78,84,77,79,68,69,95,85,80,68,79,87,78,95,50,0
	.section	.debug_info		;off: 5172
	.data.w	.Ldw_str_begin+5908
	.data.b	138,1
	.data.b	5
	.data.b	67
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 5935
	.data.b	71,84,77,95,80,87,77,95,67,79,85,78,84,77,79,68,69,95,85,80,68,79,87,78,95,51,0
	.section	.debug_info		;off: 5182
	.data.w	.Ldw_str_begin+5935
	.data.b	139,1
	.data.b	5
	.data.b	67
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 5962
	.data.b	71,116,109,95,80,119,109,95,67,111,117,110,116,77,111,100,101,0
	.section	.debug_info		;off: 5193
	.data.w	.Ldw_str_begin+5962
	.data.b	140,1
	.data.b	3
	.data.b	67
	.data.w	.Ldw_begin+5140

	.data.b	71
	.data.b	149,1
	.data.b	1
	.data.b	67
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5980
	.data.b	105,115,82,105,115,101,69,110,97,98,108,101,100,0
	.section	.debug_info		;off: 5213
	.data.w	.Ldw_str_begin+5980
	.data.b	150,1
	.data.b	20
	.data.b	67
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 5994
	.data.b	105,115,70,97,108,108,69,110,97,98,108,101,100,0
	.section	.debug_info		;off: 5230
	.data.w	.Ldw_str_begin+5994
	.data.b	151,1
	.data.b	20
	.data.b	67
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6008
	.data.b	109,111,100,101,0
	.section	.debug_info		;off: 5247
	.data.w	.Ldw_str_begin+6008
	.data.b	152,1
	.data.b	20
	.data.b	67
	.data.w	.Ldw_begin+4679
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6013
	.data.b	71,116,109,95,80,119,109,95,67,111,110,102,105,103,73,114,113,0
	.section	.debug_info		;off: 5265
	.data.w	.Ldw_str_begin+6013
	.data.b	153,1
	.data.b	3
	.data.b	67
	.data.w	.Ldw_begin+5205

	.data.b	71
	.data.b	157,1
	.data.b	1
	.data.b	67
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6031
	.data.b	105,115,72,114,101,115,69,110,97,98,108,101,100,0
	.section	.debug_info		;off: 5285
	.data.w	.Ldw_str_begin+6031
	.data.b	158,1
	.data.b	17
	.data.b	67
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6045
	.data.b	104,114,101,115,80,101,114,105,111,100,0
	.section	.debug_info		;off: 5302
	.data.w	.Ldw_str_begin+6045
	.data.b	159,1
	.data.b	17
	.data.b	67
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6056
	.data.b	104,114,101,115,80,117,108,115,101,87,105,100,116,104,0
	.section	.debug_info		;off: 5319
	.data.w	.Ldw_str_begin+6056
	.data.b	160,1
	.data.b	17
	.data.b	67
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6071
	.data.b	71,116,109,95,80,119,109,95,72,114,101,115,67,111,110,102,105,103,0
	.section	.debug_info		;off: 5337
	.data.w	.Ldw_str_begin+6071
	.data.b	161,1
	.data.b	3
	.data.b	67
	.data.w	.Ldw_begin+5277

	.data.b	71
	.data.b	166,1
	.data.b	1
	.data.b	67
	.data.b	48
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6090
	.data.b	99,108,107,0
	.section	.debug_info		;off: 5357
	.data.w	.Ldw_str_begin+6090
	.data.b	167,1
	.data.b	30
	.data.b	67
	.data.w	.Ldw_begin+5046
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6094
	.data.b	112,101,114,105,111,100,0
	.section	.debug_info		;off: 5374
	.data.w	.Ldw_str_begin+6094
	.data.b	168,1
	.data.b	30
	.data.b	67
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6101
	.data.b	100,117,116,121,67,121,99,108,101,0
	.section	.debug_info		;off: 5391
	.data.w	.Ldw_str_begin+6101
	.data.b	169,1
	.data.b	30
	.data.b	67
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6111
	.data.b	112,104,97,115,101,0
	.section	.debug_info		;off: 5408
	.data.w	.Ldw_str_begin+6111
	.data.b	170,1
	.data.b	30
	.data.b	67
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6117
	.data.b	104,114,101,115,67,111,110,102,105,103,0
	.section	.debug_info		;off: 5425
	.data.w	.Ldw_str_begin+6117
	.data.b	171,1
	.data.b	30
	.data.b	67
	.data.w	.Ldw_begin+5336
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6128
	.data.b	114,101,115,101,116,83,111,117,114,99,101,0
	.section	.debug_info		;off: 5442
	.data.w	.Ldw_str_begin+6128
	.data.b	172,1
	.data.b	30
	.data.b	67
	.data.w	.Ldw_begin+5087
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6140
	.data.b	115,105,103,110,97,108,76,101,118,101,108,0
	.section	.debug_info		;off: 5459
	.data.w	.Ldw_str_begin+6140
	.data.b	173,1
	.data.b	30
	.data.b	67
	.data.w	.Ldw_begin+4724
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6152
	.data.b	105,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 5476
	.data.w	.Ldw_str_begin+6152
	.data.b	174,1
	.data.b	30
	.data.b	67
	.data.w	.Ldw_begin+5264
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6162
	.data.b	116,114,105,103,79,117,116,0
	.section	.debug_info		;off: 5493
	.data.w	.Ldw_str_begin+6162
	.data.b	175,1
	.data.b	30
	.data.b	67
	.data.w	.Ldw_begin+5128
	.data.b	2,35
	.data.b	36
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6170
	.data.b	99,111,117,110,116,77,111,100,101,0
	.section	.debug_info		;off: 5510
	.data.w	.Ldw_str_begin+6170
	.data.b	176,1
	.data.b	30
	.data.b	67
	.data.w	.Ldw_begin+5192
	.data.b	2,35
	.data.b	40
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6180
	.data.b	105,115,83,121,110,99,85,112,100,97,116,101,69,110,97,98,108,101,100,0
	.section	.debug_info		;off: 5527
	.data.w	.Ldw_str_begin+6180
	.data.b	177,1
	.data.b	30
	.data.b	67
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	44
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6200
	.data.b	105,115,67,104,97,110,110,101,108,69,110,97,98,108,101,0
	.section	.debug_info		;off: 5544
	.data.w	.Ldw_str_begin+6200
	.data.b	178,1
	.data.b	30
	.data.b	67
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	45
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6216
	.data.b	105,115,79,117,116,112,117,116,69,110,97,98,108,101,0
	.section	.debug_info		;off: 5561
	.data.w	.Ldw_str_begin+6216
	.data.b	179,1
	.data.b	30
	.data.b	67
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	46
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6231
	.data.b	105,115,73,109,109,101,100,105,97,116,101,0
	.section	.debug_info		;off: 5578
	.data.w	.Ldw_str_begin+6231
	.data.b	180,1
	.data.b	30
	.data.b	67
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	47
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6243
	.data.b	71,116,109,95,80,119,109,95,67,111,110,102,105,103,0
	.section	.debug_info		;off: 5596
	.data.w	.Ldw_str_begin+6243
	.data.b	181,1
	.data.b	3
	.data.b	67
	.data.w	.Ldw_begin+5349

	.data.b	52
	.section	.debug_str		;off: 6258
	.data.b	0
	.section	.debug_info		;off: 5609
	.data.w	.Ldw_str_begin+6258
	.data.b	89
	.data.b	1
	.data.b	66
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6259
	.data.b	80,87,77,95,86,65,82,73,65,66,76,69,95,80,69,82,73,79,68,0
	.section	.debug_info		;off: 5619
	.data.w	.Ldw_str_begin+6259
	.data.b	90
	.data.b	5
	.data.b	66
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 6279
	.data.b	80,87,77,95,70,73,88,69,68,95,80,69,82,73,79,68,0
	.section	.debug_info		;off: 5628
	.data.w	.Ldw_str_begin+6279
	.data.b	91
	.data.b	5
	.data.b	66
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6296
	.data.b	80,87,77,95,70,73,88,69,68,95,80,69,82,73,79,68,95,83,72,73,70,84,69,68,0
	.section	.debug_info		;off: 5637
	.data.w	.Ldw_str_begin+6296
	.data.b	92
	.data.b	5
	.data.b	66
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 6321
	.data.b	80,87,77,95,70,73,88,69,68,95,80,69,82,73,79,68,95,67,69,78,84,69,82,95,65,76,73,71,78,69,68,0
	.section	.debug_info		;off: 5646
	.data.w	.Ldw_str_begin+6321
	.data.b	93
	.data.b	5
	.data.b	66
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6353
	.data.b	80,119,109,95,67,104,110,80,101,114,105,111,100,84,121,112,101,0
	.section	.debug_info		;off: 5656
	.data.w	.Ldw_str_begin+6353
	.data.b	94
	.data.b	2
	.data.b	66
	.data.w	.Ldw_begin+5608

	.data.b	71
	.data.b	111
	.data.b	1
	.data.b	66
	.data.b	52
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6371
	.data.b	72,87,67,104,97,110,110,101,108,73,110,100,101,120,0
	.section	.debug_info		;off: 5674
	.data.w	.Ldw_str_begin+6371
	.data.b	113
	.data.b	34
	.data.b	66
	.data.w	.Ldw_begin+4878
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6386
	.data.b	72,87,67,104,97,110,110,101,108,67,111,110,102,105,103,0
	.section	.debug_info		;off: 5690
	.data.w	.Ldw_str_begin+6386
	.data.b	115
	.data.b	34
	.data.b	66
	.data.w	.Ldw_begin+5595
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6402
	.data.b	80,119,109,95,72,87,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 5707
	.data.w	.Ldw_str_begin+6402
	.data.b	116
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+5667

	.data.b	71
	.data.b	140,1
	.data.b	1
	.data.b	66
	.data.b	80
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6419
	.data.b	67,104,97,110,110,101,108,73,100,0
	.section	.debug_info		;off: 5726
	.data.w	.Ldw_str_begin+6419
	.data.b	142,1
	.data.b	25
	.data.b	66
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6429
	.data.b	73,100,108,101,76,101,118,101,108,0
	.section	.debug_info		;off: 5743
	.data.w	.Ldw_str_begin+6429
	.data.b	144,1
	.data.b	25
	.data.b	66
	.data.w	.Ldw_begin+4724
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6439
	.data.b	67,104,110,80,101,114,105,111,100,67,108,97,115,115,0
	.section	.debug_info		;off: 5760
	.data.w	.Ldw_str_begin+6439
	.data.b	146,1
	.data.b	25
	.data.b	66
	.data.w	.Ldw_begin+5655
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6454
	.data.b	80,101,114,105,111,100,0
	.section	.debug_info		;off: 5777
	.data.w	.Ldw_str_begin+6454
	.data.b	148,1
	.data.b	25
	.data.b	66
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6461
	.data.b	68,117,116,121,67,121,99,108,101,0
	.section	.debug_info		;off: 5794
	.data.w	.Ldw_str_begin+6461
	.data.b	150,1
	.data.b	25
	.data.b	66
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6471
	.data.b	83,104,105,102,116,86,97,108,117,101,0
	.section	.debug_info		;off: 5811
	.data.w	.Ldw_str_begin+6471
	.data.b	152,1
	.data.b	25
	.data.b	66
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6482
	.data.b	78,111,116,105,102,105,99,97,116,105,111,110,70,117,110,99,80,116,114,0
	.section	.debug_info		;off: 5828
	.data.w	.Ldw_str_begin+6482
	.data.b	154,1
	.data.b	27
	.data.b	66
	.data.w	.Ldw_begin+416
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6502
	.data.b	80,119,109,72,119,67,104,97,110,110,101,108,67,111,110,102,105,103,0
	.section	.debug_info		;off: 5845
	.data.w	.Ldw_str_begin+6502
	.data.b	156,1
	.data.b	25
	.data.b	66
	.data.w	.Ldw_begin+5706
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6521
	.data.b	80,119,109,95,67,104,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 5863
	.data.w	.Ldw_str_begin+6521
	.data.b	157,1
	.data.b	2
	.data.b	66
	.data.w	.Ldw_begin+5718

	.data.b	71
	.data.b	161,1
	.data.b	1
	.data.b	66
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6538
	.data.b	67,111,114,101,0
	.section	.debug_info		;off: 5883
	.data.w	.Ldw_str_begin+6538
	.data.b	163,1
	.data.b	26
	.data.b	66
	.data.w	.Ldw_begin+1405
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6543
	.data.b	73,110,100,101,120,0
	.section	.debug_info		;off: 5900
	.data.w	.Ldw_str_begin+6543
	.data.b	165,1
	.data.b	26
	.data.b	66
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6549
	.data.b	80,119,109,95,77,97,112,112,105,110,103,84,121,112,101,0
	.section	.debug_info		;off: 5918
	.data.w	.Ldw_str_begin+6549
	.data.b	166,1
	.data.b	3
	.data.b	66
	.data.w	.Ldw_begin+5875

	.data.b	71
	.data.b	170,1
	.data.b	1
	.data.b	66
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6565
	.data.b	77,97,120,67,104,97,110,110,101,108,115,0
	.section	.debug_info		;off: 5938
	.data.w	.Ldw_str_begin+6565
	.data.b	172,1
	.data.b	33
	.data.b	66
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6577
	.data.b	80,119,109,95,67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 5955
	.data.w	.Ldw_str_begin+6577
	.data.b	174,1
	.data.b	33
	.data.b	66
	.data.w	.Ldw_begin+426
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6598
	.data.b	80,119,109,95,67,111,114,101,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 5973
	.data.w	.Ldw_str_begin+6598
	.data.b	179,1
	.data.b	2
	.data.b	66
	.data.w	.Ldw_begin+5930

	.data.b	71
	.data.b	184,1
	.data.b	1
	.data.b	66
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6617
	.data.b	67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 5993
	.data.w	.Ldw_str_begin+6617
	.data.b	186,1
	.data.b	32
	.data.b	66
	.data.w	.Ldw_begin+441
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6631
	.data.b	80,119,109,67,104,97,110,110,101,108,73,100,120,109,97,112,80,116,114,0
	.section	.debug_info		;off: 6010
	.data.w	.Ldw_str_begin+6631
	.data.b	188,1
	.data.b	32
	.data.b	66
	.data.w	.Ldw_begin+462
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6651
	.data.b	80,119,109,72,119,67,104,97,110,110,101,108,77,97,112,80,116,114,0
	.section	.debug_info		;off: 6027
	.data.w	.Ldw_str_begin+6651
	.data.b	190,1
	.data.b	32
	.data.b	66
	.data.w	.Ldw_begin+467
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6670
	.data.b	80,119,109,95,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 6045
	.data.w	.Ldw_str_begin+6670
	.data.b	191,1
	.data.b	2
	.data.b	66
	.data.w	.Ldw_begin+5985

	.data.b	71
	.data.b	190,6
	.data.b	1
	.data.b	80
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6685
	.data.b	83,82,67,65,68,68,82,0
	.section	.debug_info		;off: 6065
	.data.w	.Ldw_str_begin+6685
	.data.b	191,6
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	0
	.data.b	32
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

	.section	.debug_info		;off: 6084
	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6693
	.data.b	68,77,65,95,67,72,95,83,82,67,65,68,68,82,95,66,105,116,115,0
	.section	.debug_info		;off: 6086
	.data.w	.Ldw_str_begin+6693
	.data.b	192,6
	.data.b	3
	.data.b	80
	.data.w	.Ldw_begin+483

	.data.b	71
	.data.b	196,6
	.data.b	1
	.data.b	80
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6713
	.data.b	68,69,83,84,65,68,68,82,0
	.section	.debug_info		;off: 6106
	.data.w	.Ldw_str_begin+6713
	.data.b	197,6
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	0
	.data.b	32
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6722
	.data.b	68,77,65,95,67,72,95,68,69,83,84,65,68,68,82,95,66,105,116,115,0
	.section	.debug_info		;off: 6127
	.data.w	.Ldw_str_begin+6722
	.data.b	198,6
	.data.b	3
	.data.b	80
	.data.w	.Ldw_begin+488

	.data.b	71
	.data.b	202,6
	.data.b	1
	.data.b	80
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6743
	.data.b	76,77,0
	.section	.debug_info		;off: 6147
	.data.w	.Ldw_str_begin+6743
	.data.b	203,6
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	31
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6746
	.data.b	114,101,115,101,114,118,101,100,95,49,0
	.section	.debug_info		;off: 6167
	.data.w	.Ldw_str_begin+6746
	.data.b	204,6
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	30
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6757
	.data.b	76,76,73,0
	.section	.debug_info		;off: 6187
	.data.w	.Ldw_str_begin+6757
	.data.b	205,6
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	0
	.data.b	30
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6761
	.data.b	68,77,65,95,67,72,95,76,76,73,82,69,71,66,105,116,115,0
	.section	.debug_info		;off: 6208
	.data.w	.Ldw_str_begin+6761
	.data.b	206,6
	.data.b	3
	.data.b	80
	.data.w	.Ldw_begin+493

	.data.b	71
	.data.b	210,6
	.data.b	1
	.data.b	80
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6779
	.data.b	84,82,65,78,83,73,90,69,0
	.section	.debug_info		;off: 6228
	.data.w	.Ldw_str_begin+6779
	.data.b	211,6
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	20
	.data.b	12
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6788
	.data.b	83,66,83,73,90,69,0
	.section	.debug_info		;off: 6248
	.data.w	.Ldw_str_begin+6788
	.data.b	212,6
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	17
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6795
	.data.b	68,66,83,73,90,69,0
	.section	.debug_info		;off: 6268
	.data.w	.Ldw_str_begin+6795
	.data.b	213,6
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	14
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6802
	.data.b	83,87,73,68,84,72,0
	.section	.debug_info		;off: 6288
	.data.w	.Ldw_str_begin+6802
	.data.b	214,6
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	11
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6809
	.data.b	68,87,73,68,84,72,0
	.section	.debug_info		;off: 6308
	.data.w	.Ldw_str_begin+6809
	.data.b	215,6
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	8
	.data.b	3
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6816
	.data.b	83,0
	.section	.debug_info		;off: 6328
	.data.w	.Ldw_str_begin+6816
	.data.b	216,6
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	7
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6818
	.data.b	68,0
	.section	.debug_info		;off: 6348
	.data.w	.Ldw_str_begin+6818
	.data.b	217,6
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	6
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6820
	.data.b	83,73,0
	.section	.debug_info		;off: 6368
	.data.w	.Ldw_str_begin+6820
	.data.b	218,6
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	5
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6823
	.data.b	68,73,0
	.section	.debug_info		;off: 6388
	.data.w	.Ldw_str_begin+6823
	.data.b	219,6
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6826
	.data.b	65,77,0
	.section	.debug_info		;off: 6408
	.data.w	.Ldw_str_begin+6826
	.data.b	220,6
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	3
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6829
	.data.b	66,69,0
	.section	.debug_info		;off: 6428
	.data.w	.Ldw_str_begin+6829
	.data.b	221,6
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	2
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6832
	.data.b	67,69,0
	.section	.debug_info		;off: 6448
	.data.w	.Ldw_str_begin+6832
	.data.b	222,6
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	1
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6835
	.data.b	73,0
	.section	.debug_info		;off: 6468
	.data.w	.Ldw_str_begin+6835
	.data.b	223,6
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	0
	.data.b	1
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6837
	.data.b	68,77,65,95,67,72,95,67,79,78,84,82,79,76,95,66,105,116,115,0
	.section	.debug_info		;off: 6489
	.data.w	.Ldw_str_begin+6837
	.data.b	224,6
	.data.b	3
	.data.b	80
	.data.w	.Ldw_begin+498

	.data.b	71
	.data.b	207,8
	.data.b	1
	.data.b	80
	.data.b	4
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6857
	.data.b	67,82,67,86,65,76,0
	.section	.debug_info		;off: 6509
	.data.w	.Ldw_str_begin+6857
	.data.b	208,8
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	24
	.data.b	8
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	41
	.section	.debug_str		;off: 6864
	.data.b	114,101,115,101,114,118,101,100,95,56,0
	.section	.debug_info		;off: 6529
	.data.w	.Ldw_str_begin+6864
	.data.b	209,8
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+173
	.data.b	4
	.data.b	0
	.data.b	24
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6875
	.data.b	68,77,65,95,67,72,95,69,88,80,76,76,73,67,82,67,95,66,105,116,115,0
	.section	.debug_info		;off: 6550
	.data.w	.Ldw_str_begin+6875
	.data.b	210,8
	.data.b	3
	.data.b	80
	.data.w	.Ldw_begin+503

	.data.b	73
	.data.b	227,10
	.data.b	1
	.data.b	80
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

	.section	.debug_info		;off: 6569
	.data.b	40
	.section	.debug_str		;off: 6897
	.data.b	85,0
	.section	.debug_info		;off: 6570
	.data.w	.Ldw_str_begin+6897
	.data.b	228,10
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6899
	.data.b	66,0
	.section	.debug_info		;off: 6587
	.data.w	.Ldw_str_begin+6899
	.data.b	229,10
	.data.b	25
	.data.b	80
	.data.w	.Ldw_begin+6085
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6901
	.data.b	68,77,65,95,67,72,95,83,82,67,65,68,68,82,0
	.section	.debug_info		;off: 6605
	.data.w	.Ldw_str_begin+6901
	.data.b	230,10
	.data.b	3
	.data.b	80
	.data.w	.Ldw_begin+6562

	.data.b	73
	.data.b	235,10
	.data.b	1
	.data.b	80
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6916
	.data.b	85,0
	.section	.debug_info		;off: 6625
	.data.w	.Ldw_str_begin+6916
	.data.b	236,10
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6918
	.data.b	66,0
	.section	.debug_info		;off: 6642
	.data.w	.Ldw_str_begin+6918
	.data.b	237,10
	.data.b	26
	.data.b	80
	.data.w	.Ldw_begin+6126
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6920
	.data.b	68,77,65,95,67,72,95,68,69,83,84,65,68,68,82,0
	.section	.debug_info		;off: 6660
	.data.w	.Ldw_str_begin+6920
	.data.b	238,10
	.data.b	3
	.data.b	80
	.data.w	.Ldw_begin+6617

	.data.b	73
	.data.b	243,10
	.data.b	1
	.data.b	80
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6936
	.data.b	85,0
	.section	.debug_info		;off: 6680
	.data.w	.Ldw_str_begin+6936
	.data.b	244,10
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6938
	.data.b	66,0
	.section	.debug_info		;off: 6697
	.data.w	.Ldw_str_begin+6938
	.data.b	245,10
	.data.b	23
	.data.b	80
	.data.w	.Ldw_begin+6207
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6940
	.data.b	68,77,65,95,67,72,95,76,76,73,82,69,71,0
	.section	.debug_info		;off: 6715
	.data.w	.Ldw_str_begin+6940
	.data.b	246,10
	.data.b	3
	.data.b	80
	.data.w	.Ldw_begin+6672

	.data.b	73
	.data.b	251,10
	.data.b	1
	.data.b	80
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6954
	.data.b	85,0
	.section	.debug_info		;off: 6735
	.data.w	.Ldw_str_begin+6954
	.data.b	252,10
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6956
	.data.b	66,0
	.section	.debug_info		;off: 6752
	.data.w	.Ldw_str_begin+6956
	.data.b	253,10
	.data.b	25
	.data.b	80
	.data.w	.Ldw_begin+6488
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6958
	.data.b	68,77,65,95,67,72,95,67,79,78,84,82,79,76,0
	.section	.debug_info		;off: 6770
	.data.w	.Ldw_str_begin+6958
	.data.b	254,10
	.data.b	3
	.data.b	80
	.data.w	.Ldw_begin+6727

	.data.b	73
	.data.b	195,12
	.data.b	1
	.data.b	80
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6973
	.data.b	85,0
	.section	.debug_info		;off: 6790
	.data.w	.Ldw_str_begin+6973
	.data.b	196,12
	.data.b	12
	.data.b	80
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 6975
	.data.b	66,0
	.section	.debug_info		;off: 6807
	.data.w	.Ldw_str_begin+6975
	.data.b	197,12
	.data.b	27
	.data.b	80
	.data.w	.Ldw_begin+6549
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 6977
	.data.b	68,77,65,95,67,72,95,69,88,80,76,76,73,67,82,67,0
	.section	.debug_info		;off: 6825
	.data.w	.Ldw_str_begin+6977
	.data.b	198,12
	.data.b	3
	.data.b	80
	.data.w	.Ldw_begin+6782

	.data.b	52
	.section	.debug_str		;off: 6994
	.data.b	0
	.section	.debug_info		;off: 6838
	.data.w	.Ldw_str_begin+6994
	.data.b	81
	.data.b	1
	.data.b	79
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 6995
	.data.b	68,77,65,95,67,72,65,78,78,69,76,65,68,68,82,69,83,83,73,78,67,82,69,77,69,78,84,95,78,79,95,73,78,67,82,69,65,83,69,0
	.section	.debug_info		;off: 6848
	.data.w	.Ldw_str_begin+6995
	.data.b	82
	.data.b	5
	.data.b	79
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7035
	.data.b	68,77,65,95,67,72,65,78,78,69,76,65,68,68,82,69,83,83,73,78,67,82,69,77,69,78,84,95,73,78,67,82,69,65,83,69,0
	.section	.debug_info		;off: 6857
	.data.w	.Ldw_str_begin+7035
	.data.b	83
	.data.b	5
	.data.b	79
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7072
	.data.b	68,109,97,95,67,104,97,110,110,101,108,65,100,100,114,101,115,115,73,110,99,114,101,109,101,110,116,0
	.section	.debug_info		;off: 6867
	.data.w	.Ldw_str_begin+7072
	.data.b	84
	.data.b	3
	.data.b	79
	.data.w	.Ldw_begin+6837

	.data.b	52
	.section	.debug_str		;off: 7100
	.data.b	0
	.section	.debug_info		;off: 6879
	.data.w	.Ldw_str_begin+7100
	.data.b	88
	.data.b	1
	.data.b	79
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7101
	.data.b	68,77,65,95,67,72,65,78,78,69,76,84,82,65,78,83,70,69,82,87,73,68,84,72,95,56,66,73,84,0
	.section	.debug_info		;off: 6889
	.data.w	.Ldw_str_begin+7101
	.data.b	89
	.data.b	5
	.data.b	79
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7131
	.data.b	68,77,65,95,67,72,65,78,78,69,76,84,82,65,78,83,70,69,82,87,73,68,84,72,95,49,54,66,73,84,0
	.section	.debug_info		;off: 6898
	.data.w	.Ldw_str_begin+7131
	.data.b	90
	.data.b	5
	.data.b	79
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7162
	.data.b	68,77,65,95,67,72,65,78,78,69,76,84,82,65,78,83,70,69,82,87,73,68,84,72,95,51,50,66,73,84,0
	.section	.debug_info		;off: 6907
	.data.w	.Ldw_str_begin+7162
	.data.b	91
	.data.b	5
	.data.b	79
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 7193
	.data.b	68,77,65,95,67,72,65,78,78,69,76,84,82,65,78,83,70,69,82,87,73,68,84,72,95,54,52,66,73,84,0
	.section	.debug_info		;off: 6916
	.data.w	.Ldw_str_begin+7193
	.data.b	92
	.data.b	5
	.data.b	79
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 7224
	.data.b	68,77,65,95,67,72,65,78,78,69,76,84,82,65,78,83,70,69,82,87,73,68,84,72,95,49,50,56,66,73,84,0
	.section	.debug_info		;off: 6925
	.data.w	.Ldw_str_begin+7224
	.data.b	93
	.data.b	5
	.data.b	79
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7256
	.data.b	68,109,97,95,67,104,97,110,110,101,108,84,114,97,110,115,102,101,114,87,105,100,116,104,0
	.section	.debug_info		;off: 6935
	.data.w	.Ldw_str_begin+7256
	.data.b	94
	.data.b	3
	.data.b	79
	.data.w	.Ldw_begin+6878

	.data.b	52
	.section	.debug_str		;off: 7281
	.data.b	0
	.section	.debug_info		;off: 6947
	.data.w	.Ldw_str_begin+7281
	.data.b	98
	.data.b	1
	.data.b	79
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7282
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,49,0
	.section	.debug_info		;off: 6957
	.data.w	.Ldw_str_begin+7282
	.data.b	99
	.data.b	5
	.data.b	79
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7305
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,52,0
	.section	.debug_info		;off: 6966
	.data.w	.Ldw_str_begin+7305
	.data.b	100
	.data.b	5
	.data.b	79
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7328
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,56,0
	.section	.debug_info		;off: 6975
	.data.w	.Ldw_str_begin+7328
	.data.b	101
	.data.b	5
	.data.b	79
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 7351
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,49,54,0
	.section	.debug_info		;off: 6984
	.data.w	.Ldw_str_begin+7351
	.data.b	102
	.data.b	5
	.data.b	79
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 7375
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,51,50,0
	.section	.debug_info		;off: 6993
	.data.w	.Ldw_str_begin+7375
	.data.b	103
	.data.b	5
	.data.b	79
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 7399
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,54,52,0
	.section	.debug_info		;off: 7002
	.data.w	.Ldw_str_begin+7399
	.data.b	104
	.data.b	5
	.data.b	79
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 7423
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,49,50,56,0
	.section	.debug_info		;off: 7011
	.data.w	.Ldw_str_begin+7423
	.data.b	105
	.data.b	5
	.data.b	79
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 7448
	.data.b	68,77,65,95,67,72,65,78,78,69,76,66,85,82,83,84,83,73,90,69,95,50,53,54,0
	.section	.debug_info		;off: 7020
	.data.w	.Ldw_str_begin+7448
	.data.b	106
	.data.b	5
	.data.b	79
	.data.b	7

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7473
	.data.b	68,109,97,95,67,104,97,110,110,101,108,66,117,114,115,116,83,105,122,101,0
	.section	.debug_info		;off: 7030
	.data.w	.Ldw_str_begin+7473
	.data.b	107
	.data.b	3
	.data.b	79
	.data.w	.Ldw_begin+6946

	.data.b	52
	.section	.debug_str		;off: 7494
	.data.b	0
	.section	.debug_info		;off: 7042
	.data.w	.Ldw_str_begin+7494
	.data.b	111
	.data.b	1
	.data.b	79
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7495
	.data.b	68,77,65,95,70,76,79,87,67,79,78,84,82,79,76,65,78,68,84,82,65,78,83,70,69,82,84,89,80,69,95,68,77,65,95,77,50,77,0
	.section	.debug_info		;off: 7052
	.data.w	.Ldw_str_begin+7495
	.data.b	112
	.data.b	5
	.data.b	79
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7534
	.data.b	68,77,65,95,70,76,79,87,67,79,78,84,82,79,76,65,78,68,84,82,65,78,83,70,69,82,84,89,80,69,95,68,77,65,95,77,50,80,0
	.section	.debug_info		;off: 7061
	.data.w	.Ldw_str_begin+7534
	.data.b	113
	.data.b	5
	.data.b	79
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7573
	.data.b	68,77,65,95,70,76,79,87,67,79,78,84,82,79,76,65,78,68,84,82,65,78,83,70,69,82,84,89,80,69,95,68,77,65,95,80,50,77,0
	.section	.debug_info		;off: 7070
	.data.w	.Ldw_str_begin+7573
	.data.b	114
	.data.b	5
	.data.b	79
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 7612
	.data.b	68,77,65,95,70,76,79,87,67,79,78,84,82,79,76,65,78,68,84,82,65,78,83,70,69,82,84,89,80,69,95,68,77,65,95,80,50,80,0
	.section	.debug_info		;off: 7079
	.data.w	.Ldw_str_begin+7612
	.data.b	115
	.data.b	5
	.data.b	79
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 7651
	.data.b	68,77,65,95,70,76,79,87,67,79,78,84,82,79,76,65,78,68,84,82,65,78,83,70,69,82,84,89,80,69,95,68,80,69,82,95,80,50,80,0
	.section	.debug_info		;off: 7088
	.data.w	.Ldw_str_begin+7651
	.data.b	116
	.data.b	5
	.data.b	79
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 7691
	.data.b	68,77,65,95,70,76,79,87,67,79,78,84,82,79,76,65,78,68,84,82,65,78,83,70,69,82,84,89,80,69,95,80,69,82,95,77,50,80,0
	.section	.debug_info		;off: 7097
	.data.w	.Ldw_str_begin+7691
	.data.b	117
	.data.b	5
	.data.b	79
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 7730
	.data.b	68,77,65,95,70,76,79,87,67,79,78,84,82,79,76,65,78,68,84,82,65,78,83,70,69,82,84,89,80,69,95,80,69,82,95,80,50,77,0
	.section	.debug_info		;off: 7106
	.data.w	.Ldw_str_begin+7730
	.data.b	118
	.data.b	5
	.data.b	79
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 7769
	.data.b	68,77,65,95,70,76,79,87,67,79,78,84,82,79,76,65,78,68,84,82,65,78,83,70,69,82,84,89,80,69,95,83,80,69,82,95,80,50,80,0
	.section	.debug_info		;off: 7115
	.data.w	.Ldw_str_begin+7769
	.data.b	119
	.data.b	5
	.data.b	79
	.data.b	7

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7809
	.data.b	68,109,97,95,70,108,111,119,67,111,110,116,114,111,108,65,110,100,84,114,97,110,115,102,101,114,84,121,112,101,0
	.section	.debug_info		;off: 7125
	.data.w	.Ldw_str_begin+7809
	.data.b	120
	.data.b	3
	.data.b	79
	.data.w	.Ldw_begin+7041

	.data.b	52
	.section	.debug_str		;off: 7840
	.data.b	0
	.section	.debug_info		;off: 7137
	.data.w	.Ldw_str_begin+7840
	.data.b	124
	.data.b	1
	.data.b	79
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7841
	.data.b	68,77,65,95,68,66,83,79,85,82,67,69,79,82,68,69,83,84,73,78,65,84,73,79,78,95,83,79,85,82,67,69,0
	.section	.debug_info		;off: 7147
	.data.w	.Ldw_str_begin+7841
	.data.b	125
	.data.b	5
	.data.b	79
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7874
	.data.b	68,77,65,95,68,66,83,79,85,82,67,69,79,82,68,69,83,84,73,78,65,84,73,79,78,95,68,69,83,84,73,78,65,84,73,79,78,0
	.section	.debug_info		;off: 7156
	.data.w	.Ldw_str_begin+7874
	.data.b	126
	.data.b	5
	.data.b	79
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7912
	.data.b	68,109,97,95,68,66,83,111,117,114,99,101,79,114,68,101,115,116,105,110,97,116,105,111,110,0
	.section	.debug_info		;off: 7166
	.data.w	.Ldw_str_begin+7912
	.data.b	127
	.data.b	3
	.data.b	79
	.data.w	.Ldw_begin+7136

	.data.b	52
	.section	.debug_str		;off: 7938
	.data.b	0
	.section	.debug_info		;off: 7178
	.data.w	.Ldw_str_begin+7938
	.data.b	131,1
	.data.b	1
	.data.b	79
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 7939
	.data.b	68,77,65,95,68,66,83,87,73,84,67,72,77,79,68,69,95,83,87,0
	.section	.debug_info		;off: 7189
	.data.w	.Ldw_str_begin+7939
	.data.b	132,1
	.data.b	5
	.data.b	79
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 7959
	.data.b	68,77,65,95,68,66,83,87,73,84,67,72,77,79,68,69,95,72,87,95,83,87,0
	.section	.debug_info		;off: 7199
	.data.w	.Ldw_str_begin+7959
	.data.b	133,1
	.data.b	5
	.data.b	79
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 7982
	.data.b	68,109,97,95,68,66,83,119,105,116,99,104,77,111,100,101,0
	.section	.debug_info		;off: 7210
	.data.w	.Ldw_str_begin+7982
	.data.b	134,1
	.data.b	3
	.data.b	79
	.data.w	.Ldw_begin+7177

	.data.b	52
	.section	.debug_str		;off: 7999
	.data.b	0
	.section	.debug_info		;off: 7223
	.data.w	.Ldw_str_begin+7999
	.data.b	138,1
	.data.b	1
	.data.b	79
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8000
	.data.b	68,77,65,95,67,66,83,79,85,82,67,69,79,82,68,69,83,84,73,78,65,84,73,79,78,95,83,79,85,82,67,69,0
	.section	.debug_info		;off: 7234
	.data.w	.Ldw_str_begin+8000
	.data.b	139,1
	.data.b	5
	.data.b	79
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8033
	.data.b	68,77,65,95,67,66,83,79,85,82,67,69,79,82,68,69,83,84,73,78,65,84,73,79,78,95,68,69,83,84,73,78,65,84,73,79,78,0
	.section	.debug_info		;off: 7244
	.data.w	.Ldw_str_begin+8033
	.data.b	140,1
	.data.b	5
	.data.b	79
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 8071
	.data.b	68,77,65,95,67,66,83,79,85,82,67,69,79,82,68,69,83,84,73,78,65,84,73,79,78,95,66,79,84,72,0
	.section	.debug_info		;off: 7254
	.data.w	.Ldw_str_begin+8071
	.data.b	141,1
	.data.b	5
	.data.b	79
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8102
	.data.b	68,109,97,95,67,66,83,111,117,114,99,101,79,114,68,101,115,116,105,110,97,116,105,111,110,0
	.section	.debug_info		;off: 7265
	.data.w	.Ldw_str_begin+8102
	.data.b	142,1
	.data.b	3
	.data.b	79
	.data.w	.Ldw_begin+7222

	.data.b	52
	.section	.debug_str		;off: 8128
	.data.b	0
	.section	.debug_info		;off: 7278
	.data.w	.Ldw_str_begin+8128
	.data.b	146,1
	.data.b	1
	.data.b	79
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8129
	.data.b	68,77,65,95,67,66,83,73,90,69,95,78,79,78,69,0
	.section	.debug_info		;off: 7289
	.data.w	.Ldw_str_begin+8129
	.data.b	147,1
	.data.b	5
	.data.b	79
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 8145
	.data.b	68,77,65,95,67,66,83,73,90,69,95,50,66,89,84,69,0
	.section	.debug_info		;off: 7299
	.data.w	.Ldw_str_begin+8145
	.data.b	148,1
	.data.b	5
	.data.b	79
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8162
	.data.b	68,77,65,95,67,66,83,73,90,69,95,52,66,89,84,69,0
	.section	.debug_info		;off: 7309
	.data.w	.Ldw_str_begin+8162
	.data.b	149,1
	.data.b	5
	.data.b	79
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 8179
	.data.b	68,77,65,95,67,66,83,73,90,69,95,56,66,89,84,69,0
	.section	.debug_info		;off: 7319
	.data.w	.Ldw_str_begin+8179
	.data.b	150,1
	.data.b	5
	.data.b	79
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 8196
	.data.b	68,77,65,95,67,66,83,73,90,69,95,49,54,66,89,84,69,0
	.section	.debug_info		;off: 7329
	.data.w	.Ldw_str_begin+8196
	.data.b	151,1
	.data.b	5
	.data.b	79
	.data.b	4

	.data.b	51
	.section	.debug_str		;off: 8214
	.data.b	68,77,65,95,67,66,83,73,90,69,95,51,50,66,89,84,69,0
	.section	.debug_info		;off: 7339
	.data.w	.Ldw_str_begin+8214
	.data.b	152,1
	.data.b	5
	.data.b	79
	.data.b	5

	.data.b	51
	.section	.debug_str		;off: 8232
	.data.b	68,77,65,95,67,66,83,73,90,69,95,54,52,66,89,84,69,0
	.section	.debug_info		;off: 7349
	.data.w	.Ldw_str_begin+8232
	.data.b	153,1
	.data.b	5
	.data.b	79
	.data.b	6

	.data.b	51
	.section	.debug_str		;off: 8250
	.data.b	68,77,65,95,67,66,83,73,90,69,95,49,50,56,66,89,84,69,0
	.section	.debug_info		;off: 7359
	.data.w	.Ldw_str_begin+8250
	.data.b	154,1
	.data.b	5
	.data.b	79
	.data.b	7

	.data.b	51
	.section	.debug_str		;off: 8269
	.data.b	68,77,65,95,67,66,83,73,90,69,95,50,53,54,66,89,84,69,0
	.section	.debug_info		;off: 7369
	.data.w	.Ldw_str_begin+8269
	.data.b	155,1
	.data.b	5
	.data.b	79
	.data.b	8

	.data.b	51
	.section	.debug_str		;off: 8288
	.data.b	68,77,65,95,67,66,83,73,90,69,95,53,49,50,66,89,84,69,0
	.section	.debug_info		;off: 7379
	.data.w	.Ldw_str_begin+8288
	.data.b	156,1
	.data.b	5
	.data.b	79
	.data.b	9

	.data.b	51
	.section	.debug_str		;off: 8307
	.data.b	68,77,65,95,67,66,83,73,90,69,95,49,48,50,52,66,89,84,69,0
	.section	.debug_info		;off: 7389
	.data.w	.Ldw_str_begin+8307
	.data.b	157,1
	.data.b	5
	.data.b	79
	.data.b	10

	.data.b	51
	.section	.debug_str		;off: 8327
	.data.b	68,77,65,95,67,66,83,73,90,69,95,50,48,52,56,66,89,84,69,0
	.section	.debug_info		;off: 7399
	.data.w	.Ldw_str_begin+8327
	.data.b	158,1
	.data.b	5
	.data.b	79
	.data.b	11

	.data.b	51
	.section	.debug_str		;off: 8347
	.data.b	68,77,65,95,67,66,83,73,90,69,95,52,48,57,54,66,89,84,69,0
	.section	.debug_info		;off: 7409
	.data.w	.Ldw_str_begin+8347
	.data.b	159,1
	.data.b	5
	.data.b	79
	.data.b	12

	.data.b	51
	.section	.debug_str		;off: 8367
	.data.b	68,77,65,95,67,66,83,73,90,69,95,56,49,57,50,66,89,84,69,0
	.section	.debug_info		;off: 7419
	.data.w	.Ldw_str_begin+8367
	.data.b	160,1
	.data.b	5
	.data.b	79
	.data.b	13

	.data.b	51
	.section	.debug_str		;off: 8387
	.data.b	68,77,65,95,67,66,83,73,90,69,95,49,54,51,56,52,66,89,84,69,0
	.section	.debug_info		;off: 7429
	.data.w	.Ldw_str_begin+8387
	.data.b	161,1
	.data.b	5
	.data.b	79
	.data.b	14

	.data.b	51
	.section	.debug_str		;off: 8408
	.data.b	68,77,65,95,67,66,83,73,90,69,95,51,50,55,54,56,66,89,84,69,0
	.section	.debug_info		;off: 7439
	.data.w	.Ldw_str_begin+8408
	.data.b	162,1
	.data.b	5
	.data.b	79
	.data.b	15

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8429
	.data.b	68,109,97,95,67,66,83,105,122,101,0
	.section	.debug_info		;off: 7450
	.data.w	.Ldw_str_begin+8429
	.data.b	163,1
	.data.b	3
	.data.b	79
	.data.w	.Ldw_begin+7277

	.data.b	52
	.section	.debug_str		;off: 8440
	.data.b	0
	.section	.debug_info		;off: 7463
	.data.w	.Ldw_str_begin+8440
	.data.b	167,1
	.data.b	1
	.data.b	79
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8441
	.data.b	68,77,65,95,80,65,84,84,69,82,78,83,73,90,69,95,68,73,83,65,66,76,69,0
	.section	.debug_info		;off: 7474
	.data.w	.Ldw_str_begin+8441
	.data.b	168,1
	.data.b	5
	.data.b	79
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 8465
	.data.b	68,77,65,95,80,65,84,84,69,82,78,83,73,90,69,95,56,66,73,84,0
	.section	.debug_info		;off: 7484
	.data.w	.Ldw_str_begin+8465
	.data.b	169,1
	.data.b	5
	.data.b	79
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8486
	.data.b	68,77,65,95,80,65,84,84,69,82,78,83,73,90,69,95,49,54,66,73,84,0
	.section	.debug_info		;off: 7494
	.data.w	.Ldw_str_begin+8486
	.data.b	170,1
	.data.b	5
	.data.b	79
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 8508
	.data.b	68,77,65,95,80,65,84,84,69,82,78,83,73,90,69,95,51,50,66,73,84,0
	.section	.debug_info		;off: 7504
	.data.w	.Ldw_str_begin+8508
	.data.b	171,1
	.data.b	5
	.data.b	79
	.data.b	3

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8530
	.data.b	68,109,97,95,80,97,116,116,101,114,110,83,105,122,101,0
	.section	.debug_info		;off: 7515
	.data.w	.Ldw_str_begin+8530
	.data.b	172,1
	.data.b	3
	.data.b	79
	.data.w	.Ldw_begin+7462

	.data.b	52
	.section	.debug_str		;off: 8546
	.data.b	0
	.section	.debug_info		;off: 7528
	.data.w	.Ldw_str_begin+8546
	.data.b	176,1
	.data.b	1
	.data.b	79
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8547
	.data.b	68,77,65,95,68,79,85,66,76,69,66,85,70,70,69,82,70,82,79,90,69,78,83,84,65,84,85,83,95,78,79,95,70,82,79,90,69,78,0
	.section	.debug_info		;off: 7539
	.data.w	.Ldw_str_begin+8547
	.data.b	177,1
	.data.b	5
	.data.b	79
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 8586
	.data.b	68,77,65,95,68,79,85,66,76,69,66,85,70,70,69,82,70,82,79,90,69,78,83,84,65,84,85,83,95,66,85,70,70,69,82,48,95,70,82,79,90,69,78,0
	.section	.debug_info		;off: 7549
	.data.w	.Ldw_str_begin+8586
	.data.b	178,1
	.data.b	5
	.data.b	79
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 8630
	.data.b	68,77,65,95,68,79,85,66,76,69,66,85,70,70,69,82,70,82,79,90,69,78,83,84,65,84,85,83,95,66,85,70,70,69,82,49,95,70,82,79,90,69,78,0
	.section	.debug_info		;off: 7559
	.data.w	.Ldw_str_begin+8630
	.data.b	179,1
	.data.b	5
	.data.b	79
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 8674
	.data.b	68,77,65,95,68,79,85,66,76,69,66,85,70,70,69,82,70,82,79,90,69,78,83,84,65,84,85,83,95,66,79,84,72,95,70,82,79,90,69,78,95,66,85,70,70,69,82,48,70,73,82,83,84,0
	.section	.debug_info		;off: 7569
	.data.w	.Ldw_str_begin+8674
	.data.b	180,1
	.data.b	5
	.data.b	79
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 8728
	.data.b	68,77,65,95,68,79,85,66,76,69,66,85,70,70,69,82,70,82,79,90,69,78,83,84,65,84,85,83,95,66,79,84,72,95,70,82,79,90,69,78,95,66,85,70,70,69,82,49,70,73,82,83,84,0
	.section	.debug_info		;off: 7579
	.data.w	.Ldw_str_begin+8728
	.data.b	181,1
	.data.b	5
	.data.b	79
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8782
	.data.b	68,109,97,95,68,111,117,98,108,101,66,117,102,102,101,114,70,114,111,122,101,110,83,116,97,116,117,115,0
	.section	.debug_info		;off: 7590
	.data.w	.Ldw_str_begin+8782
	.data.b	182,1
	.data.b	3
	.data.b	79
	.data.w	.Ldw_begin+7527

	.data.b	71
	.data.b	253,1
	.data.b	1
	.data.b	79
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8811
	.data.b	97,100,100,114,101,115,115,0
	.section	.debug_info		;off: 7610
	.data.w	.Ldw_str_begin+8811
	.data.b	254,1
	.data.b	12
	.data.b	79
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8819
	.data.b	105,110,99,114,101,109,101,110,116,0
	.section	.debug_info		;off: 7627
	.data.w	.Ldw_str_begin+8819
	.data.b	255,1
	.data.b	33
	.data.b	79
	.data.w	.Ldw_begin+6866
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8829
	.data.b	98,117,114,115,116,83,105,122,101,0
	.section	.debug_info		;off: 7644
	.data.w	.Ldw_str_begin+8829
	.data.b	128,2
	.data.b	26
	.data.b	79
	.data.w	.Ldw_begin+7029
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8839
	.data.b	68,109,97,95,67,104,97,110,110,101,108,65,100,100,114,101,115,115,67,111,110,102,105,103,0
	.section	.debug_info		;off: 7662
	.data.w	.Ldw_str_begin+8839
	.data.b	129,2
	.data.b	3
	.data.b	79
	.data.w	.Ldw_begin+7602

	.data.b	71
	.data.b	133,2
	.data.b	1
	.data.b	79
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8864
	.data.b	114,101,113,117,101,115,116,0
	.section	.debug_info		;off: 7682
	.data.w	.Ldw_str_begin+8864
	.data.b	134,2
	.data.b	12
	.data.b	79
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8872
	.data.b	114,101,113,117,101,115,116,77,85,88,0
	.section	.debug_info		;off: 7699
	.data.w	.Ldw_str_begin+8872
	.data.b	135,2
	.data.b	12
	.data.b	79
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 8883
	.data.b	68,109,97,95,67,104,97,110,110,101,108,82,101,113,117,115,116,0
	.section	.debug_info		;off: 7717
	.data.w	.Ldw_str_begin+8883
	.data.b	138,2
	.data.b	3
	.data.b	79
	.data.w	.Ldw_begin+7674

	.data.b	71
	.data.b	143,2
	.data.b	1
	.data.b	79
	.data.b	52
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8901
	.data.b	115,111,117,114,99,101,0
	.section	.debug_info		;off: 7737
	.data.w	.Ldw_str_begin+8901
	.data.b	144,2
	.data.b	30
	.data.b	79
	.data.w	.Ldw_begin+7661
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8908
	.data.b	100,101,115,116,105,110,97,116,105,111,110,0
	.section	.debug_info		;off: 7754
	.data.w	.Ldw_str_begin+8908
	.data.b	145,2
	.data.b	30
	.data.b	79
	.data.w	.Ldw_begin+7661
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8920
	.data.b	116,114,97,110,115,102,101,114,87,105,100,116,104,0
	.section	.debug_info		;off: 7771
	.data.w	.Ldw_str_begin+8920
	.data.b	146,2
	.data.b	30
	.data.b	79
	.data.w	.Ldw_begin+6934
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8934
	.data.b	102,108,111,119,67,111,110,116,114,111,108,65,110,100,84,114,97,110,115,102,101,114,84,121,112,101,0
	.section	.debug_info		;off: 7788
	.data.w	.Ldw_str_begin+8934
	.data.b	147,2
	.data.b	36
	.data.b	79
	.data.w	.Ldw_begin+7124
	.data.b	2,35
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8961
	.data.b	115,111,117,114,99,101,82,101,113,117,101,115,116,0
	.section	.debug_info		;off: 7805
	.data.w	.Ldw_str_begin+8961
	.data.b	148,2
	.data.b	23
	.data.b	79
	.data.w	.Ldw_begin+7716
	.data.b	2,35
	.data.b	32
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8975
	.data.b	100,101,115,116,105,110,97,116,105,111,110,82,101,113,117,101,115,116,0
	.section	.debug_info		;off: 7822
	.data.w	.Ldw_str_begin+8975
	.data.b	151,2
	.data.b	23
	.data.b	79
	.data.w	.Ldw_begin+7716
	.data.b	2,35
	.data.b	40
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 8994
	.data.b	116,114,97,110,115,102,101,114,83,105,122,101,0
	.section	.debug_info		;off: 7839
	.data.w	.Ldw_str_begin+8994
	.data.b	154,2
	.data.b	12
	.data.b	79
	.data.w	.Ldw_begin+1178
	.data.b	2,35
	.data.b	48
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9007
	.data.b	68,109,97,95,67,104,97,110,110,101,108,84,114,97,110,115,102,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 7857
	.data.w	.Ldw_str_begin+9007
	.data.b	155,2
	.data.b	3
	.data.b	79
	.data.w	.Ldw_begin+7729

	.data.b	71
	.data.b	187,2
	.data.b	1
	.data.b	79
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9033
	.data.b	112,97,116,116,101,114,110,83,105,122,101,0
	.section	.debug_info		;off: 7877
	.data.w	.Ldw_str_begin+9033
	.data.b	188,2
	.data.b	21
	.data.b	79
	.data.w	.Ldw_begin+7514
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9045
	.data.b	112,97,116,116,101,114,110,68,97,116,97,0
	.section	.debug_info		;off: 7894
	.data.w	.Ldw_str_begin+9045
	.data.b	189,2
	.data.b	12
	.data.b	79
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9057
	.data.b	112,97,116,116,101,114,110,68,97,116,97,77,97,115,107,66,105,116,0
	.section	.debug_info		;off: 7911
	.data.w	.Ldw_str_begin+9057
	.data.b	190,2
	.data.b	12
	.data.b	79
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9076
	.data.b	112,97,116,116,101,114,110,77,97,116,99,104,101,100,83,116,111,112,0
	.section	.debug_info		;off: 7928
	.data.w	.Ldw_str_begin+9076
	.data.b	191,2
	.data.b	13
	.data.b	79
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9095
	.data.b	68,109,97,95,77,97,116,99,104,80,97,116,116,101,114,110,67,111,110,102,105,103,0
	.section	.debug_info		;off: 7946
	.data.w	.Ldw_str_begin+9095
	.data.b	192,2
	.data.b	3
	.data.b	79
	.data.w	.Ldw_begin+7869

	.data.b	71
	.data.b	197,2
	.data.b	1
	.data.b	79
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9118
	.data.b	115,101,108,0
	.section	.debug_info		;off: 7966
	.data.w	.Ldw_str_begin+9118
	.data.b	198,2
	.data.b	31
	.data.b	79
	.data.w	.Ldw_begin+7165
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9122
	.data.b	109,111,100,101,0
	.section	.debug_info		;off: 7983
	.data.w	.Ldw_str_begin+9122
	.data.b	199,2
	.data.b	22
	.data.b	79
	.data.w	.Ldw_begin+7209
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9127
	.data.b	115,119,105,116,99,104,65,100,100,114,0
	.section	.debug_info		;off: 8000
	.data.w	.Ldw_str_begin+9127
	.data.b	200,2
	.data.b	12
	.data.b	79
	.data.w	.Ldw_begin+1190
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9138
	.data.b	68,109,97,95,68,111,117,98,108,101,66,117,102,102,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 8018
	.data.w	.Ldw_str_begin+9138
	.data.b	201,2
	.data.b	3
	.data.b	79
	.data.w	.Ldw_begin+7958

	.data.b	71
	.data.b	207,2
	.data.b	1
	.data.b	79
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9161
	.data.b	115,101,108,0
	.section	.debug_info		;off: 8038
	.data.w	.Ldw_str_begin+9161
	.data.b	208,2
	.data.b	31
	.data.b	79
	.data.w	.Ldw_begin+7264
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9165
	.data.b	115,114,99,83,105,122,101,0
	.section	.debug_info		;off: 8055
	.data.w	.Ldw_str_begin+9165
	.data.b	209,2
	.data.b	16
	.data.b	79
	.data.w	.Ldw_begin+7449
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9173
	.data.b	100,101,115,83,105,122,101,0
	.section	.debug_info		;off: 8072
	.data.w	.Ldw_str_begin+9173
	.data.b	210,2
	.data.b	16
	.data.b	79
	.data.w	.Ldw_begin+7449
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9181
	.data.b	100,101,115,82,111,108,108,98,97,99,107,72,97,108,116,69,110,0
	.section	.debug_info		;off: 8089
	.data.w	.Ldw_str_begin+9181
	.data.b	211,2
	.data.b	13
	.data.b	79
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9199
	.data.b	68,109,97,95,67,105,114,99,117,108,97,114,66,117,102,102,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 8107
	.data.w	.Ldw_str_begin+9199
	.data.b	212,2
	.data.b	3
	.data.b	79
	.data.w	.Ldw_begin+8030

	.data.b	71
	.data.b	218,2
	.data.b	1
	.data.b	79
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9224
	.data.b	108,105,110,107,101,100,76,105,115,116,73,116,101,109,83,114,99,65,100,100,114,0
	.section	.debug_info		;off: 8127
	.data.w	.Ldw_str_begin+9224
	.data.b	219,2
	.data.b	20
	.data.b	79
	.data.w	.Ldw_begin+6604
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9246
	.data.b	108,105,110,107,101,100,76,105,115,116,73,116,101,109,68,101,115,116,65,100,100,114,0
	.section	.debug_info		;off: 8144
	.data.w	.Ldw_str_begin+9246
	.data.b	220,2
	.data.b	21
	.data.b	79
	.data.w	.Ldw_begin+6659
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9269
	.data.b	108,105,110,107,101,100,76,105,115,116,73,116,101,109,76,108,105,82,101,103,0
	.section	.debug_info		;off: 8161
	.data.w	.Ldw_str_begin+9269
	.data.b	221,2
	.data.b	19
	.data.b	79
	.data.w	.Ldw_begin+6714
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9290
	.data.b	108,105,110,107,101,100,76,105,115,116,73,116,101,109,67,116,114,108,0
	.section	.debug_info		;off: 8178
	.data.w	.Ldw_str_begin+9290
	.data.b	222,2
	.data.b	20
	.data.b	79
	.data.w	.Ldw_begin+6769
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9309
	.data.b	108,105,110,107,101,100,76,105,115,116,73,116,101,109,67,82,67,0
	.section	.debug_info		;off: 8195
	.data.w	.Ldw_str_begin+9309
	.data.b	223,2
	.data.b	22
	.data.b	79
	.data.w	.Ldw_begin+6824
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9327
	.data.b	68,109,97,95,76,105,110,107,101,100,76,105,115,116,73,116,101,109,0
	.section	.debug_info		;off: 8213
	.data.w	.Ldw_str_begin+9327
	.data.b	224,2
	.data.b	3
	.data.b	79
	.data.w	.Ldw_begin+8119

	.data.b	45
	.section	.debug_str		;off: 9346
	.data.b	68,109,97,95,72,119,85,110,105,116,84,121,112,101,0
	.section	.debug_info		;off: 8226
	.data.w	.Ldw_str_begin+9346
	.data.b	48
	.data.b	46
	.data.b	77
	.data.w	.Ldw_begin+1154

	.data.b	45
	.section	.debug_str		;off: 9361
	.data.b	68,109,97,95,67,104,97,110,110,101,108,84,121,112,101,0
	.section	.debug_info		;off: 8238
	.data.w	.Ldw_str_begin+9361
	.data.b	50
	.data.b	46
	.data.b	77
	.data.w	.Ldw_begin+1154

	.data.b	45
	.section	.debug_str		;off: 9377
	.data.b	68,109,97,95,84,114,97,110,115,102,101,114,84,121,112,101,0
	.section	.debug_info		;off: 8250
	.data.w	.Ldw_str_begin+9377
	.data.b	52
	.data.b	46
	.data.b	77
	.data.w	.Ldw_begin+1154

	.data.b	45
	.section	.debug_str		;off: 9394
	.data.b	68,109,97,95,76,105,110,107,101,100,76,105,115,116,84,121,112,101,0
	.section	.debug_info		;off: 8262
	.data.w	.Ldw_str_begin+9394
	.data.b	55
	.data.b	46
	.data.b	77
	.data.w	.Ldw_begin+8249

	.data.b	45
	.section	.debug_str		;off: 9413
	.data.b	68,109,97,95,83,104,97,100,111,119,105,110,103,84,121,112,101,0
	.section	.debug_info		;off: 8274
	.data.w	.Ldw_str_begin+9413
	.data.b	59
	.data.b	46
	.data.b	77
	.data.w	.Ldw_begin+8249

	.data.b	45
	.section	.debug_str		;off: 9431
	.data.b	68,109,97,95,68,111,117,98,108,101,66,117,102,102,101,114,84,121,112,101,0
	.section	.debug_info		;off: 8286
	.data.w	.Ldw_str_begin+9431
	.data.b	63
	.data.b	46
	.data.b	77
	.data.w	.Ldw_begin+8249

	.data.b	45
	.section	.debug_str		;off: 9452
	.data.b	68,109,97,95,67,105,114,99,117,108,97,114,66,117,102,102,101,114,84,121,112,101,0
	.section	.debug_info		;off: 8298
	.data.w	.Ldw_str_begin+9452
	.data.b	67
	.data.b	46
	.data.b	77
	.data.w	.Ldw_begin+8249

	.data.b	45
	.section	.debug_str		;off: 9475
	.data.b	68,109,97,95,80,97,116,116,101,114,110,84,121,112,101,0
	.section	.debug_info		;off: 8310
	.data.w	.Ldw_str_begin+9475
	.data.b	71
	.data.b	46
	.data.b	77
	.data.w	.Ldw_begin+8249

	.data.b	45
	.section	.debug_str		;off: 9491
	.data.b	68,109,97,95,76,108,105,66,117,102,84,121,112,101,0
	.section	.debug_info		;off: 8322
	.data.w	.Ldw_str_begin+9491
	.data.b	75
	.data.b	46
	.data.b	77
	.data.w	.Ldw_begin+8212

	.data.b	52
	.section	.debug_str		;off: 9506
	.data.b	0
	.section	.debug_info		;off: 8334
	.data.w	.Ldw_str_begin+9506
	.data.b	94
	.data.b	1
	.data.b	77
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 9507
	.data.b	68,77,65,95,67,72,95,67,65,78,67,69,76,95,68,73,82,69,67,84,0
	.section	.debug_info		;off: 8344
	.data.w	.Ldw_str_begin+9507
	.data.b	96
	.data.b	5
	.data.b	77
	.data.b	0

	.data.b	51
	.section	.debug_str		;off: 9528
	.data.b	68,77,65,95,67,72,95,67,65,78,67,69,76,95,83,65,70,69,0
	.section	.debug_info		;off: 8353
	.data.w	.Ldw_str_begin+9528
	.data.b	98
	.data.b	5
	.data.b	77
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9547
	.data.b	68,109,97,95,67,104,67,97,110,99,101,108,84,121,112,101,0
	.section	.debug_info		;off: 8363
	.data.w	.Ldw_str_begin+9547
	.data.b	99
	.data.b	3
	.data.b	77
	.data.w	.Ldw_begin+8333

	.data.b	52
	.section	.debug_str		;off: 9564
	.data.b	0
	.section	.debug_info		;off: 8375
	.data.w	.Ldw_str_begin+9564
	.data.b	103
	.data.b	1
	.data.b	77
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 9565
	.data.b	68,77,65,95,67,72,95,73,78,84,95,84,67,0
	.section	.debug_info		;off: 8385
	.data.w	.Ldw_str_begin+9565
	.data.b	105
	.data.b	5
	.data.b	77
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 9579
	.data.b	68,77,65,95,67,72,95,73,78,84,95,69,82,82,79,82,0
	.section	.debug_info		;off: 8394
	.data.w	.Ldw_str_begin+9579
	.data.b	107
	.data.b	6
	.data.b	77
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 9596
	.data.b	68,77,65,95,67,72,95,73,78,84,95,80,65,84,84,69,82,78,0
	.section	.debug_info		;off: 8403
	.data.w	.Ldw_str_begin+9596
	.data.b	119
	.data.b	6
	.data.b	77
	.data.b	16

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9615
	.data.b	68,109,97,95,67,104,69,118,101,110,116,84,121,112,101,0
	.section	.debug_info		;off: 8413
	.data.w	.Ldw_str_begin+9615
	.data.b	126
	.data.b	3
	.data.b	77
	.data.w	.Ldw_begin+8374

	.data.b	52
	.section	.debug_str		;off: 9631
	.data.b	0
	.section	.debug_info		;off: 8425
	.data.w	.Ldw_str_begin+9631
	.data.b	155,1
	.data.b	1
	.data.b	77
	.data.b	4
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 9632
	.data.b	68,77,65,95,67,72,95,68,66,95,70,82,79,90,69,78,95,66,85,70,48,0
	.section	.debug_info		;off: 8436
	.data.w	.Ldw_str_begin+9632
	.data.b	157,1
	.data.b	5
	.data.b	77
	.data.b	1

	.data.b	51
	.section	.debug_str		;off: 9654
	.data.b	68,77,65,95,67,72,95,68,66,95,70,82,79,90,69,78,95,66,85,70,49,0
	.section	.debug_info		;off: 8446
	.data.w	.Ldw_str_begin+9654
	.data.b	159,1
	.data.b	5
	.data.b	77
	.data.b	2

	.data.b	51
	.section	.debug_str		;off: 9676
	.data.b	68,77,65,95,67,72,95,68,66,95,66,79,84,72,95,70,82,79,90,69,78,95,66,85,70,48,0
	.section	.debug_info		;off: 8456
	.data.w	.Ldw_str_begin+9676
	.data.b	161,1
	.data.b	5
	.data.b	77
	.data.b	3

	.data.b	51
	.section	.debug_str		;off: 9703
	.data.b	68,77,65,95,67,72,95,68,66,95,66,79,84,72,95,70,79,82,90,69,78,95,66,85,70,49,0
	.section	.debug_info		;off: 8466
	.data.w	.Ldw_str_begin+9703
	.data.b	163,1
	.data.b	5
	.data.b	77
	.data.b	4

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9730
	.data.b	68,109,97,95,68,98,108,70,114,122,110,83,116,97,116,117,115,84,121,112,101,0
	.section	.debug_info		;off: 8477
	.data.w	.Ldw_str_begin+9730
	.data.b	164,1
	.data.b	3
	.data.b	77
	.data.w	.Ldw_begin+8424

	.data.b	71
	.data.b	221,1
	.data.b	1
	.data.b	77
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9752
	.data.b	80,104,121,67,104,97,110,110,101,108,73,100,0
	.section	.debug_info		;off: 8497
	.data.w	.Ldw_str_begin+9752
	.data.b	223,1
	.data.b	40
	.data.b	77
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9765
	.data.b	72,119,85,110,105,116,73,100,0
	.section	.debug_info		;off: 8514
	.data.w	.Ldw_str_begin+9765
	.data.b	225,1
	.data.b	40
	.data.b	77
	.data.w	.Ldw_begin+8225
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9774
	.data.b	67,111,114,101,67,104,73,100,120,0
	.section	.debug_info		;off: 8531
	.data.w	.Ldw_str_begin+9774
	.data.b	227,1
	.data.b	40
	.data.b	77
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9784
	.data.b	67,104,84,114,97,110,115,102,101,114,73,100,120,0
	.section	.debug_info		;off: 8548
	.data.w	.Ldw_str_begin+9784
	.data.b	231,1
	.data.b	40
	.data.b	77
	.data.w	.Ldw_begin+8249
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9798
	.data.b	67,104,83,104,97,100,111,119,105,110,103,73,100,120,0
	.section	.debug_info		;off: 8565
	.data.w	.Ldw_str_begin+9798
	.data.b	236,1
	.data.b	40
	.data.b	77
	.data.w	.Ldw_begin+8273
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9813
	.data.b	67,111,114,101,68,99,73,100,120,0
	.section	.debug_info		;off: 8582
	.data.w	.Ldw_str_begin+9813
	.data.b	240,1
	.data.b	40
	.data.b	77
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9823
	.data.b	67,111,114,101,68,99,70,105,114,115,116,67,104,0
	.section	.debug_info		;off: 8599
	.data.w	.Ldw_str_begin+9823
	.data.b	243,1
	.data.b	40
	.data.b	77
	.data.w	.Ldw_begin+8237
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9837
	.data.b	67,104,77,97,112,67,111,114,101,73,100,0
	.section	.debug_info		;off: 8616
	.data.w	.Ldw_str_begin+9837
	.data.b	246,1
	.data.b	40
	.data.b	77
	.data.w	.Ldw_begin+1405
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9849
	.data.b	68,109,97,95,67,104,97,110,110,101,108,77,97,112,84,121,112,101,0
	.section	.debug_info		;off: 8634
	.data.w	.Ldw_str_begin+9849
	.data.b	247,1
	.data.b	3
	.data.b	77
	.data.w	.Ldw_begin+8489

	.data.b	71
	.data.b	254,1
	.data.b	1
	.data.b	77
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9868
	.data.b	76,108,105,77,97,120,78,117,109,0
	.section	.debug_info		;off: 8654
	.data.w	.Ldw_str_begin+9868
	.data.b	128,2
	.data.b	40
	.data.b	77
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9878
	.data.b	76,108,105,84,111,84,114,97,110,115,102,101,114,73,100,80,116,114,0
	.section	.debug_info		;off: 8671
	.data.w	.Ldw_str_begin+9878
	.data.b	131,2
	.data.b	41
	.data.b	77
	.data.w	.Ldw_begin+513
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9897
	.data.b	68,109,97,95,76,105,110,107,101,100,76,105,115,116,77,97,112,84,121,112,101,0
	.section	.debug_info		;off: 8689
	.data.w	.Ldw_str_begin+9897
	.data.b	132,2
	.data.b	3
	.data.b	77
	.data.w	.Ldw_begin+8646

	.data.b	71
	.data.b	138,2
	.data.b	1
	.data.b	77
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9919
	.data.b	76,108,105,77,97,112,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 8709
	.data.w	.Ldw_str_begin+9919
	.data.b	140,2
	.data.b	41
	.data.b	77
	.data.w	.Ldw_begin+523
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9933
	.data.b	76,108,105,66,117,102,80,116,114,0
	.section	.debug_info		;off: 8726
	.data.w	.Ldw_str_begin+9933
	.data.b	142,2
	.data.b	41
	.data.b	77
	.data.w	.Ldw_begin+528
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 9943
	.data.b	68,109,97,95,67,104,76,105,110,107,101,100,76,105,115,116,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 8744
	.data.w	.Ldw_str_begin+9943
	.data.b	143,2
	.data.b	3
	.data.b	77
	.data.w	.Ldw_begin+8701

	.data.b	71
	.data.b	151,2
	.data.b	1
	.data.b	77
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9970
	.data.b	83,104,97,100,111,119,84,111,84,114,97,110,115,102,101,114,73,100,0
	.section	.debug_info		;off: 8764
	.data.w	.Ldw_str_begin+9970
	.data.b	153,2
	.data.b	40
	.data.b	77
	.data.w	.Ldw_begin+8249
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 9989
	.data.b	83,104,97,100,111,119,84,111,76,108,105,73,100,0
	.section	.debug_info		;off: 8781
	.data.w	.Ldw_str_begin+9989
	.data.b	157,2
	.data.b	40
	.data.b	77
	.data.w	.Ldw_begin+8261
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10003
	.data.b	68,109,97,95,83,104,97,100,111,119,105,110,103,77,97,112,84,121,112,101,0
	.section	.debug_info		;off: 8799
	.data.w	.Ldw_str_begin+10003
	.data.b	159,2
	.data.b	3
	.data.b	77
	.data.w	.Ldw_begin+8756

	.data.b	71
	.data.b	167,2
	.data.b	1
	.data.b	77
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10024
	.data.b	68,98,108,66,117,102,67,111,110,102,105,103,0
	.section	.debug_info		;off: 8819
	.data.w	.Ldw_str_begin+10024
	.data.b	169,2
	.data.b	44
	.data.b	77
	.data.w	.Ldw_begin+533
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10037
	.data.b	68,109,97,68,98,108,70,114,122,110,78,111,116,105,102,105,99,97,116,105,111,110,80,116,114,0
	.section	.debug_info		;off: 8836
	.data.w	.Ldw_str_begin+10037
	.data.b	171,2
	.data.b	12
	.data.b	77
	.data.w	.Ldw_begin+553
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10063
	.data.b	68,109,97,95,68,111,117,98,108,101,66,117,102,102,101,114,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 8854
	.data.w	.Ldw_str_begin+10063
	.data.b	173,2
	.data.b	3
	.data.b	77
	.data.w	.Ldw_begin+8811

	.data.b	71
	.data.b	181,2
	.data.b	1
	.data.b	77
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10090
	.data.b	68,99,77,97,120,78,117,109,0
	.section	.debug_info		;off: 8874
	.data.w	.Ldw_str_begin+10090
	.data.b	183,2
	.data.b	39
	.data.b	77
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10099
	.data.b	68,99,84,111,67,104,97,110,110,101,108,80,116,114,0
	.section	.debug_info		;off: 8891
	.data.w	.Ldw_str_begin+10099
	.data.b	186,2
	.data.b	40
	.data.b	77
	.data.w	.Ldw_begin+563
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10114
	.data.b	68,109,97,95,68,97,105,115,121,67,104,97,105,110,77,97,112,84,121,112,101,0
	.section	.debug_info		;off: 8909
	.data.w	.Ldw_str_begin+10114
	.data.b	187,2
	.data.b	3
	.data.b	77
	.data.w	.Ldw_begin+8866

	.data.b	71
	.data.b	194,2
	.data.b	1
	.data.b	77
	.data.b	56
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10136
	.data.b	67,104,68,111,117,98,108,101,66,117,102,102,101,114,73,100,0
	.section	.debug_info		;off: 8929
	.data.w	.Ldw_str_begin+10136
	.data.b	197,2
	.data.b	44
	.data.b	77
	.data.w	.Ldw_begin+8285
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10153
	.data.b	67,104,67,105,114,99,117,108,97,114,66,117,102,102,101,114,73,100,0
	.section	.debug_info		;off: 8946
	.data.w	.Ldw_str_begin+10153
	.data.b	201,2
	.data.b	44
	.data.b	77
	.data.w	.Ldw_begin+8297
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10172
	.data.b	67,104,80,97,116,116,101,114,110,73,100,0
	.section	.debug_info		;off: 8963
	.data.w	.Ldw_str_begin+10172
	.data.b	205,2
	.data.b	44
	.data.b	77
	.data.w	.Ldw_begin+8309
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10184
	.data.b	67,104,76,105,110,107,101,100,76,105,115,116,73,100,0
	.section	.debug_info		;off: 8980
	.data.w	.Ldw_str_begin+10184
	.data.b	209,2
	.data.b	44
	.data.b	77
	.data.w	.Ldw_begin+8261
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10199
	.data.b	67,104,84,114,97,110,115,102,101,114,67,111,110,102,105,103,0
	.section	.debug_info		;off: 8997
	.data.w	.Ldw_str_begin+10199
	.data.b	216,2
	.data.b	44
	.data.b	77
	.data.w	.Ldw_begin+568
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10216
	.data.b	68,109,97,95,84,114,97,110,115,102,101,114,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 9015
	.data.w	.Ldw_str_begin+10216
	.data.b	217,2
	.data.b	3
	.data.b	77
	.data.w	.Ldw_begin+8921

	.data.b	71
	.data.b	223,2
	.data.b	1
	.data.b	77
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10239
	.data.b	67,104,97,110,110,101,108,73,100,0
	.section	.debug_info		;off: 9035
	.data.w	.Ldw_str_begin+10239
	.data.b	225,2
	.data.b	44
	.data.b	77
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10249
	.data.b	73,115,84,114,97,110,115,67,102,103,69,120,105,115,116,115,0
	.section	.debug_info		;off: 9052
	.data.w	.Ldw_str_begin+10249
	.data.b	228,2
	.data.b	44
	.data.b	77
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10266
	.data.b	67,104,84,114,97,110,115,102,101,114,84,111,116,97,108,78,117,109,0
	.section	.debug_info		;off: 9069
	.data.w	.Ldw_str_begin+10266
	.data.b	232,2
	.data.b	44
	.data.b	77
	.data.w	.Ldw_begin+8249
	.data.b	2,35
	.data.b	2
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10285
	.data.b	67,104,83,104,97,100,111,119,84,111,116,97,108,78,117,109,0
	.section	.debug_info		;off: 9086
	.data.w	.Ldw_str_begin+10285
	.data.b	235,2
	.data.b	44
	.data.b	77
	.data.w	.Ldw_begin+8273
	.data.b	2,35
	.data.b	3
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10302
	.data.b	67,104,76,108,105,84,111,116,97,108,78,117,109,0
	.section	.debug_info		;off: 9103
	.data.w	.Ldw_str_begin+10302
	.data.b	239,2
	.data.b	44
	.data.b	77
	.data.w	.Ldw_begin+8261
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10316
	.data.b	67,104,73,110,116,101,114,114,117,112,116,69,110,66,105,116,115,0
	.section	.debug_info		;off: 9120
	.data.w	.Ldw_str_begin+10316
	.data.b	244,2
	.data.b	44
	.data.b	77
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	5
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10334
	.data.b	67,104,67,111,110,116,105,110,117,111,117,115,77,111,100,101,0
	.section	.debug_info		;off: 9137
	.data.w	.Ldw_str_begin+10334
	.data.b	248,2
	.data.b	44
	.data.b	77
	.data.w	.Ldw_begin+1142
	.data.b	2,35
	.data.b	6
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10351
	.data.b	67,104,83,104,97,100,111,119,77,97,112,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 9154
	.data.w	.Ldw_str_begin+10351
	.data.b	252,2
	.data.b	45
	.data.b	77
	.data.w	.Ldw_begin+578
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10370
	.data.b	67,104,76,108,105,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 9171
	.data.w	.Ldw_str_begin+10370
	.data.b	128,3
	.data.b	45
	.data.b	77
	.data.w	.Ldw_begin+588
	.data.b	2,35
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10385
	.data.b	68,109,97,67,104,97,110,110,101,108,78,111,116,105,102,105,99,97,116,105,111,110,80,116,114,0
	.section	.debug_info		;off: 9188
	.data.w	.Ldw_str_begin+10385
	.data.b	131,3
	.data.b	12
	.data.b	77
	.data.w	.Ldw_begin+608
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10411
	.data.b	67,104,84,114,97,110,115,102,101,114,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 9205
	.data.w	.Ldw_str_begin+10411
	.data.b	133,3
	.data.b	45
	.data.b	77
	.data.w	.Ldw_begin+618
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10431
	.data.b	68,109,97,95,67,104,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 9223
	.data.w	.Ldw_str_begin+10431
	.data.b	134,3
	.data.b	3
	.data.b	77
	.data.w	.Ldw_begin+9027

	.data.b	71
	.data.b	140,3
	.data.b	1
	.data.b	77
	.data.b	24
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10448
	.data.b	77,97,120,72,119,85,110,105,116,78,117,109,0
	.section	.debug_info		;off: 9243
	.data.w	.Ldw_str_begin+10448
	.data.b	142,3
	.data.b	40
	.data.b	77
	.data.w	.Ldw_begin+8225
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10461
	.data.b	72,119,85,110,105,116,76,105,115,116,80,116,114,0
	.section	.debug_info		;off: 9260
	.data.w	.Ldw_str_begin+10461
	.data.b	144,3
	.data.b	41
	.data.b	77
	.data.w	.Ldw_begin+628
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10475
	.data.b	72,119,84,111,67,104,97,110,110,101,108,80,116,114,0
	.section	.debug_info		;off: 9277
	.data.w	.Ldw_str_begin+10475
	.data.b	147,3
	.data.b	41
	.data.b	77
	.data.w	.Ldw_begin+633
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10490
	.data.b	68,109,97,95,72,119,85,110,105,116,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 9295
	.data.w	.Ldw_str_begin+10490
	.data.b	148,3
	.data.b	3
	.data.b	77
	.data.w	.Ldw_begin+9235

	.data.b	71
	.data.b	154,3
	.data.b	1
	.data.b	77
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10511
	.data.b	77,97,120,67,104,97,110,110,101,108,0
	.section	.debug_info		;off: 9315
	.data.w	.Ldw_str_begin+10511
	.data.b	156,3
	.data.b	44
	.data.b	77
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10522
	.data.b	77,97,120,68,97,105,115,121,67,104,97,105,110,0
	.section	.debug_info		;off: 9332
	.data.w	.Ldw_str_begin+10522
	.data.b	159,3
	.data.b	44
	.data.b	77
	.data.w	.Ldw_begin+1154
	.data.b	2,35
	.data.b	1
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10536
	.data.b	68,97,105,115,121,67,104,97,105,110,76,105,115,116,80,116,114,0
	.section	.debug_info		;off: 9349
	.data.w	.Ldw_str_begin+10536
	.data.b	161,3
	.data.b	45
	.data.b	77
	.data.w	.Ldw_begin+654
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10554
	.data.b	67,104,97,110,110,101,108,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 9366
	.data.w	.Ldw_str_begin+10554
	.data.b	164,3
	.data.b	45
	.data.b	77
	.data.w	.Ldw_begin+664
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10571
	.data.b	68,109,97,95,67,111,114,101,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 9384
	.data.w	.Ldw_str_begin+10571
	.data.b	165,3
	.data.b	3
	.data.b	77
	.data.w	.Ldw_begin+9307

	.data.b	71
	.data.b	173,3
	.data.b	1
	.data.b	77
	.data.b	12
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10590
	.data.b	68,98,108,66,117,102,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 9404
	.data.w	.Ldw_str_begin+10590
	.data.b	176,3
	.data.b	45
	.data.b	77
	.data.w	.Ldw_begin+674
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10606
	.data.b	67,105,114,99,66,117,102,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 9421
	.data.w	.Ldw_str_begin+10606
	.data.b	180,3
	.data.b	45
	.data.b	77
	.data.w	.Ldw_begin+684
	.data.b	2,35
	.data.b	4
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10623
	.data.b	80,97,116,116,101,114,110,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 9438
	.data.w	.Ldw_str_begin+10623
	.data.b	184,3
	.data.b	45
	.data.b	77
	.data.w	.Ldw_begin+694
	.data.b	2,35
	.data.b	8
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10640
	.data.b	68,109,97,95,67,111,109,109,111,110,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 9456
	.data.w	.Ldw_str_begin+10640
	.data.b	186,3
	.data.b	3
	.data.b	77
	.data.w	.Ldw_begin+9396

	.data.b	71
	.data.b	193,3
	.data.b	1
	.data.b	77
	.data.b	28
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10661
	.data.b	67,111,114,101,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 9476
	.data.w	.Ldw_str_begin+10661
	.data.b	195,3
	.data.b	41
	.data.b	77
	.data.w	.Ldw_begin+709
	.data.b	2,35
	.data.b	0
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10675
	.data.b	67,111,109,109,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 9493
	.data.w	.Ldw_str_begin+10675
	.data.b	199,3
	.data.b	41
	.data.b	77
	.data.w	.Ldw_begin+730
	.data.b	2,35
	.data.b	16
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10689
	.data.b	67,104,97,110,110,101,108,77,97,112,73,110,102,111,80,116,114,0
	.section	.debug_info		;off: 9510
	.data.w	.Ldw_str_begin+10689
	.data.b	203,3
	.data.b	41
	.data.b	77
	.data.w	.Ldw_begin+740
	.data.b	2,35
	.data.b	20
	.data.b	1

	.data.b	40
	.section	.debug_str		;off: 10707
	.data.b	72,119,85,110,105,116,67,111,110,102,105,103,80,116,114,0
	.section	.debug_info		;off: 9527
	.data.w	.Ldw_str_begin+10707
	.data.b	205,3
	.data.b	41
	.data.b	77
	.data.w	.Ldw_begin+750
	.data.b	2,35
	.data.b	24
	.data.b	1

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 10723
	.data.b	68,109,97,95,67,111,110,102,105,103,84,121,112,101,0
	.section	.debug_info		;off: 9545
	.data.w	.Ldw_str_begin+10723
	.data.b	206,3
	.data.b	3
	.data.b	77
	.data.w	.Ldw_begin+9468

	.data.b	8
	.section	.debug_str		;off: 10738
	.data.b	68,115,97,100,99,95,67,111,110,102,105,103,83,101,116,0
	.section	.debug_info		;off: 9558
	.data.w	.Ldw_str_begin+10738
	.data.b	51
	.data.b	31
	.data.b	39
	.data.w	.Ldw_begin+760
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

	.section	.debug_info		;off: 9571
	.data.b	8
	.section	.debug_str		;off: 10754
	.data.b	80,119,109,95,67,111,110,102,105,103,83,101,116,0
	.section	.debug_info		;off: 9572
	.data.w	.Ldw_str_begin+10754
	.data.b	43
	.data.b	29
	.data.b	75
	.data.w	.Ldw_begin+781
	.data.b	1
	.data.b	1

	.data.b	8
	.section	.debug_str		;off: 10768
	.data.b	68,109,97,95,67,111,110,102,105,103,83,101,116,0
	.section	.debug_info		;off: 9586
	.data.w	.Ldw_str_begin+10768
	.data.b	51
	.data.b	29
	.data.b	82
	.data.w	.Ldw_begin+802
	.data.b	1
	.data.b	1

	.data.b	6
	.section	.debug_str		;off: 10782
	.data.b	68,115,97,100,99,95,68,101,109,111,73,110,105,116,83,116,97,116,117,115,67,111,114,101,48,0
	.section	.debug_info		;off: 9600
	.data.w	.Ldw_str_begin+10782
	.data.b	55
	.data.b	14
	.data.b	1
	.data.w	.Ldw_begin+1154
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Dsadc_DemoInitStatusCore0..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.

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

	.section	.debug_info		;off: 9619
	.data.b	6
	.section	.debug_str		;off: 10808
	.data.b	68,115,97,100,99,95,68,101,109,111,67,105,114,99,117,108,97,114,66,117,102,102,101,114,70,117,108,108,70,108,97,103,0
	.section	.debug_info		;off: 9620
	.data.w	.Ldw_str_begin+10808
	.data.b	57
	.data.b	16
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Dsadc_DemoCircularBufferFullFlag..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.

	.data.b	6
	.section	.debug_str		;off: 10841
	.data.b	68,115,97,100,99,95,68,101,109,111,73,110,105,116,83,116,97,116,117,115,67,111,114,101,49,0
	.section	.debug_info		;off: 9640
	.data.w	.Ldw_str_begin+10841
	.data.b	66
	.data.b	14
	.data.b	1
	.data.w	.Ldw_begin+1154
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Dsadc_DemoInitStatusCore1..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.

	.data.b	6
	.section	.debug_str		;off: 10867
	.data.b	68,115,97,100,99,95,68,101,109,111,67,111,114,101,69,120,101,70,108,97,103,0
	.section	.debug_info		;off: 9660
	.data.w	.Ldw_str_begin+10867
	.data.b	76
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+4615
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Dsadc_DemoCoreExeFlag..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.

	.data.b	6
	.section	.debug_str		;off: 10889
	.data.b	68,115,97,100,99,68,101,109,111,95,77,97,105,110,67,111,110,118,82,101,115,117,108,116,0
	.section	.debug_info		;off: 9680
	.data.w	.Ldw_str_begin+10889
	.data.b	84
	.data.b	18
	.data.b	1
	.data.w	.Ldw_begin+818
	.data.b	1
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	DsadcDemo_MainConvResult

	.data.b	6
	.section	.debug_str		;off: 10914
	.data.b	68,115,97,100,99,68,101,109,111,95,77,97,115,116,101,114,67,111,114,101,73,110,105,116,70,108,97,103,0
	.section	.debug_info		;off: 9700
	.data.w	.Ldw_str_begin+10914
	.data.b	86
	.data.b	16
	.data.b	1
	.data.w	.Ldw_begin+1142
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	DsadcDemo_MasterCoreInitFlag..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.

	.data.b	6
	.section	.debug_str		;off: 10943
	.data.b	68,115,97,100,99,95,68,101,109,111,67,111,114,101,73,110,105,116,83,116,97,116,117,115,0
	.section	.debug_info		;off: 9720
	.data.w	.Ldw_str_begin+10943
	.data.b	94
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+839
	.data.b	0
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	Dsadc_DemoCoreInitStatus..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.

	.data.b	27
	.section	.debug_str		;off: 10968
	.data.b	77,117,108,116,105,99,111,114,101,95,71,101,116,67,111,114,101,73,68,0
	.section	.debug_info		;off: 9740
	.data.w	.Ldw_str_begin+10968
	.data.b	63
	.data.b	31
	.data.b	15
	.data.w	.Ldw_begin+1393
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

	.section	.debug_info		;off: 9757
	.data.b	37

	.section	.debug_abbrev		;off: 293
	.data.b	37
	.data.b	11
	.data.b	1
	.data.b	0,0

	.section	.debug_info		;off: 9758
	.data.b	8
	.section	.debug_str		;off: 10988
	.data.b	105,100,0
	.section	.debug_info		;off: 9759
	.data.w	.Ldw_str_begin+10988
	.data.b	65
	.data.b	17
	.data.b	15
	.data.w	.Ldw_begin+1393
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 10991
	.data.b	68,115,97,100,99,95,73,110,105,116,0
	.section	.debug_info		;off: 9775
	.data.w	.Ldw_str_begin+10991
	.data.b	135,2
	.data.b	38
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

	.section	.debug_info		;off: 9789
	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11002
	.data.b	68,115,97,100,99,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 9791
	.data.w	.Ldw_str_begin+11002
	.data.b	141,2
	.data.b	38
	.data.b	9
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11015
	.data.b	68,115,97,100,99,95,83,101,116,117,112,82,101,115,117,108,116,66,117,102,102,101,114,0
	.section	.debug_info		;off: 9807
	.data.w	.Ldw_str_begin+11015
	.data.b	148,2
	.data.b	48
	.data.b	9
	.data.w	.Ldw_begin+1226
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11039
	.data.b	68,115,97,100,99,95,83,116,97,114,116,67,111,110,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 9827
	.data.w	.Ldw_str_begin+11039
	.data.b	156,2
	.data.b	48
	.data.b	9
	.data.w	.Ldw_begin+1226
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11061
	.data.b	68,115,97,100,99,95,83,116,111,112,67,111,110,118,101,114,115,105,111,110,0
	.section	.debug_info		;off: 9847
	.data.w	.Ldw_str_begin+11061
	.data.b	161,2
	.data.b	48
	.data.b	9
	.data.w	.Ldw_begin+1226
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11082
	.data.b	68,115,97,100,99,95,71,101,116,83,116,114,101,97,109,76,97,115,116,80,111,105,110,116,101,114,0
	.section	.debug_info		;off: 9867
	.data.w	.Ldw_str_begin+11082
	.data.b	167,2
	.data.b	53
	.data.b	9
	.data.w	.Ldw_begin+3643
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11109
	.data.b	68,115,97,100,99,95,71,101,116,67,104,97,110,110,101,108,83,116,97,116,117,115,0
	.section	.debug_info		;off: 9887
	.data.w	.Ldw_str_begin+11109
	.data.b	176,2
	.data.b	50
	.data.b	9
	.data.w	.Ldw_begin+3714
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11132
	.data.b	68,115,97,100,99,95,71,101,116,84,105,109,101,115,116,97,109,112,0
	.section	.debug_info		;off: 9907
	.data.w	.Ldw_str_begin+11132
	.data.b	207,2
	.data.b	53
	.data.b	9
	.data.w	.Ldw_begin+3631
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11151
	.data.b	68,115,97,100,99,95,69,110,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 9927
	.data.w	.Ldw_str_begin+11151
	.data.b	214,2
	.data.b	38
	.data.b	9
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11176
	.data.b	68,115,97,100,99,95,68,105,115,97,98,108,101,78,111,116,105,102,105,99,97,116,105,111,110,0
	.section	.debug_info		;off: 9943
	.data.w	.Ldw_str_begin+11176
	.data.b	219,2
	.data.b	38
	.data.b	9
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11202
	.data.b	68,115,97,100,99,95,71,101,116,86,101,114,115,105,111,110,73,110,102,111,0
	.section	.debug_info		;off: 9959
	.data.w	.Ldw_str_begin+11202
	.data.b	226,2
	.data.b	37
	.data.b	9
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11223
	.data.b	73,110,116,99,95,68,105,115,97,98,108,101,73,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 9975
	.data.w	.Ldw_str_begin+11223
	.data.b	119
	.data.b	37
	.data.b	40
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11245
	.data.b	73,110,116,99,95,69,110,97,98,108,101,73,110,116,101,114,114,117,112,116,0
	.section	.debug_info		;off: 9990
	.data.w	.Ldw_str_begin+11245
	.data.b	124
	.data.b	37
	.data.b	40
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11266
	.data.b	84,105,109,101,114,95,68,101,108,97,121,77,115,0
	.section	.debug_info		;off: 10005
	.data.w	.Ldw_str_begin+11266
	.data.b	51
	.data.b	13
	.data.b	47
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11280
	.data.b	84,109,99,80,114,105,110,116,102,0
	.section	.debug_info		;off: 10020
	.data.w	.Ldw_str_begin+11280
	.data.b	176,1
	.data.b	14
	.data.b	50
	.data.w	.Ldw_begin+1154
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	27
	.section	.debug_str		;off: 11290
	.data.b	103,101,116,67,104,97,114,0
	.section	.debug_info		;off: 10040
	.data.w	.Ldw_str_begin+11290
	.data.b	177,1
	.data.b	13
	.data.b	50
	.data.w	.Ldw_begin+153
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11298
	.data.b	80,119,109,95,73,110,105,116,0
	.section	.debug_info		;off: 10060
	.data.w	.Ldw_str_begin+11298
	.data.b	124
	.data.b	36
	.data.b	64
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11307
	.data.b	80,119,109,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 10075
	.data.w	.Ldw_str_begin+11307
	.data.b	130,1
	.data.b	36
	.data.b	64
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11318
	.data.b	68,109,97,95,73,110,105,116,0
	.section	.debug_info		;off: 10091
	.data.w	.Ldw_str_begin+11318
	.data.b	236,1
	.data.b	36
	.data.b	76
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11327
	.data.b	68,109,97,95,68,101,73,110,105,116,0
	.section	.debug_info		;off: 10107
	.data.w	.Ldw_str_begin+11327
	.data.b	242,1
	.data.b	36
	.data.b	76
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11338
	.data.b	68,109,97,95,67,104,97,110,110,101,108,83,116,97,114,116,0
	.section	.debug_info		;off: 10123
	.data.w	.Ldw_str_begin+11338
	.data.b	248,1
	.data.b	36
	.data.b	76
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	26
	.section	.debug_str		;off: 11355
	.data.b	68,109,97,95,67,104,97,110,110,101,108,67,97,110,99,101,108,0
	.section	.debug_info		;off: 10139
	.data.w	.Ldw_str_begin+11355
	.data.b	254,1
	.data.b	36
	.data.b	76
	.data.b	1
	.data.b	0
	.data.b	1
	.data.b	1
	.data.b	0
	.data.b	1

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 11373
	.data.b	68,115,97,100,99,95,82,101,115,117,108,116,50,86,111,108,116,97,103,101,68,105,102,102,0
	.section	.debug_info		;off: 10155
	.data.w	.Ldw_str_begin+11373
	.data.b	155,1
	.data.b	16
	.data.b	1
	.data.w	.Ldw_begin+1214
	.data.w	Dsadc_Result2VoltageDiff..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.w	__ghs_eofn_Dsadc_Result2VoltageDiff
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

	.section	.debug_abbrev		;off: 323
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
	.data.w	Dsadc_Result2VoltageDiff..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.w	__ghs_eofn_Dsadc_Result2VoltageDiff-Dsadc_Result2VoltageDiff..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.b	1
	.data.w	.LDW21
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3505
	.data.b	0,5,2
	.data.w	Dsadc_Result2VoltageDiff..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.b	6
	.data.b	3
	.data.b	158,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	108
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 10188
	.data.b	22
	.section	.debug_str		;off: 11398
	.data.b	82,101,115,117,108,116,86,97,108,0
	.section	.debug_info		;off: 10189
	.data.w	.Ldw_str_begin+11398
	.data.b	155,1
	.data.b	48
	.data.b	1
	.data.w	.Ldw_begin+1166
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

	.section	.debug_abbrev		;off: 371
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

	.section	.debug_info		;off: 10206
	.data.b	34
	.data.w	.LDW11
	.data.w	.LDW21

	.section	.debug_abbrev		;off: 390
	.data.b	34
	.data.b	11
	.data.b	1
	.data.b	17,1
	.data.b	18,1
	.data.b	0,0

	.section	.debug_info		;off: 10215
	.data.b	7
	.section	.debug_str		;off: 11408
	.data.b	86,111,108,116,0
	.section	.debug_info		;off: 10216
	.data.w	.Ldw_str_begin+11408
	.data.b	157,1
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1214
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+19
	.section	.debug_loc		;off: 19
	.data.w	.LDW11
	.data.w	.LDW21
	.data.b	3,0
	.data.b	144
	.data.b	246,1
	.data.w	0x0
	.data.w	0x0

	.section	.debug_abbrev		;off: 399
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

	.section	.debug_info		;off: 10234
	.data.b	0

	.data.b	0

	.data.b	25
	.section	.debug_str		;off: 11413
	.data.b	68,115,97,100,99,95,82,101,115,117,108,116,50,86,111,108,116,97,103,101,83,105,110,103,108,101,0
	.section	.debug_info		;off: 10237
	.data.w	.Ldw_str_begin+11413
	.data.b	187,1
	.data.b	16
	.data.b	1
	.data.w	.Ldw_begin+1214
	.data.w	Dsadc_Result2VoltageSingle..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.w	__ghs_eofn_Dsadc_Result2VoltageSingle
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
	.data.w	Dsadc_Result2VoltageSingle..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.w	__ghs_eofn_Dsadc_Result2VoltageSingle-Dsadc_Result2VoltageSingle..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.b	1
	.data.w	.LDW51
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3525
	.data.b	0,5,2
	.data.w	Dsadc_Result2VoltageSingle..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.b	6
	.data.b	3
	.data.b	190,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	108
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 10270
	.data.b	22
	.section	.debug_str		;off: 11440
	.data.b	82,101,115,117,108,116,86,97,108,0
	.section	.debug_info		;off: 10271
	.data.w	.Ldw_str_begin+11440
	.data.b	187,1
	.data.b	50
	.data.b	1
	.data.w	.Ldw_begin+1166
	.data.b	0
	.data.w	.Ldw_loc_begin+40
	.section	.debug_loc		;off: 40
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10288
	.data.b	34
	.data.w	.LDW41
	.data.w	.LDW51

	.data.b	7
	.section	.debug_str		;off: 11450
	.data.b	86,111,108,116,0
	.section	.debug_info		;off: 10298
	.data.w	.Ldw_str_begin+11450
	.data.b	189,1
	.data.b	13
	.data.b	1
	.data.w	.Ldw_begin+1214
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+59
	.section	.debug_loc		;off: 59
	.data.w	.LDW41
	.data.w	.LDW51
	.data.b	3,0
	.data.b	144
	.data.b	246,1
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10316
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 11455
	.data.b	68,115,97,100,99,95,83,105,110,103,108,101,65,99,99,101,115,115,67,111,110,118,101,114,115,105,111,110,68,101,109,111,0
	.section	.debug_info		;off: 10319
	.data.w	.Ldw_str_begin+11455
	.data.b	218,1
	.data.b	13
	.data.b	1
	.data.w	Dsadc_SingleAccessConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.w	__ghs_eofn_Dsadc_SingleAccessConversionDemo
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

	.section	.debug_abbrev		;off: 420
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
	.data.w	Dsadc_SingleAccessConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.w	__ghs_eofn_Dsadc_SingleAccessConversionDemo-Dsadc_SingleAccessConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.b	1
	.data.w	.LDW81
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3545
	.data.b	0,5,2
	.data.w	Dsadc_SingleAccessConversionDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.b	6
	.data.b	3
	.data.b	218,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	43
	.data.b	45
	.data.b	43
	.data.b	45
	.data.b	59
	.data.b	43
	.data.b	13
	.data.b	28
	.data.b	43
	.data.b	45
	.data.b	27
	.data.b	60
	.data.b	13
	.data.b	77
	.data.b	60
	.data.b	59
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	28
	.data.b	44
	.data.b	27
	.data.b	43
	.data.b	13
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	105
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	34
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	12
	.data.b	11
	.data.b	3
	.data.b	115
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	11
	.data.b	11
	.data.b	75
	.data.b	123
	.data.b	75
	.data.b	75
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	107
	.data.b	59
	.data.b	43
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	43
	.data.b	44
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 10350
	.data.b	34
	.data.w	.LDW71
	.data.w	.LDW81

	.data.b	7
	.section	.debug_str		;off: 11488
	.data.b	77,97,105,110,67,104,83,116,97,116,117,115,0
	.section	.debug_info		;off: 10360
	.data.w	.Ldw_str_begin+11488
	.data.b	220,1
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+3714
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+80
	.section	.debug_loc		;off: 80
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10378
	.data.b	7
	.section	.debug_str		;off: 11501
	.data.b	65,117,120,67,104,83,116,97,116,117,115,0
	.section	.debug_info		;off: 10379
	.data.w	.Ldw_str_begin+11501
	.data.b	221,1
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+3714
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+99
	.section	.debug_loc		;off: 99
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10397
	.data.b	8
	.section	.debug_str		;off: 11513
	.data.b	69,114,114,0
	.section	.debug_info		;off: 10398
	.data.w	.Ldw_str_begin+11513
	.data.b	222,1
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1226
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 11517
	.data.b	84,101,109,112,95,82,101,115,117,108,116,66,117,102,0
	.section	.debug_info		;off: 10413
	.data.w	.Ldw_str_begin+11517
	.data.b	223,1
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+120
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 11532
	.data.b	84,105,109,101,115,116,97,109,112,86,97,108,117,101,0
	.section	.debug_info		;off: 10428
	.data.w	.Ldw_str_begin+11532
	.data.b	224,1
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+3631
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+118
	.section	.debug_loc		;off: 118
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10446
	.data.b	7
	.section	.debug_str		;off: 11547
	.data.b	87,97,105,116,76,111,111,112,0
	.section	.debug_info		;off: 10447
	.data.w	.Ldw_str_begin+11547
	.data.b	225,1
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+137
	.section	.debug_loc		;off: 137
	.data.w	.LDW71
	.data.w	.LDW81
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10465
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 11556
	.data.b	68,115,97,100,99,95,83,116,114,101,97,109,105,110,103,87,105,116,104,76,105,110,101,97,114,66,117,102,102,101,114,68,101,109,111,0
	.section	.debug_info		;off: 10468
	.data.w	.Ldw_str_begin+11556
	.data.b	199,2
	.data.b	13
	.data.b	1
	.data.w	Dsadc_StreamingWithLinearBufferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.w	__ghs_eofn_Dsadc_StreamingWithLinearBufferDemo
	.data.b	1
	.data.b	93
	.data.b	240,128,1
	.data.b	116
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
	.data.w	Dsadc_StreamingWithLinearBufferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.w	__ghs_eofn_Dsadc_StreamingWithLinearBufferDemo-Dsadc_StreamingWithLinearBufferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.b	1
	.data.w	.LDW12
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3645
	.data.b	0,5,2
	.data.w	Dsadc_StreamingWithLinearBufferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.b	6
	.data.b	3
	.data.b	199,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	43
	.data.b	45
	.data.b	60
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	77
	.data.b	13
	.data.b	59
	.data.b	43
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	43
	.data.b	61
	.data.b	44
	.data.b	2
	.data.b	4
	.data.b	12
	.data.b	44
	.data.b	59
	.data.b	43
	.data.b	12
	.data.b	91
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	32
	.data.b	1
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	11
	.data.b	11
	.data.b	60
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	40
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	12
	.data.b	3
	.data.b	114
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	116
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	27
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	91
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	43
	.data.b	43
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 10499
	.data.b	34
	.data.w	.LDW02
	.data.w	.LDW12

	.data.b	8
	.section	.debug_str		;off: 11592
	.data.b	82,101,115,117,108,116,76,111,111,112,0
	.section	.debug_info		;off: 10509
	.data.w	.Ldw_str_begin+11592
	.data.b	201,2
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+3643
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 11603
	.data.b	82,101,115,117,108,116,78,117,109,0
	.section	.debug_info		;off: 10524
	.data.w	.Ldw_str_begin+11603
	.data.b	202,2
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+3643
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 11613
	.data.b	69,114,114,0
	.section	.debug_info		;off: 10539
	.data.w	.Ldw_str_begin+11613
	.data.b	203,2
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1226
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 11617
	.data.b	82,101,115,117,108,116,80,116,114,0
	.section	.debug_info		;off: 10554
	.data.w	.Ldw_str_begin+11617
	.data.b	204,2
	.data.b	23
	.data.b	1
	.data.w	.Ldw_begin+139
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+156
	.section	.debug_loc		;off: 156
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	2,0
	.data.b	125
	.data.b	12
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10572
	.data.b	8
	.section	.debug_str		;off: 11627
	.data.b	67,104,83,116,97,116,117,115,0
	.section	.debug_info		;off: 10573
	.data.w	.Ldw_str_begin+11627
	.data.b	205,2
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+3714
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 11636
	.data.b	87,97,105,116,76,111,111,112,0
	.section	.debug_info		;off: 10588
	.data.w	.Ldw_str_begin+11636
	.data.b	206,2
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+176
	.section	.debug_loc		;off: 176
	.data.w	.LDW02
	.data.w	.LDW12
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10606
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 11645
	.data.b	68,115,97,100,99,95,83,116,114,101,97,109,105,110,103,87,105,116,104,67,105,114,99,117,108,97,114,66,117,102,102,101,114,68,101,109,111,0
	.section	.debug_info		;off: 10609
	.data.w	.Ldw_str_begin+11645
	.data.b	171,3
	.data.b	13
	.data.b	1
	.data.w	Dsadc_StreamingWithCircularBufferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.w	__ghs_eofn_Dsadc_StreamingWithCircularBufferDemo
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
	.data.w	Dsadc_StreamingWithCircularBufferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.w	__ghs_eofn_Dsadc_StreamingWithCircularBufferDemo-Dsadc_StreamingWithCircularBufferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.b	1
	.data.w	.LDW42
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3753
	.data.b	0,5,2
	.data.w	Dsadc_StreamingWithCircularBufferDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.b	6
	.data.b	3
	.data.b	171,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	43
	.data.b	44
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	93
	.data.b	12
	.data.b	29
	.data.b	59
	.data.b	43
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	45
	.data.b	43
	.data.b	61
	.data.b	44
	.data.b	2
	.data.b	4
	.data.b	12
	.data.b	43
	.data.b	59
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	22
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	12
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	0,5,2
	.data.w	.LDWlin1
	.data.b	3
	.data.b	112
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	12
	.data.b	11
	.data.b	11
	.data.b	59
	.data.b	29
	.data.b	3
	.data.b	125
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	12
	.data.b	1
	.data.b	12
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	76
	.data.b	43
	.data.b	2
	.data.b	12
	.data.b	0,1,1
	.section	.debug_info		;off: 10640
	.data.b	34
	.data.w	.LDW32
	.data.w	.LDW42

	.data.b	8
	.section	.debug_str		;off: 11683
	.data.b	82,101,115,117,108,116,76,111,111,112,0
	.section	.debug_info		;off: 10650
	.data.w	.Ldw_str_begin+11683
	.data.b	173,3
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+3643
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 11694
	.data.b	69,114,114,0
	.section	.debug_info		;off: 10665
	.data.w	.Ldw_str_begin+11694
	.data.b	174,3
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1226
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 11698
	.data.b	87,97,105,116,76,111,111,112,0
	.section	.debug_info		;off: 10680
	.data.w	.Ldw_str_begin+11698
	.data.b	175,3
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+195
	.section	.debug_loc		;off: 195
	.data.w	.LDW32
	.data.w	.LDW42
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10698
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 11707
	.data.b	68,115,97,100,99,95,83,105,110,103,108,101,65,99,99,101,115,115,67,111,110,118,101,114,115,105,111,110,87,105,116,104,68,109,97,68,101,109,111,0
	.section	.debug_info		;off: 10701
	.data.w	.Ldw_str_begin+11707
	.data.b	137,4
	.data.b	13
	.data.b	1
	.data.w	Dsadc_SingleAccessConversionWithDmaDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.w	__ghs_eofn_Dsadc_SingleAccessConversionWithDmaDemo
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

	.section	.debug_frame		;off: 264
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Dsadc_SingleAccessConversionWithDmaDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.w	__ghs_eofn_Dsadc_SingleAccessConversionWithDmaDemo-Dsadc_SingleAccessConversionWithDmaDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.b	1
	.data.w	.LDW72
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3866
	.data.b	0,5,2
	.data.w	Dsadc_SingleAccessConversionWithDmaDemo..D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5CDsadc_Demo.
	.data.b	6
	.data.b	3
	.data.b	137,4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	7
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	45
	.data.b	45
	.data.b	45
	.data.b	60
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	77
	.data.b	12
	.data.b	2
	.data.b	4
	.data.b	12
	.data.b	43
	.data.b	59
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	2
	.data.b	0
	.data.b	3
	.data.b	120
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	16
	.data.b	1
	.data.b	12
	.data.b	11
	.data.b	11
	.data.b	59
	.data.b	28
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	20
	.data.b	1
	.data.b	61
	.data.b	11
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	91
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	13
	.data.b	60
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 10732
	.data.b	34
	.data.w	.LDW62
	.data.w	.LDW72

	.data.b	8
	.section	.debug_str		;off: 11747
	.data.b	77,97,105,110,67,104,83,116,97,116,117,115,0
	.section	.debug_info		;off: 10742
	.data.w	.Ldw_str_begin+11747
	.data.b	139,4
	.data.b	22
	.data.b	1
	.data.w	.Ldw_begin+3714
	.data.b	0
	.data.b	0

	.data.b	8
	.section	.debug_str		;off: 11760
	.data.b	69,114,114,0
	.section	.debug_info		;off: 10757
	.data.w	.Ldw_str_begin+11760
	.data.b	140,4
	.data.b	20
	.data.b	1
	.data.w	.Ldw_begin+1226
	.data.b	0
	.data.b	0

	.data.b	7
	.section	.debug_str		;off: 11764
	.data.b	87,97,105,116,76,111,111,112,0
	.section	.debug_info		;off: 10772
	.data.w	.Ldw_str_begin+11764
	.data.b	141,4
	.data.b	12
	.data.b	1
	.data.w	.Ldw_begin+1190
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+214
	.section	.debug_loc		;off: 214
	.data.w	.LDW62
	.data.w	.LDW72
	.data.b	1,0
	.data.b	85
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10790
	.data.b	8
	.section	.debug_str		;off: 11773
	.data.b	82,101,115,117,108,116,76,111,111,112,0
	.section	.debug_info		;off: 10791
	.data.w	.Ldw_str_begin+11773
	.data.b	142,4
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1154
	.data.b	0
	.data.b	0

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 11784
	.data.b	68,115,97,100,99,95,68,101,109,111,69,110,116,114,121,0
	.section	.debug_info		;off: 10808
	.data.w	.Ldw_str_begin+11784
	.data.b	226,4
	.data.b	6
	.data.b	1
	.data.w	Dsadc_DemoEntry
	.data.w	__ghs_eofn_Dsadc_DemoEntry
	.data.b	1
	.data.b	93
	.data.b	240,129,1
	.data.b	112
	.data.b	0
	.data.b	36
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
	.data.w	Dsadc_DemoEntry
	.data.w	__ghs_eofn_Dsadc_DemoEntry-Dsadc_DemoEntry
	.data.b	1
	.data.w	.LDW03
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 3950
	.data.b	0,5,2
	.data.w	Dsadc_DemoEntry
	.data.b	6
	.data.b	3
	.data.b	226,4
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
	.data.b	60
	.data.b	27
	.data.b	12
	.data.b	43
	.data.b	59
	.data.b	59
	.data.b	124
	.data.b	59
	.data.b	59
	.data.b	59
	.data.b	60
	.data.b	60
	.data.b	59
	.data.b	60
	.data.b	27
	.data.b	43
	.data.b	11
	.data.b	6
	.data.b	12
	.data.b	6
	.data.b	11
	.data.b	12
	.data.b	11
	.data.b	27
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	43
	.data.b	11
	.data.b	43
	.data.b	11
	.data.b	27
	.data.b	59
	.data.b	11
	.data.b	43
	.data.b	11
	.data.b	27
	.data.b	59
	.data.b	12
	.data.b	11
	.data.b	59
	.data.b	11
	.data.b	27
	.data.b	43
	.data.b	27
	.data.b	61
	.data.b	28
	.data.b	27
	.data.b	43
	.data.b	12
	.data.b	11
	.data.b	59
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
	.data.b	183,127
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	202,0
	.data.b	2
	.data.b	8
	.data.b	1
	.data.b	11
	.data.b	2
	.data.b	8
	.data.b	0,1,1
	.section	.debug_info		;off: 10839
	.data.b	34
	.data.w	.LDW92
	.data.w	.LDW03

	.data.b	7
	.section	.debug_str		;off: 11800
	.data.b	67,109,100,0
	.section	.debug_info		;off: 10849
	.data.w	.Ldw_str_begin+11800
	.data.b	228,4
	.data.b	10
	.data.b	1
	.data.w	.Ldw_begin+153
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+233
	.section	.debug_loc		;off: 233
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	80
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10867
	.data.b	7
	.section	.debug_str		;off: 11804
	.data.b	69,120,105,116,70,108,97,103,0
	.section	.debug_info		;off: 10868
	.data.w	.Ldw_str_begin+11804
	.data.b	229,4
	.data.b	11
	.data.b	1
	.data.w	.Ldw_begin+1154
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+252
	.section	.debug_loc		;off: 252
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	1,0
	.data.b	86
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10886
	.data.b	7
	.section	.debug_str		;off: 11813
	.data.b	68,115,97,100,99,95,118,101,114,0
	.section	.debug_info		;off: 10887
	.data.w	.Ldw_str_begin+11813
	.data.b	230,4
	.data.b	25
	.data.b	1
	.data.w	.Ldw_begin+1325
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+271
	.section	.debug_loc		;off: 271
	.data.w	.LDW92
	.data.w	.LDW03
	.data.b	2,0
	.data.b	125
	.data.b	8
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10905
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 11823
	.data.b	68,115,97,100,99,95,68,101,109,111,0
	.section	.debug_info		;off: 10908
	.data.w	.Ldw_str_begin+11823
	.data.b	208,5
	.data.b	6
	.data.b	1
	.data.w	Dsadc_Demo
	.data.w	__ghs_eofn_Dsadc_Demo
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
	.data.w	Dsadc_Demo
	.data.w	__ghs_eofn_Dsadc_Demo-Dsadc_Demo
	.data.b	1
	.data.w	.LDW33
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4061
	.data.b	0,5,2
	.data.w	Dsadc_Demo
	.data.b	6
	.data.b	3
	.data.b	208,5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	29
	.data.b	2
	.data.b	4
	.data.b	0,5,2
	.data.w	.LDWlin2
	.data.b	2
	.data.b	0
	.data.b	0,5,2
	.data.w	.LDWlin3
	.data.b	12
	.data.b	6
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	3
	.data.b	116
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	3
	.data.b	126
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	6
	.data.b	125
	.data.b	11
	.data.b	107
	.data.b	12
	.data.b	43
	.data.b	3
	.data.b	7
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
	.data.b	3
	.data.b	18
	.data.b	2
	.data.b	36
	.data.b	1
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	3
	.data.b	110
	.data.b	2
	.data.b	4
	.data.b	1
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	11
	.data.b	11
	.data.b	27
	.data.b	28
	.data.b	11
	.data.b	11
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	4
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
	.data.b	12
	.data.b	43
	.data.b	11
	.data.b	43
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
	.section	.debug_info		;off: 10939
	.data.b	34
	.data.w	.LDW23
	.data.w	.LDW33

	.data.b	7
	.section	.debug_str		;off: 11834
	.data.b	67,111,114,101,73,100,0
	.section	.debug_info		;off: 10949
	.data.w	.Ldw_str_begin+11834
	.data.b	210,5
	.data.b	19
	.data.b	1
	.data.w	.Ldw_begin+1405
	.data.b	0
	.data.b	0
	.data.w	.Ldw_loc_begin+291
	.section	.debug_loc		;off: 291
	.data.w	.LDW23
	.data.w	.LDW33
	.data.b	1,0
	.data.b	84
	.data.w	0x0
	.data.w	0x0

	.section	.debug_info		;off: 10967
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 11841
	.data.b	68,115,97,100,99,68,101,109,111,95,67,105,114,99,117,108,97,114,66,117,102,102,101,114,70,117,108,108,0
	.section	.debug_info		;off: 10970
	.data.w	.Ldw_str_begin+11841
	.data.b	171,6
	.data.b	6
	.data.b	1
	.data.w	DsadcDemo_CircularBufferFull
	.data.w	__ghs_eofn_DsadcDemo_CircularBufferFull
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

	.section	.debug_frame		;off: 336
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	DsadcDemo_CircularBufferFull
	.data.w	__ghs_eofn_DsadcDemo_CircularBufferFull-DsadcDemo_CircularBufferFull
	.data.b	1
	.data.w	.LDW63
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 4185
	.data.b	0,5,2
	.data.w	DsadcDemo_CircularBufferFull
	.data.b	6
	.data.b	3
	.data.b	171,6
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	59
	.data.b	28
	.data.b	76
	.data.b	12
	.data.b	43
	.data.b	2
	.data.b	0
	.data.b	11
	.data.b	2
	.data.b	4
	.data.b	0,1,1
	.section	.debug_info		;off: 11001
	.data.b	34
	.data.w	.LDW53
	.data.w	.LDW63

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
	.data.b	27
	.data.b	2
	.data.b	3
	.data.b	29
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
	.data.b	1
	.data.b	55
	.data.b	69,95,78,79,84,95,79,75,32,40,83,116,100,95,82,101,116,117,114,110,84,121,112,101,41,40,48,120,48,49,117,41,0
	.data.b	4
	.data.b	3
	.data.b	30
	.data.b	9
	.data.b	3
	.data.b	41
	.data.b	10
	.data.b	3
	.data.b	40
	.data.b	11
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
	.data.b	226,1
	.data.b	68,83,65,68,67,95,67,70,71,95,73,78,84,69,82,82,85,80,84,95,77,79,68,69,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	228,1
	.data.b	68,83,65,68,67,95,67,70,71,95,80,79,76,76,73,78,71,95,77,79,68,69,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	235,1
	.data.b	68,115,97,100,99,67,111,110,102,95,68,115,97,100,99,67,104,97,110,110,101,108,95,83,105,110,103,108,101,73,110,116,32,40,40,68,115,97,100,99,95,67,104,97,110,110,101,108,84,121,112,101,41,48,41,0
	.data.b	1
	.data.b	240,1
	.data.b	68,115,97,100,99,67,111,110,102,95,68,115,97,100,99,67,104,97,110,110,101,108,95,83,116,114,101,97,109,105,110,103,76,105,110,101,97,114,32,40,40,68,115,97,100,99,95,67,104,97,110,110,101,108,84,121,112,101,41,49
	.data.b	41,0
	.data.b	1
	.data.b	245,1
	.data.b	68,115,97,100,99,67,111,110,102,95,68,115,97,100,99,67,104,97,110,110,101,108,95,83,116,114,101,97,109,105,110,103,67,105,114,99,117,108,97,114,32,40,40,68,115,97,100,99,95,67,104,97,110,110,101,108,84,121,112,101
	.data.b	41,50,41,0
	.data.b	1
	.data.b	250,1
	.data.b	68,115,97,100,99,67,111,110,102,95,68,115,97,100,99,67,104,97,110,110,101,108,95,83,105,110,103,108,101,68,109,97,32,40,40,68,115,97,100,99,95,67,104,97,110,110,101,108,84,121,112,101,41,51,41,0
	.data.b	4
	.data.b	3
	.data.b	41
	.data.b	12
	.data.b	3
	.data.b	39
	.data.b	13
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
	.data.b	78
	.data.b	77,67,65,76,95,77,65,83,84,69,82,95,67,79,82,69,32,40,77,67,65,76,95,67,79,82,69,48,41,0
	.data.b	1
	.data.b	81
	.data.b	77,67,65,76,95,78,85,77,66,69,82,95,79,70,95,67,79,82,69,83,32,40,52,85,41,0
	.data.b	1
	.data.b	134,1
	.data.b	77,67,65,76,95,77,79,68,85,76,69,95,67,70,71,95,68,77,65,95,85,83,69,68,32,40,83,84,68,95,79,78,41,0
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
	.data.b	145,2
	.data.b	68,83,65,68,67,95,67,79,77,77,79,78,95,66,65,83,69,95,65,68,68,82,69,83,83,32,48,120,66,48,48,48,50,48,56,48,85,0
	.data.b	1
	.data.b	147,2
	.data.b	68,83,65,68,67,48,95,66,65,83,69,95,65,68,68,82,69,83,83,32,48,120,66,48,48,48,50,48,48,48,85,0
	.data.b	1
	.data.b	169,2
	.data.b	68,83,65,68,67,48,32,40,40,68,83,65,68,67,95,77,79,68,85,76,69,32,42,41,40,68,83,65,68,67,48,95,66,65,83,69,95,65,68,68,82,69,83,83,41,41,0
	.data.b	1
	.data.b	189,2
	.data.b	68,83,65,68,67,95,67,79,77,77,79,78,95,77,79,68,85,76,69,32,40,40,68,83,65,68,67,95,67,79,77,77,79,78,32,42,41,40,68,83,65,68,67,95,67,79,77,77,79,78,95,66,65,83,69,95,65,68,68,82
	.data.b	69,83,83,41,41,0
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
	.data.b	145,1
	.data.b	77,67,65,76,95,67,79,82,69,48,32,40,77,85,76,84,73,67,79,82,69,73,68,95,67,80,85,48,41,0
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
	.data.b	43
	.data.b	34
	.data.b	3
	.data.b	45
	.data.b	35
	.data.b	4
	.data.b	3
	.data.b	46
	.data.b	36
	.data.b	1
	.data.b	207,2
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	209,2
	.data.b	37
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
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	47
	.data.b	38
	.data.b	4
	.data.b	1
	.data.b	231,1
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	233,1
	.data.b	37
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
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	43
	.data.b	39
	.data.b	1
	.data.b	47
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	48
	.data.b	37
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
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	132,2
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	133,2
	.data.b	37
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
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	35
	.data.b	68,83,65,68,67,95,68,69,77,79,95,67,79,78,86,69,82,83,73,79,78,95,78,85,77,32,40,49,48,85,41,0
	.data.b	1
	.data.b	40
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67
	.data.b	72,69,65,66,76,69,32,0
	.data.b	3
	.data.b	41
	.data.b	37
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
	.data.b	45
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72
	.data.b	69,65,66,76,69,32,0
	.data.b	3
	.data.b	46
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	59
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	60
	.data.b	37
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
	.data.b	67
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	68
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	31
	.data.b	40
	.data.b	3
	.data.b	34
	.data.b	41
	.data.b	4
	.data.b	3
	.data.b	35
	.data.b	42
	.data.b	3
	.data.b	34
	.data.b	43
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
	.data.b	247,31
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,52,51,57,32,40,52,51,57,85,41,0
	.data.b	1
	.data.b	253,31
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,52,52,48,32,40,52,52,48,85,41,0
	.data.b	1
	.data.b	131,32
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,52,52,49,32,40,52,52,49,85,41,0
	.data.b	1
	.data.b	137,32
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,52,52,50,32,40,52,52,50,85,41,0
	.data.b	1
	.data.b	143,32
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,52,52,51,32,40,52,52,51,85,41,0
	.data.b	1
	.data.b	149,32
	.data.b	73,78,84,67,95,73,78,84,83,82,67,95,78,85,77,95,52,52,52,32,40,52,52,52,85,41,0
	.data.b	4
	.data.b	3
	.data.b	37
	.data.b	44
	.data.b	1
	.data.b	187,21
	.data.b	73,78,84,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	188,21
	.data.b	45
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
	.data.b	45
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	37
	.data.b	46
	.data.b	4
	.data.b	1
	.data.b	110
	.data.b	73,78,84,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	111
	.data.b	45
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
	.data.b	45
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	32
	.data.b	47
	.data.b	4
	.data.b	3
	.data.b	33
	.data.b	48
	.data.b	1
	.data.b	22
	.data.b	68,69,77,79,95,67,79,77,77,79,78,95,72,95,32,0
	.data.b	3
	.data.b	30
	.data.b	49
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
	.data.b	50
	.data.b	3
	.data.b	35
	.data.b	51
	.data.b	1
	.data.b	20
	.data.b	95,83,84,68,65,82,71,95,72,32,0
	.data.b	3
	.data.b	38
	.data.b	52
	.data.b	1
	.data.b	31
	.data.b	95,95,95,103,104,115,95,100,105,100,95,112,97,99,107,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	36
	.data.b	53
	.data.b	3
	.data.b	36
	.data.b	54
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
	.data.b	55
	.data.b	3
	.data.b	41
	.data.b	56
	.data.b	3
	.data.b	26
	.data.b	57
	.data.b	4
	.data.b	1
	.data.b	239,2
	.data.b	65,83,73,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	241,2
	.data.b	58
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
	.data.b	58
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	38
	.data.b	59
	.data.b	4
	.data.b	3
	.data.b	39
	.data.b	60
	.data.b	4
	.data.b	1
	.data.b	140,1
	.data.b	85,65,82,84,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	142,1
	.data.b	61
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
	.data.b	61
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	37
	.data.b	48
	.data.b	4
	.data.b	3
	.data.b	38
	.data.b	62
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
	.data.b	63
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
	.data.b	61
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
	.data.b	61
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
	.data.b	34
	.data.b	64
	.data.b	3
	.data.b	38
	.data.b	65
	.data.b	1
	.data.b	54
	.data.b	80,87,77,95,68,69,95,73,78,73,84,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	63
	.data.b	80,87,77,95,83,69,84,95,68,85,84,89,95,67,89,67,76,69,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	72
	.data.b	80,87,77,95,83,69,84,95,80,69,82,73,79,68,95,65,78,68,95,68,85,84,89,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	81
	.data.b	80,87,77,95,83,69,84,95,79,85,84,80,85,84,95,84,79,95,73,68,76,69,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	89
	.data.b	80,87,77,95,86,69,82,83,73,79,78,95,73,78,70,79,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	98
	.data.b	80,87,77,95,71,69,84,95,79,85,84,80,85,84,95,83,84,65,84,69,95,65,80,73,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	172,1
	.data.b	80,87,77,95,68,85,84,89,95,83,72,73,70,84,95,73,78,95,84,73,67,75,83,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	174,1
	.data.b	80,87,77,95,72,65,78,68,76,69,95,83,72,73,70,84,95,66,89,95,79,70,70,83,69,84,32,40,83,84,68,95,79,70,70,41,0
	.data.b	1
	.data.b	176,1
	.data.b	80,87,77,95,78,79,84,73,70,73,67,65,84,73,79,78,95,83,85,80,80,79,82,84,69,68,32,40,83,84,68,95,79,78,41,0
	.data.b	1
	.data.b	178,1
	.data.b	80,87,77,95,48,95,49,48,48,95,73,78,84,69,82,82,85,80,84,95,72,65,78,68,76,69,32,40,83,84,68,95,79,78,41,0
	.data.b	4
	.data.b	3
	.data.b	40
	.data.b	66
	.data.b	3
	.data.b	37
	.data.b	67
	.data.b	3
	.data.b	33
	.data.b	68
	.data.b	3
	.data.b	44
	.data.b	69
	.data.b	3
	.data.b	33
	.data.b	70
	.data.b	4
	.data.b	1
	.data.b	39
	.data.b	71,84,77,95,82,69,71,95,67,72,69,67,75,32,0
	.data.b	1
	.data.b	213,1
	.data.b	71,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	215,1
	.data.b	71
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
	.data.b	71
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	112
	.data.b	71,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	114
	.data.b	71
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
	.data.b	144,8
	.data.b	71,84,77,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	146,8
	.data.b	71
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	34
	.data.b	72
	.data.b	1
	.data.b	158,1
	.data.b	71,84,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	160,1
	.data.b	71
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
	.data.b	71
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	193,1
	.data.b	80,87,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	195,1
	.data.b	73
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,80,87,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	232,3
	.data.b	80,87,77,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	234,3
	.data.b	73
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	41
	.data.b	74
	.data.b	4
	.data.b	3
	.data.b	42
	.data.b	75
	.data.b	1
	.data.b	39
	.data.b	80,87,77,95,83,84,65,82,84,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	40
	.data.b	73
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	169,1
	.data.b	73,78,83,73,68,69,95,80,87,77,95,83,84,65,82,84,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	1
	.data.b	172,1
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	47
	.data.b	80,87,77,95,83,84,79,80,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	48
	.data.b	73
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	121
	.data.b	80,87,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	122
	.data.b	73
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	195,25
	.data.b	73,78,83,73,68,69,95,80,87,77,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	1
	.data.b	198,25
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	200,1
	.data.b	80,87,77,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	201,1
	.data.b	73
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	36
	.data.b	76
	.data.b	3
	.data.b	36
	.data.b	77
	.data.b	3
	.data.b	40
	.data.b	78
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
	.data.b	253,25
	.data.b	68,109,97,67,111,110,102,95,68,109,97,67,104,97,110,110,101,108,95,68,115,97,100,99,51,32,40,40,68,109,97,95,67,104,97,110,110,101,108,84,121,112,101,41,49,55,41,0
	.data.b	4
	.data.b	3
	.data.b	42
	.data.b	79
	.data.b	3
	.data.b	41
	.data.b	80
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
	.data.b	81
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
	.data.b	81
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	38
	.data.b	82
	.data.b	1
	.data.b	47
	.data.b	68,77,65,95,83,84,65,82,84,95,83,69,67,95,67,79,78,70,73,71,95,68,65,84,65,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	48
	.data.b	81
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
	.data.b	81
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
	.data.b	81
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
	.data.b	81
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	1
	.data.b	42
	.data.b	68,83,65,68,67,95,67,79,78,86,69,82,83,73,79,78,95,87,65,73,84,95,84,73,77,69,79,85,84,32,40,49,48,48,48,85,41,0
	.data.b	1
	.data.b	45
	.data.b	68,83,65,68,67,95,83,84,82,69,65,77,73,78,71,95,76,73,78,69,65,82,95,66,85,70,70,69,82,95,83,65,77,80,76,69,95,78,85,77,32,40,53,85,41,0
	.data.b	1
	.data.b	46
	.data.b	68,83,65,68,67,95,83,84,82,69,65,77,73,78,71,95,67,73,82,67,85,76,65,82,95,66,85,70,70,69,82,95,83,65,77,80,76,69,95,78,85,77,32,40,49,48,85,41,0
	.data.b	1
	.data.b	52
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	53
	.data.b	37
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
	.data.b	59
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,48,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	60
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	63
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	64
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	237,41
	.data.b	73,78,83,73,68,69,95,68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32
	.data.b	0
	.data.b	1
	.data.b	240,41
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	68
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,67,79,82,69,49,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	69
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	73
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,73,78,73,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69,65
	.data.b	66,76,69,32,0
	.data.b	3
	.data.b	74
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	237,8
	.data.b	73,78,83,73,68,69,95,68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,73,78,73,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79
	.data.b	95,67,65,67,72,69,65,66,76,69,32,0
	.data.b	1
	.data.b	240,8
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	78
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,73,78,73,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72,69,65,66
	.data.b	76,69,32,0
	.data.b	3
	.data.b	79
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	81
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67
	.data.b	72,69,65,66,76,69,32,0
	.data.b	3
	.data.b	82
	.data.b	37
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
	.data.b	88
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,86,65,82,95,67,76,69,65,82,69,68,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,95,78,79,95,67,65,67,72
	.data.b	69,65,66,76,69,32,0
	.data.b	3
	.data.b	89
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	91
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	92
	.data.b	37
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
	.data.b	100
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,78,83,84,95,65,83,73,76,95,68,95,71,76,79,66,65,76,95,85,78,83,80,69,67,73,70,73,69,68,32,0
	.data.b	3
	.data.b	101
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	118
	.data.b	68,83,65,68,67,95,83,84,65,82,84,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	119
	.data.b	37
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
	.data.b	183,6
	.data.b	68,83,65,68,67,95,83,84,79,80,95,83,69,67,95,67,79,68,69,95,65,83,73,76,95,68,95,71,76,79,66,65,76,32,0
	.data.b	3
	.data.b	184,6
	.data.b	37
	.data.b	1
	.data.b	29
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	0
	.section	.debug_abbrev		;off: 466
	.data.b	0
