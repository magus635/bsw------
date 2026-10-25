	.weak	Exception_GetIntVectorInfo
	.weak	EL2_GetExceptionInformation
	.weak	EL1_GetExceptionInformation
	.weak	Exception_UndefinedCallback
	.weak	Exception_PrefetchAbortCallback
	.weak	Exception_DataAbortCallback
	.weak	EL2_UndefinedException
	.weak	EL2_HVCHandler
	.weak	EL2_PrefetchAbortException
	.weak	EL2_DataAbortException
	.weak	EL2_HypModeEntryHandler
	.weak	EL2_IRQHandler
	.weak	EL2_FIQHandler
	.weak	EL1_Reserved
	.weak	readExceptionRegInfo
	.weak	EL1_SVCHandler
	.weak	EL1_UndefinedException
	.weak	EL1_PrefetchAbortException
	.weak	EL1_DataAbortException
	.weak	EL1_IRQHandler
	.weak	EL1_FIQHandler
	.weak	dummp
	.section ".exceptionHandler","ax"
	.align	4
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cexception...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68257C..0::
..gh.f.a.1.e.0:
	.endo	..gh.f.a.1.e.0
	.weak	__callee.Exception_GetIntVectorInfo.v.v
__callee.Exception_GetIntVectorInfo.v.v::
	.size	__callee.Exception_GetIntVectorInfo.v.v,0
Exception_GetIntVectorInfo::
.LDW01:
.LDW11:
..gh.beginasm.1:
	.endo	..gh.beginasm.1
 cmp r0, #0x0    
 beq stepFail    
 cmp r1, #0x0  
 beq stepFail    
 ldr r2, =GICIsrVectorTable  
 str r2, [r0]    
 mov r2, #992    
 str r2, [r1]    
 mov  r0, #0x0   
 b stepFinish    
stepFail: mov r0, #0xFFFFFFFF  
stepFinish: blx lr 

..gh.endasm.2:
	.endo	..gh.endasm.2

.LDW21:
;line90
..lin.64363837..283325fd.0_1::
	.weak	__ghs_eofn_Exception_GetIntVectorInfo
__ghs_eofn_Exception_GetIntVectorInfo::
	.endf	Exception_GetIntVectorInfo

	.section ".bss","awb"
.L39:
	.endo	.L39
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.3:
	.endo	..gh.f.a.1.e.3
	.weak	__callee.EL2_GetExceptionInformation.v.v
__callee.EL2_GetExceptionInformation.v.v::
	.size	__callee.EL2_GetExceptionInformation.v.v,0
EL2_GetExceptionInformation::
.LDW31:
.LDW41:
..gh.beginasm.4:
	.endo	..gh.beginasm.4
 ldr r1, =exceptionRegInformation 
 mov r2, #0x0 
 mov r3, r0   
 strd r2, r3, [r1], #0x8   
 mrc p15, 4, r2, c5, c2, 0 
 mrc p15, 4, r3, c5, c1, 1 
 strd r2, r3, [r1], #0x8   
 mrc p15, 4, r2, c6, c0, 4 
 mrc p15, 0, r3, c5, c1, 1 
 strd r2, r3, [r1], #0x8   
 mrc p15, 0, r2, c5, c1, 0 
 mrc p15, 0, r3, c6, c0, 0 
 strd r2, r3, [r1], #0x8   
 mrc p15, 0, r2, c5, c0, 0 
 mrc p15, 0, r3, c6, c0, 2 
 strd r2, r3, [r1], #0x8   
 mrc p15, 0, r2, c5, c0, 1  
 mrc p15, 0, r3, c12, c1, 0 
 strd r2, r3, [r1], #0x8    
 ldr r0, =exceptionRegInformation 
 blx lr 

..gh.endasm.5:
	.endo	..gh.endasm.5

.LDW51:
;line126
..lin.64363837..69271b1c.0_2::
	.weak	__ghs_eofn_EL2_GetExceptionInformation
__ghs_eofn_EL2_GetExceptionInformation::
	.endf	EL2_GetExceptionInformation

	.section ".bss","awb"
.L87:
	.endo	.L87
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.6:
	.endo	..gh.f.a.1.e.6
	.weak	__callee.EL1_GetExceptionInformation.v.v
__callee.EL1_GetExceptionInformation.v.v::
	.size	__callee.EL1_GetExceptionInformation.v.v,0
EL1_GetExceptionInformation::
.LDW61:
.LDW71:
..gh.beginasm.7:
	.endo	..gh.beginasm.7
 ldr r1, =exceptionRegInformation  
 mov r2, #0x1      
 mov r3, r0        
 strd r2, r3, [r1], #0x8           
 mov r2, #0x0      
 mov r3, #0x0      
 strd r2, r3, [r1], #0x8 
 mrc p15, 0, r3, c5, c1, 1 
 strd r2, r3, [r1], #0x8   
 mrc p15, 0, r2, c5, c1, 0 
 mrc p15, 0, r3, c6, c0, 0 
 strd r2, r3, [r1], #0x8   
 mrc p15, 0, r2, c5, c0, 0 
 mrc p15, 0, r3, c6, c0, 2 
 strd r2, r3, [r1], #0x8   
 mrc p15, 0, r2, c5, c0, 1     
 mrc p15, 0, r3, c12, c1, 0    
 strd r2, r3, [r1], #0x8       
 ldr r0, =exceptionRegInformation 
 blx lr 

..gh.endasm.8:
	.endo	..gh.endasm.8

.LDW81:
;line160
..lin.64363837..bd0ec81b.0_3::
	.weak	__ghs_eofn_EL1_GetExceptionInformation
__ghs_eofn_EL1_GetExceptionInformation::
	.endf	EL1_GetExceptionInformation

	.section ".bss","awb"
.L135:
	.endo	.L135
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.9:
	.endo	..gh.f.a.1.e.9
	.weak	__callee.Exception_UndefinedCallback.v.v
__callee.Exception_UndefinedCallback.v.v::
	.size	__callee.Exception_UndefinedCallback.v.v,0
Exception_UndefinedCallback::
.LDW91:
.LDW02:
..gh.beginasm.10:
	.endo	..gh.beginasm.10
 b Exception_UndefinedCallback  

..gh.endasm.11:
	.endo	..gh.endasm.11

.LDW12:
;line169
..lin.64363837..d0dad152.0_4::
	.weak	__ghs_eofn_Exception_UndefinedCallback
__ghs_eofn_Exception_UndefinedCallback::
	.endf	Exception_UndefinedCallback

	.section ".bss","awb"
.L183:
	.endo	.L183
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.12:
	.endo	..gh.f.a.1.e.12
	.weak	__callee.Exception_PrefetchAbortCallback.v.v
__callee.Exception_PrefetchAbortCallback.v.v::
	.size	__callee.Exception_PrefetchAbortCallback.v.v,0
Exception_PrefetchAbortCallback::
.LDW22:
.LDW32:
..gh.beginasm.13:
	.endo	..gh.beginasm.13
 b Exception_PrefetchAbortCallback  

..gh.endasm.14:
	.endo	..gh.endasm.14

.LDW42:
;line178
..lin.64363837..e90f3c49.0_5::
	.weak	__ghs_eofn_Exception_PrefetchAbortCallback
__ghs_eofn_Exception_PrefetchAbortCallback::
	.endf	Exception_PrefetchAbortCallback

	.section ".bss","awb"
.L231:
	.endo	.L231
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.15:
	.endo	..gh.f.a.1.e.15
	.weak	__callee.Exception_DataAbortCallback.v.v
__callee.Exception_DataAbortCallback.v.v::
	.size	__callee.Exception_DataAbortCallback.v.v,0
Exception_DataAbortCallback::
.LDW52:
.LDW62:
..gh.beginasm.16:
	.endo	..gh.beginasm.16
 b Exception_DataAbortCallback  

..gh.endasm.17:
	.endo	..gh.endasm.17

.LDW72:
;line191
..lin.64363837..eb6f0f12.0_6::
	.weak	__ghs_eofn_Exception_DataAbortCallback
__ghs_eofn_Exception_DataAbortCallback::
	.endf	Exception_DataAbortCallback

	.section ".bss","awb"
.L279:
	.endo	.L279
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.18:
	.endo	..gh.f.a.1.e.18
	.weak	__callee.EL2_UndefinedException.v.v
__callee.EL2_UndefinedException.v.v::
	.size	__callee.EL2_UndefinedException.v.v,0
EL2_UndefinedException::
.LDW82:
.LDW92:
..gh.beginasm.19:
	.endo	..gh.beginasm.19
 b EL2_UndefinedException  
 eret 

..gh.endasm.20:
	.endo	..gh.endasm.20

.LDW03:
;line201
..lin.64363837..5fc20be8.0_7::
	.weak	__ghs_eofn_EL2_UndefinedException
__ghs_eofn_EL2_UndefinedException::
	.endf	EL2_UndefinedException

	.section ".bss","awb"
.L327:
	.endo	.L327
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.21:
	.endo	..gh.f.a.1.e.21
	.weak	__callee.EL2_HVCHandler.v.v
__callee.EL2_HVCHandler.v.v::
	.size	__callee.EL2_HVCHandler.v.v,0
EL2_HVCHandler::
.LDW13:
.LDW23:
..gh.beginasm.22:
	.endo	..gh.beginasm.22
 b EL2_HVCHandler  
 eret 

..gh.endasm.23:
	.endo	..gh.endasm.23

.LDW33:
;line211
..lin.64363837..4c820486.0_8::
	.weak	__ghs_eofn_EL2_HVCHandler
__ghs_eofn_EL2_HVCHandler::
	.endf	EL2_HVCHandler

	.section ".bss","awb"
.L375:
	.endo	.L375
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.24:
	.endo	..gh.f.a.1.e.24
	.weak	__callee.EL2_PrefetchAbortException.v.v
__callee.EL2_PrefetchAbortException.v.v::
	.size	__callee.EL2_PrefetchAbortException.v.v,0
EL2_PrefetchAbortException::
.LDW43:
.LDW53:
..gh.beginasm.25:
	.endo	..gh.beginasm.25
 b EL2_PrefetchAbortException  
 eret 

..gh.endasm.26:
	.endo	..gh.endasm.26

.LDW63:
;line221
..lin.64363837..4b1ffbf.0_9::
	.weak	__ghs_eofn_EL2_PrefetchAbortException
__ghs_eofn_EL2_PrefetchAbortException::
	.endf	EL2_PrefetchAbortException

	.section ".bss","awb"
.L423:
	.endo	.L423
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.27:
	.endo	..gh.f.a.1.e.27
	.weak	__callee.EL2_DataAbortException.v.v
__callee.EL2_DataAbortException.v.v::
	.size	__callee.EL2_DataAbortException.v.v,0
EL2_DataAbortException::
.LDW73:
.LDW83:
..gh.beginasm.28:
	.endo	..gh.beginasm.28
 push {r0-r12, lr}     
 mrs r0, elr_hyp       
 bl EL2_GetExceptionInformation   
 bl Exception_DataAbortCallback   
 pop {r0-r12, lr} 
 eret             

..gh.endasm.29:
	.endo	..gh.endasm.29

.LDW93:
;line235
..lin.64363837..ccde01a8.0_10::
	.weak	__ghs_eofn_EL2_DataAbortException
__ghs_eofn_EL2_DataAbortException::
	.endf	EL2_DataAbortException

	.section ".bss","awb"
.L471:
	.endo	.L471
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.30:
	.endo	..gh.f.a.1.e.30
	.weak	__callee.EL2_HypModeEntryHandler.v.v
__callee.EL2_HypModeEntryHandler.v.v::
	.size	__callee.EL2_HypModeEntryHandler.v.v,0
EL2_HypModeEntryHandler::
.LDW04:
.LDW14:
..gh.beginasm.31:
	.endo	..gh.beginasm.31
 b EL2_HypModeEntryHandler  
 eret 

..gh.endasm.32:
	.endo	..gh.endasm.32

.LDW24:
;line245
..lin.64363837..ac21512d.0_11::
	.weak	__ghs_eofn_EL2_HypModeEntryHandler
__ghs_eofn_EL2_HypModeEntryHandler::
	.endf	EL2_HypModeEntryHandler

	.section ".bss","awb"
.L519:
	.endo	.L519
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.33:
	.endo	..gh.f.a.1.e.33
	.weak	__callee.EL2_IRQHandler.v.v
__callee.EL2_IRQHandler.v.v::
	.size	__callee.EL2_IRQHandler.v.v,0
EL2_IRQHandler::
.LDW34:
.LDW44:
..gh.beginasm.34:
	.endo	..gh.beginasm.34
 b EL2_IRQHandler  
 eret 

..gh.endasm.35:
	.endo	..gh.endasm.35

.LDW54:
;line255
..lin.64363837..6a3475f1.0_12::
	.weak	__ghs_eofn_EL2_IRQHandler
__ghs_eofn_EL2_IRQHandler::
	.endf	EL2_IRQHandler

	.section ".bss","awb"
.L567:
	.endo	.L567
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.36:
	.endo	..gh.f.a.1.e.36
	.weak	__callee.EL2_FIQHandler.v.v
__callee.EL2_FIQHandler.v.v::
	.size	__callee.EL2_FIQHandler.v.v,0
EL2_FIQHandler::
.LDW64:
.LDW74:
..gh.beginasm.37:
	.endo	..gh.beginasm.37
 b EL2_FIQHandler  
 eret 

..gh.endasm.38:
	.endo	..gh.endasm.38

.LDW84:
;line265
..lin.64363837..45b4c985.0_13::
	.weak	__ghs_eofn_EL2_FIQHandler
__ghs_eofn_EL2_FIQHandler::
	.endf	EL2_FIQHandler

	.section ".bss","awb"
.L615:
	.endo	.L615
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.39:
	.endo	..gh.f.a.1.e.39
	.weak	__callee.EL1_Reserved.v.v
__callee.EL1_Reserved.v.v::
	.size	__callee.EL1_Reserved.v.v,0
EL1_Reserved::
.LDW94:
.LDW05:
..gh.beginasm.40:
	.endo	..gh.beginasm.40
 b EL1_Reserved  

..gh.endasm.41:
	.endo	..gh.endasm.41

.LDW15:
;line274
..lin.64363837..416a0fa6.0_14::
	.weak	__ghs_eofn_EL1_Reserved
__ghs_eofn_EL1_Reserved::
	.endf	EL1_Reserved

	.section ".bss","awb"
.L663:
	.endo	.L663
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.42:
	.endo	..gh.f.a.1.e.42
	.weak	__callee.readExceptionRegInfo.v.v
__callee.readExceptionRegInfo.v.v::
	.size	__callee.readExceptionRegInfo.v.v,0
readExceptionRegInfo::
.LDW25:
.LDW35:
..gh.beginasm.43:
	.endo	..gh.beginasm.43
 ldr r0, =exceptionRegInformation  
 blx lr  

..gh.endasm.44:
	.endo	..gh.endasm.44

.LDW45:
;line284
..lin.64363837..194e9d7a.0_15::
	.weak	__ghs_eofn_readExceptionRegInfo
__ghs_eofn_readExceptionRegInfo::
	.endf	readExceptionRegInfo

	.section ".bss","awb"
.L711:
	.endo	.L711
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.45:
	.endo	..gh.f.a.1.e.45
	.weak	__callee.EL1_SVCHandler.v.v
__callee.EL1_SVCHandler.v.v::
	.size	__callee.EL1_SVCHandler.v.v,0
EL1_SVCHandler::
.LDW55:
.LDW65:
..gh.beginasm.46:
	.endo	..gh.beginasm.46
 push {r0-r12, lr}  
 ldr r5, [lr, #-4]  
 bic r5, r5, #0xFF000000  
 cpsie i            
 cmp r4, #0         
 beq PopStack_SVC   
PopStack_SVC: pop {r0-r12, lr} 
 eret 

..gh.endasm.47:
	.endo	..gh.endasm.47

.LDW75:
;line300
..lin.64363837..4802e390.0_16::
	.weak	__ghs_eofn_EL1_SVCHandler
__ghs_eofn_EL1_SVCHandler::
	.endf	EL1_SVCHandler

	.section ".bss","awb"
.L759:
	.endo	.L759
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.48:
	.endo	..gh.f.a.1.e.48
	.weak	__callee.EL1_UndefinedException.v.v
__callee.EL1_UndefinedException.v.v::
	.size	__callee.EL1_UndefinedException.v.v,0
EL1_UndefinedException::
.LDW85:
.LDW95:
..gh.beginasm.49:
	.endo	..gh.beginasm.49
 push {r0-r12, lr}               
 mov r0, lr                      
 bl EL1_GetExceptionInformation  
 bl Exception_UndefinedCallback  
 cmp r0, #0                      
 beq ignore_undefinedInstruction 
 ldr r0, [sp, #0x34]             
 sub r0, r0, #4                  
 str r0, [sp, #0x34]             
ignore_undefinedInstruction: pop {r0-r12, lr} 
 eret  

..gh.endasm.50:
	.endo	..gh.endasm.50

.LDW06:
;line319
..lin.64363837..939add87.0_17::
	.weak	__ghs_eofn_EL1_UndefinedException
__ghs_eofn_EL1_UndefinedException::
	.endf	EL1_UndefinedException

	.section ".bss","awb"
.L807:
	.endo	.L807
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.51:
	.endo	..gh.f.a.1.e.51
	.weak	__callee.EL1_PrefetchAbortException.v.v
__callee.EL1_PrefetchAbortException.v.v::
	.size	__callee.EL1_PrefetchAbortException.v.v,0
EL1_PrefetchAbortException::
.LDW16:
.LDW26:
..gh.beginasm.52:
	.endo	..gh.beginasm.52
 sub lr, lr, #4     
 push {r0-r12, lr}  
 mov r0, lr         
 bl EL1_GetExceptionInformation      
 bl Exception_PrefetchAbortCallback  
 pop {r0-r12, lr}   
 eret               

..gh.endasm.53:
	.endo	..gh.endasm.53

.LDW36:
;line334
..lin.64363837..35c888de.0_18::
	.weak	__ghs_eofn_EL1_PrefetchAbortException
__ghs_eofn_EL1_PrefetchAbortException::
	.endf	EL1_PrefetchAbortException

	.section ".bss","awb"
.L855:
	.endo	.L855
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.54:
	.endo	..gh.f.a.1.e.54
	.weak	__callee.EL1_DataAbortException.v.v
__callee.EL1_DataAbortException.v.v::
	.size	__callee.EL1_DataAbortException.v.v,0
EL1_DataAbortException::
.LDW46:
.LDW56:
..gh.beginasm.55:
	.endo	..gh.beginasm.55
 sub lr, lr, #8                  
 push {r0-r12, lr}               
 mov r0, lr                      
 bl EL1_GetExceptionInformation  
 bl Exception_DataAbortCallback  
 cmp r0, #0                      
 bne try_dataabort_again         
 ldr r0, [sp, #0x34]             
 add r0, r0, #4                  
 str r0, [sp, #0x34]             
try_dataabort_again: pop {r0-r12, lr} 
 eret       

..gh.endasm.56:
	.endo	..gh.endasm.56

.LDW66:
;line354
..lin.64363837..b6d347.0_19::
	.weak	__ghs_eofn_EL1_DataAbortException
__ghs_eofn_EL1_DataAbortException::
	.endf	EL1_DataAbortException

	.section ".bss","awb"
.L903:
	.endo	.L903
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.57:
	.endo	..gh.f.a.1.e.57
	.weak	__callee.EL1_IRQHandler.v.v
__callee.EL1_IRQHandler.v.v::
	.size	__callee.EL1_IRQHandler.v.v,0
EL1_IRQHandler::
.LDW76:
.LDW86:
..gh.beginasm.58:
	.endo	..gh.beginasm.58
 sub lr, lr, #4     
 srsfd sp!, #0x13   
 cps  #0x13         
 push {r0-r12, lr}  
 VMRS R1, FPSCR     
 PUSH {R1}          
 VMRS R1, FPEXC     
 PUSH {R1}          
 vpush {d0-d15}     
 vpush {d16-d31}    
 and r1, sp, #4     
 sub sp, sp, r1     
 mrc p15,0,r0,c12,c12,0  
Hanlde_Another_IRQ: push {r0-r1}  
 cpsie i  
 ldr r1, =GICIsrVectorTable  
 ldr r1, [r1, r0, lsl #2]  
 blx r1  
 cpsid i  
 pop {r0-r1}  
 mrc p15, 0, r2, c12,c12,4  
 tst r2, #0x02  
 bne EOIMODE_Enable_IRQ  
 mcr p15, 0, r0, c12, c12, 1  
 isb  
 b   EOIMODE_Disable_IRQ  
EOIMODE_Enable_IRQ: mcr p15, 0, r0, c12, c11, 1  
 isb  
 b   EOIMODE_Disable_IRQ  
EOIMODE_Disable_IRQ: mrc p15, 0, r0, c12, c12, 0  
 ldr r2, =0x3FF  
 cmp r0, r2  
 bne Hanlde_Another_IRQ  
 add sp, sp, r1  
 vpop {d16-d31}  
 vpop {d0-d15}  
 POP {R1}  
 VMSR FPEXC, R1  
 POP {R1}  
 VMSR FPSCR, R1  
 pop {r0-r12, lr}  
 rfefd sp!  
 eret  

..gh.endasm.59:
	.endo	..gh.endasm.59

.LDW96:
;line438
..lin.64363837..39411890.0_20::
	.weak	__ghs_eofn_EL1_IRQHandler
__ghs_eofn_EL1_IRQHandler::
	.endf	EL1_IRQHandler

	.section ".bss","awb"
.L951:
	.endo	.L951
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.60:
	.endo	..gh.f.a.1.e.60
	.weak	__callee.EL1_FIQHandler.v.v
__callee.EL1_FIQHandler.v.v::
	.size	__callee.EL1_FIQHandler.v.v,0
EL1_FIQHandler::
.LDW07:
.LDW17:
..gh.beginasm.61:
	.endo	..gh.beginasm.61
 sub lr, lr, #4     
 srsfd sp!, #0x13   
 cps  #0x13         
 push {r0-r12, lr}  
 VMRS R1, FPSCR     
 PUSH {R1}          
 VMRS R1, FPEXC     
 PUSH {R1}          
 vpush {d0-d15}     
 vpush {d16-d31}    
 and r1, sp, #4     
 sub sp, sp, r1     
 mrc p15,0,r0,c12,c8,0  
Hanlde_Another_FIRQ: push {r0-r1}  
 cpsie f  
 ldr r1, =GICIsrVectorTable  
 ldr r1, [r1, r0, lsl #2]  
 blx r1  
 cpsid f  
 pop {r0-r1}  
 mrc p15, 0, r2, c12,c12,4  
 tst r2, #0x02  
 bne EOIMODE_Enable_FIRQ  
 mcr p15,0,r0,c12,c8,1  
 isb  
 b   EOIMODE_Disable_FIRQ  
EOIMODE_Enable_FIRQ: mcr p15, 0, r0, c12, c11, 1  
 isb  
EOIMODE_Disable_FIRQ: mrc p15,0,r0,c12,c8,0  
 ldr r2, =0x3FF  
 cmp r0, r2  
 bne Hanlde_Another_FIRQ  
 add sp, sp, r1  
 vpop {d16-d31}  
 vpop {d0-d15}  
 POP {R1}  
 VMSR FPEXC, R1  
 POP {R1}  
 VMSR FPSCR, R1  
 pop {r0-r12, lr}  
 rfefd sp!  
 eret  

..gh.endasm.62:
	.endo	..gh.endasm.62

.LDW27:
;line521
..lin.64363837..14c16c24.0_21::
	.weak	__ghs_eofn_EL1_FIQHandler
__ghs_eofn_EL1_FIQHandler::
	.endf	EL1_FIQHandler

	.section ".bss","awb"
.L999:
	.endo	.L999
	.section ".exceptionHandler","ax"
..gh.f.a.1.e.63:
	.endo	..gh.f.a.1.e.63
	.weak	__callee.dummp.v.v
__callee.dummp.v.v::
	.size	__callee.dummp.v.v,0
dummp::
.LDW37:
.LDW47:
..gh.beginasm.64:
	.endo	..gh.beginasm.64
 nop      
 b dummp  

..gh.endasm.65:
	.endo	..gh.endasm.65

.LDW57:
;line532
..lin.64363837..f529908.0_22::
	.weak	__ghs_eofn_dummp
__ghs_eofn_dummp::
	.endf	dummp

	.section ".bss","awb"
.L1047:
	.endo	.L1047
	.section ".exceptionHandler","ax"
	.text
..bof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cexception...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68257C..1::
	.global	__global.def.GICIsrVectorTable.a992_Ui
__global.def.GICIsrVectorTable.a992_Ui::
	.size	__global.def.GICIsrVectorTable.a992_Ui,0
;GICIsrVectorTable	GICIsrVectorTable	export
	.global	__global.def.exceptionRegInformation.a12_Ui
__global.def.exceptionRegInformation.a12_Ui::
	.size	__global.def.exceptionRegInformation.a12_Ui,0
;exceptionRegInformation	exceptionRegInformation	export

	.section ".exceptionRegInfo","aw"
	.align	4
exceptionRegInformation::	.data.b	255,255,255,255
	.space	44
	.endo	exceptionRegInformation
	.section ".IRQ_init_vector","aw"
	.align	4
GICIsrVectorTable::	.data.b	255,255,255,255
	.space	3964
	.endo	GICIsrVectorTable
	.data
	.ghsnote info, 29, 8195, 131712
	.text
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cexception...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68257C..1::
	.section ".exceptionHandler","ax"
..eof.D.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject.5CDebug.5Cexception...44.3A.5CAuto_ToolAndFirmware.5C12_MCAL.5C04_THA6412.5C04_Release.5CTMC_THA6_Series_MCAL_AS440_FuSa_V1.2E2.2E0.5C02_Code.5CTHA6XXX_MC_AS440.5CDemoWorkspace.5CCodeProject..6A68257C..0::
	.text
	.section	.debug_abbrev		;off: 0
.Ldw_abbr_begin:
	.section	.debug_str		;off: 0
.Ldw_str_begin:
	.section	.debug_info		;off: 0
.Ldw_begin:
	.data.b	118,4,0,0
	.data.b	2,0
	.data.w	.Ldw_abbr_begin
	.data.b	4
	.data.b	2
	.section	.debug_str		;off: 0
	.data.b	46,92,83,116,97,114,116,117,112,47,101,120,99,101,112,116,105,111,110,46,99,0
	.section	.debug_info		;off: 12
	.data.w	.Ldw_str_begin
	.section	.debug_str		;off: 22
	.data.b	68,58,92,65,117,116,111,95,84,111,111,108,65,110,100,70,105,114,109,119,97,114,101,92,49,50,95,77,67,65,76,92,48,52,95,84,72,65,54,52,49,50,92,48,52,95,82,101,108,101,97,115,101,92,84,77,67,95,84,72
	.data.b	65,54,95,83,101,114,105,101,115,95,77,67,65,76,95,65,83,52,52,48,95,70,117,83,97,95,86,49,46,50,46,48,92,48,50,95,67,111,100,101,92,84,72,65,54,88,88,88,95,77,67,95,65,83,52,52,48,92,68,101
	.data.b	109,111,87,111,114,107,115,112,97,99,101,92,67,111,100,101,80,114,111,106,101,99,116,0
	.section	.debug_info		;off: 16
	.data.w	.Ldw_str_begin+22
	.section	.debug_str		;off: 166
	.data.b	71,72,83,32,67,32,50,48,50,51,46,49,46,52,32,91,100,117,97,108,93,0
	.section	.debug_info		;off: 20
	.data.w	.Ldw_str_begin+166
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
	.data.b	137,3,0,0
	.data.b	2,0
	.data.b	3,1,0,0
	.data.b	1
	.data.b	0
	.data.b	0
	.data.b	4
	.data.b	10
	.data.b	0,1,1
	.data.b	1,1,0
	.data.b	0,0,1
	.data.b	0
	.data.b	46,92,83,116,97,114,116,117,112,47,101,120,99,101,112,116,105,111,110,46,99,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,112,105,108,101,114,92,99,111,109,112,105,108,101,114,116,121,112,101,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,112,105,108,101,114,92,99,111,109,112,105,108,101,114,95,103,104,115,46,104,0
	.data.b	0,0,0
	.data.b	46,92,46,46,92,46,46,92,83,68,75,92,112,108,97,116,102,111,114,109,92,99,111,109,109,111,110,92,99,111,109,109,111,110,95,104,97,108,46,104,0
	.data.b	0,0,0
	.data.b	46,92,67,111,109,109,111,110,70,105,108,101,92,105,110,99,108,117,100,101,92,80,108,97,116,102,111,114,109,95,84,121,112,101,115,46,104,0
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
	.data.b	75
	.data.b	1

	.section	.debug_abbrev		;off: 19
	.data.b	75
	.data.b	21
	.data.b	1
	.data.b	39,12
	.data.b	0,0

	.section	.debug_info		;off: 37
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

	.data.b	42
	.section	.debug_str		;off: 188
	.data.b	117,110,115,105,103,110,101,100,32,108,111,110,103,0
	.section	.debug_info		;off: 102
	.data.w	.Ldw_str_begin+188
	.data.b	7
	.data.b	4

	.section	.debug_abbrev		;off: 26
	.data.b	42
	.data.b	36
	.data.b	0
	.data.b	3,14
	.data.b	62,11
	.data.b	11,11
	.data.b	0,0

	.section	.debug_info		;off: 108
	.data.b	42
	.section	.debug_str		;off: 202
	.data.b	105,110,116,0
	.section	.debug_info		;off: 109
	.data.w	.Ldw_str_begin+202
	.data.b	5
	.data.b	4

	.data.b	64
	.data.b	0
	.data.b	128,31
	.data.w	.Ldw_begin+149

	.section	.debug_abbrev		;off: 37
	.data.b	64
	.data.b	1
	.data.b	1
	.data.b	9,11
	.data.b	11,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 123
	.data.b	56
	.data.w	.Ldw_begin+108
	.data.b	4
	.data.b	0
	.data.b	223,7

	.section	.debug_abbrev		;off: 48
	.data.b	56
	.data.b	33
	.data.b	0
	.data.b	73,16
	.data.b	11,15
	.data.b	34,13
	.data.b	47,13
	.data.b	0,0

	.section	.debug_info		;off: 132
	.data.b	0

	.data.b	64
	.data.b	0
	.data.b	48
	.data.w	.Ldw_begin+149

	.data.b	56
	.data.w	.Ldw_begin+108
	.data.b	4
	.data.b	0
	.data.b	11

	.data.b	0

	.data.b	45
	.section	.debug_str		;off: 206
	.data.b	117,105,110,116,51,50,0
	.section	.debug_info		;off: 150
	.data.w	.Ldw_str_begin+206
	.data.b	64
	.data.b	29
	.data.b	5
	.data.w	.Ldw_begin+101

	.section	.debug_abbrev		;off: 61
	.data.b	45
	.data.b	22
	.data.b	0
	.data.b	3,14
	.data.b	59,15
	.data.b	57,15
	.data.b	58,15
	.data.b	73,16
	.data.b	0,0

	.section	.debug_info		;off: 161
	.data.b	6
	.section	.debug_str		;off: 213
	.data.b	71,73,67,73,115,114,86,101,99,116,111,114,84,97,98,108,101,0
	.section	.debug_info		;off: 162
	.data.w	.Ldw_str_begin+213
	.data.b	31
	.data.b	8
	.data.b	1
	.data.w	.Ldw_begin+115
	.data.b	1
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	GICIsrVectorTable

	.section	.debug_abbrev		;off: 76
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

	.section	.debug_info		;off: 181
	.data.b	6
	.section	.debug_str		;off: 231
	.data.b	101,120,99,101,112,116,105,111,110,82,101,103,73,110,102,111,114,109,97,116,105,111,110,0
	.section	.debug_info		;off: 182
	.data.w	.Ldw_str_begin+231
	.data.b	55
	.data.b	8
	.data.b	1
	.data.w	.Ldw_begin+133
	.data.b	1
	.data.b	0
	.data.b	5
	.data.b	3
	.data.w	exceptionRegInformation

	.data.b	24
	.section	.debug_str		;off: 255
	.data.b	69,120,99,101,112,116,105,111,110,95,71,101,116,73,110,116,86,101,99,116,111,114,73,110,102,111,0
	.section	.debug_info		;off: 202
	.data.w	.Ldw_str_begin+255
	.data.b	65
	.data.b	26
	.data.b	1
	.data.w	Exception_GetIntVectorInfo
	.data.w	__ghs_eofn_Exception_GetIntVectorInfo
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

	.section	.debug_abbrev		;off: 97
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
	.data.w	Exception_GetIntVectorInfo
	.data.w	__ghs_eofn_Exception_GetIntVectorInfo-Exception_GetIntVectorInfo
	.data.b	1
	.data.w	.LDW21
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 269
	.data.b	0,5,2
	.data.w	Exception_GetIntVectorInfo
	.data.b	6
	.data.b	3
	.data.b	195,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_Exception_GetIntVectorInfo
	.data.b	3
	.data.b	22
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 232
	.data.b	34
	.data.w	.LDW11
	.data.w	.LDW21

	.section	.debug_abbrev		;off: 143
	.data.b	34
	.data.b	11
	.data.b	1
	.data.b	17,1
	.data.b	18,1
	.data.b	0,0

	.section	.debug_info		;off: 241
	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 282
	.data.b	69,76,50,95,71,101,116,69,120,99,101,112,116,105,111,110,73,110,102,111,114,109,97,116,105,111,110,0
	.section	.debug_info		;off: 244
	.data.w	.Ldw_str_begin+282
	.data.b	93
	.data.b	26
	.data.b	1
	.data.w	EL2_GetExceptionInformation
	.data.w	__ghs_eofn_EL2_GetExceptionInformation
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

	.section	.debug_frame		;off: 168
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	EL2_GetExceptionInformation
	.data.w	__ghs_eofn_EL2_GetExceptionInformation-EL2_GetExceptionInformation
	.data.b	1
	.data.w	.LDW51
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 298
	.data.b	0,5,2
	.data.w	EL2_GetExceptionInformation
	.data.b	6
	.data.b	3
	.data.b	223,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_EL2_GetExceptionInformation
	.data.b	3
	.data.b	30
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 274
	.data.b	34
	.data.w	.LDW41
	.data.w	.LDW51

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 310
	.data.b	69,76,49,95,71,101,116,69,120,99,101,112,116,105,111,110,73,110,102,111,114,109,97,116,105,111,110,0
	.section	.debug_info		;off: 286
	.data.w	.Ldw_str_begin+310
	.data.b	128,1
	.data.b	26
	.data.b	1
	.data.w	EL1_GetExceptionInformation
	.data.w	__ghs_eofn_EL1_GetExceptionInformation
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

	.section	.debug_frame		;off: 192
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	EL1_GetExceptionInformation
	.data.w	__ghs_eofn_EL1_GetExceptionInformation-EL1_GetExceptionInformation
	.data.b	1
	.data.w	.LDW81
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 327
	.data.b	0,5,2
	.data.w	EL1_GetExceptionInformation
	.data.b	6
	.data.b	3
	.data.b	130,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_EL1_GetExceptionInformation
	.data.b	3
	.data.b	29
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 317
	.data.b	34
	.data.w	.LDW71
	.data.w	.LDW81

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 338
	.data.b	69,120,99,101,112,116,105,111,110,95,85,110,100,101,102,105,110,101,100,67,97,108,108,98,97,99,107,0
	.section	.debug_info		;off: 329
	.data.w	.Ldw_str_begin+338
	.data.b	162,1
	.data.b	26
	.data.b	1
	.data.w	Exception_UndefinedCallback
	.data.w	__ghs_eofn_Exception_UndefinedCallback
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

	.section	.debug_frame		;off: 216
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Exception_UndefinedCallback
	.data.w	__ghs_eofn_Exception_UndefinedCallback-Exception_UndefinedCallback
	.data.b	1
	.data.w	.LDW12
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 356
	.data.b	0,5,2
	.data.w	Exception_UndefinedCallback
	.data.b	6
	.data.b	3
	.data.b	164,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_Exception_UndefinedCallback
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 360
	.data.b	34
	.data.w	.LDW02
	.data.w	.LDW12

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 366
	.data.b	69,120,99,101,112,116,105,111,110,95,80,114,101,102,101,116,99,104,65,98,111,114,116,67,97,108,108,98,97,99,107,0
	.section	.debug_info		;off: 372
	.data.w	.Ldw_str_begin+366
	.data.b	171,1
	.data.b	26
	.data.b	1
	.data.w	Exception_PrefetchAbortCallback
	.data.w	__ghs_eofn_Exception_PrefetchAbortCallback
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

	.section	.debug_frame		;off: 240
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Exception_PrefetchAbortCallback
	.data.w	__ghs_eofn_Exception_PrefetchAbortCallback-Exception_PrefetchAbortCallback
	.data.b	1
	.data.w	.LDW42
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 385
	.data.b	0,5,2
	.data.w	Exception_PrefetchAbortCallback
	.data.b	6
	.data.b	3
	.data.b	173,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_Exception_PrefetchAbortCallback
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 403
	.data.b	34
	.data.w	.LDW32
	.data.w	.LDW42

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 398
	.data.b	69,120,99,101,112,116,105,111,110,95,68,97,116,97,65,98,111,114,116,67,97,108,108,98,97,99,107,0
	.section	.debug_info		;off: 415
	.data.w	.Ldw_str_begin+398
	.data.b	180,1
	.data.b	26
	.data.b	1
	.data.w	Exception_DataAbortCallback
	.data.w	__ghs_eofn_Exception_DataAbortCallback
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

	.section	.debug_frame		;off: 264
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	Exception_DataAbortCallback
	.data.w	__ghs_eofn_Exception_DataAbortCallback-Exception_DataAbortCallback
	.data.b	1
	.data.w	.LDW72
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 414
	.data.b	0,5,2
	.data.w	Exception_DataAbortCallback
	.data.b	6
	.data.b	3
	.data.b	182,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_Exception_DataAbortCallback
	.data.b	3
	.data.b	8
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 446
	.data.b	34
	.data.w	.LDW62
	.data.w	.LDW72

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 426
	.data.b	69,76,50,95,85,110,100,101,102,105,110,101,100,69,120,99,101,112,116,105,111,110,0
	.section	.debug_info		;off: 458
	.data.w	.Ldw_str_begin+426
	.data.b	193,1
	.data.b	26
	.data.b	1
	.data.w	EL2_UndefinedException
	.data.w	__ghs_eofn_EL2_UndefinedException
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

	.section	.debug_frame		;off: 288
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	EL2_UndefinedException
	.data.w	__ghs_eofn_EL2_UndefinedException-EL2_UndefinedException
	.data.b	1
	.data.w	.LDW03
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 443
	.data.b	0,5,2
	.data.w	EL2_UndefinedException
	.data.b	6
	.data.b	3
	.data.b	195,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_EL2_UndefinedException
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 489
	.data.b	34
	.data.w	.LDW92
	.data.w	.LDW03

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 449
	.data.b	69,76,50,95,72,86,67,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 501
	.data.w	.Ldw_str_begin+449
	.data.b	203,1
	.data.b	26
	.data.b	1
	.data.w	EL2_HVCHandler
	.data.w	__ghs_eofn_EL2_HVCHandler
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

	.section	.debug_frame		;off: 312
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	EL2_HVCHandler
	.data.w	__ghs_eofn_EL2_HVCHandler-EL2_HVCHandler
	.data.b	1
	.data.w	.LDW33
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 472
	.data.b	0,5,2
	.data.w	EL2_HVCHandler
	.data.b	6
	.data.b	3
	.data.b	205,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_EL2_HVCHandler
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 532
	.data.b	34
	.data.w	.LDW23
	.data.w	.LDW33

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 464
	.data.b	69,76,50,95,80,114,101,102,101,116,99,104,65,98,111,114,116,69,120,99,101,112,116,105,111,110,0
	.section	.debug_info		;off: 544
	.data.w	.Ldw_str_begin+464
	.data.b	213,1
	.data.b	26
	.data.b	1
	.data.w	EL2_PrefetchAbortException
	.data.w	__ghs_eofn_EL2_PrefetchAbortException
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
	.data.w	EL2_PrefetchAbortException
	.data.w	__ghs_eofn_EL2_PrefetchAbortException-EL2_PrefetchAbortException
	.data.b	1
	.data.w	.LDW63
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 501
	.data.b	0,5,2
	.data.w	EL2_PrefetchAbortException
	.data.b	6
	.data.b	3
	.data.b	215,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_EL2_PrefetchAbortException
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 575
	.data.b	34
	.data.w	.LDW53
	.data.w	.LDW63

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 491
	.data.b	69,76,50,95,68,97,116,97,65,98,111,114,116,69,120,99,101,112,116,105,111,110,0
	.section	.debug_info		;off: 587
	.data.w	.Ldw_str_begin+491
	.data.b	223,1
	.data.b	26
	.data.b	1
	.data.w	EL2_DataAbortException
	.data.w	__ghs_eofn_EL2_DataAbortException
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
	.data.w	EL2_DataAbortException
	.data.w	__ghs_eofn_EL2_DataAbortException-EL2_DataAbortException
	.data.b	1
	.data.w	.LDW93
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 530
	.data.b	0,5,2
	.data.w	EL2_DataAbortException
	.data.b	6
	.data.b	3
	.data.b	225,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_EL2_DataAbortException
	.data.b	3
	.data.b	9
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 618
	.data.b	34
	.data.w	.LDW83
	.data.w	.LDW93

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 514
	.data.b	69,76,50,95,72,121,112,77,111,100,101,69,110,116,114,121,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 630
	.data.w	.Ldw_str_begin+514
	.data.b	237,1
	.data.b	26
	.data.b	1
	.data.w	EL2_HypModeEntryHandler
	.data.w	__ghs_eofn_EL2_HypModeEntryHandler
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

	.section	.debug_frame		;off: 384
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	EL2_HypModeEntryHandler
	.data.w	__ghs_eofn_EL2_HypModeEntryHandler-EL2_HypModeEntryHandler
	.data.b	1
	.data.w	.LDW24
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 559
	.data.b	0,5,2
	.data.w	EL2_HypModeEntryHandler
	.data.b	6
	.data.b	3
	.data.b	239,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_EL2_HypModeEntryHandler
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 661
	.data.b	34
	.data.w	.LDW14
	.data.w	.LDW24

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 538
	.data.b	69,76,50,95,73,82,81,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 673
	.data.w	.Ldw_str_begin+538
	.data.b	247,1
	.data.b	26
	.data.b	1
	.data.w	EL2_IRQHandler
	.data.w	__ghs_eofn_EL2_IRQHandler
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

	.section	.debug_frame		;off: 408
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	EL2_IRQHandler
	.data.w	__ghs_eofn_EL2_IRQHandler-EL2_IRQHandler
	.data.b	1
	.data.w	.LDW54
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 588
	.data.b	0,5,2
	.data.w	EL2_IRQHandler
	.data.b	6
	.data.b	3
	.data.b	249,1
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_EL2_IRQHandler
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 704
	.data.b	34
	.data.w	.LDW44
	.data.w	.LDW54

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 553
	.data.b	69,76,50,95,70,73,81,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 716
	.data.w	.Ldw_str_begin+553
	.data.b	129,2
	.data.b	26
	.data.b	1
	.data.w	EL2_FIQHandler
	.data.w	__ghs_eofn_EL2_FIQHandler
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

	.section	.debug_frame		;off: 432
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	EL2_FIQHandler
	.data.w	__ghs_eofn_EL2_FIQHandler-EL2_FIQHandler
	.data.b	1
	.data.w	.LDW84
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 617
	.data.b	0,5,2
	.data.w	EL2_FIQHandler
	.data.b	6
	.data.b	3
	.data.b	131,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_EL2_FIQHandler
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 747
	.data.b	34
	.data.w	.LDW74
	.data.w	.LDW84

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 568
	.data.b	69,76,49,95,82,101,115,101,114,118,101,100,0
	.section	.debug_info		;off: 759
	.data.w	.Ldw_str_begin+568
	.data.b	139,2
	.data.b	26
	.data.b	1
	.data.w	EL1_Reserved
	.data.w	__ghs_eofn_EL1_Reserved
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

	.section	.debug_frame		;off: 456
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	EL1_Reserved
	.data.w	__ghs_eofn_EL1_Reserved-EL1_Reserved
	.data.b	1
	.data.w	.LDW15
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 646
	.data.b	0,5,2
	.data.w	EL1_Reserved
	.data.b	6
	.data.b	3
	.data.b	141,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_EL1_Reserved
	.data.b	3
	.data.b	4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 790
	.data.b	34
	.data.w	.LDW05
	.data.w	.LDW15

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 581
	.data.b	114,101,97,100,69,120,99,101,112,116,105,111,110,82,101,103,73,110,102,111,0
	.section	.debug_info		;off: 802
	.data.w	.Ldw_str_begin+581
	.data.b	148,2
	.data.b	26
	.data.b	1
	.data.w	readExceptionRegInfo
	.data.w	__ghs_eofn_readExceptionRegInfo
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

	.section	.debug_frame		;off: 480
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	readExceptionRegInfo
	.data.w	__ghs_eofn_readExceptionRegInfo-readExceptionRegInfo
	.data.b	1
	.data.w	.LDW45
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 675
	.data.b	0,5,2
	.data.w	readExceptionRegInfo
	.data.b	6
	.data.b	3
	.data.b	150,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_readExceptionRegInfo
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 833
	.data.b	34
	.data.w	.LDW35
	.data.w	.LDW45

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 602
	.data.b	69,76,49,95,83,86,67,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 845
	.data.w	.Ldw_str_begin+602
	.data.b	158,2
	.data.b	26
	.data.b	1
	.data.w	EL1_SVCHandler
	.data.w	__ghs_eofn_EL1_SVCHandler
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

	.section	.debug_frame		;off: 504
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	EL1_SVCHandler
	.data.w	__ghs_eofn_EL1_SVCHandler-EL1_SVCHandler
	.data.b	1
	.data.w	.LDW75
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 704
	.data.b	0,5,2
	.data.w	EL1_SVCHandler
	.data.b	6
	.data.b	3
	.data.b	160,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_EL1_SVCHandler
	.data.b	3
	.data.b	11
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 876
	.data.b	34
	.data.w	.LDW65
	.data.w	.LDW75

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 617
	.data.b	69,76,49,95,85,110,100,101,102,105,110,101,100,69,120,99,101,112,116,105,111,110,0
	.section	.debug_info		;off: 888
	.data.w	.Ldw_str_begin+617
	.data.b	174,2
	.data.b	26
	.data.b	1
	.data.w	EL1_UndefinedException
	.data.w	__ghs_eofn_EL1_UndefinedException
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

	.section	.debug_frame		;off: 528
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	EL1_UndefinedException
	.data.w	__ghs_eofn_EL1_UndefinedException-EL1_UndefinedException
	.data.b	1
	.data.w	.LDW06
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 733
	.data.b	0,5,2
	.data.w	EL1_UndefinedException
	.data.b	6
	.data.b	3
	.data.b	176,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_EL1_UndefinedException
	.data.b	3
	.data.b	14
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 919
	.data.b	34
	.data.w	.LDW95
	.data.w	.LDW06

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 640
	.data.b	69,76,49,95,80,114,101,102,101,116,99,104,65,98,111,114,116,69,120,99,101,112,116,105,111,110,0
	.section	.debug_info		;off: 931
	.data.w	.Ldw_str_begin+640
	.data.b	193,2
	.data.b	26
	.data.b	1
	.data.w	EL1_PrefetchAbortException
	.data.w	__ghs_eofn_EL1_PrefetchAbortException
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

	.section	.debug_frame		;off: 552
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	EL1_PrefetchAbortException
	.data.w	__ghs_eofn_EL1_PrefetchAbortException-EL1_PrefetchAbortException
	.data.b	1
	.data.w	.LDW36
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 762
	.data.b	0,5,2
	.data.w	EL1_PrefetchAbortException
	.data.b	6
	.data.b	3
	.data.b	195,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_EL1_PrefetchAbortException
	.data.b	3
	.data.b	10
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 962
	.data.b	34
	.data.w	.LDW26
	.data.w	.LDW36

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 667
	.data.b	69,76,49,95,68,97,116,97,65,98,111,114,116,69,120,99,101,112,116,105,111,110,0
	.section	.debug_info		;off: 974
	.data.w	.Ldw_str_begin+667
	.data.b	208,2
	.data.b	26
	.data.b	1
	.data.w	EL1_DataAbortException
	.data.w	__ghs_eofn_EL1_DataAbortException
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

	.section	.debug_frame		;off: 576
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	EL1_DataAbortException
	.data.w	__ghs_eofn_EL1_DataAbortException-EL1_DataAbortException
	.data.b	1
	.data.w	.LDW66
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 791
	.data.b	0,5,2
	.data.w	EL1_DataAbortException
	.data.b	6
	.data.b	3
	.data.b	210,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_EL1_DataAbortException
	.data.b	3
	.data.b	15
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 1005
	.data.b	34
	.data.w	.LDW56
	.data.w	.LDW66

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 690
	.data.b	69,76,49,95,73,82,81,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 1017
	.data.w	.Ldw_str_begin+690
	.data.b	228,2
	.data.b	26
	.data.b	1
	.data.w	EL1_IRQHandler
	.data.w	__ghs_eofn_EL1_IRQHandler
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

	.section	.debug_frame		;off: 600
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	EL1_IRQHandler
	.data.w	__ghs_eofn_EL1_IRQHandler-EL1_IRQHandler
	.data.b	1
	.data.w	.LDW96
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 820
	.data.b	0,5,2
	.data.w	EL1_IRQHandler
	.data.b	6
	.data.b	3
	.data.b	230,2
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_EL1_IRQHandler
	.data.b	3
	.data.b	207,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 1048
	.data.b	34
	.data.w	.LDW86
	.data.w	.LDW96

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 705
	.data.b	69,76,49,95,70,73,81,72,97,110,100,108,101,114,0
	.section	.debug_info		;off: 1060
	.data.w	.Ldw_str_begin+705
	.data.b	184,3
	.data.b	26
	.data.b	1
	.data.w	EL1_FIQHandler
	.data.w	__ghs_eofn_EL1_FIQHandler
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

	.section	.debug_frame		;off: 624
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	EL1_FIQHandler
	.data.w	__ghs_eofn_EL1_FIQHandler-EL1_FIQHandler
	.data.b	1
	.data.w	.LDW27
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 850
	.data.b	0,5,2
	.data.w	EL1_FIQHandler
	.data.b	6
	.data.b	3
	.data.b	186,3
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_EL1_FIQHandler
	.data.b	3
	.data.b	206,0
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 1091
	.data.b	34
	.data.w	.LDW17
	.data.w	.LDW27

	.data.b	0

	.data.b	0

	.data.b	24
	.section	.debug_str		;off: 720
	.data.b	100,117,109,109,112,0
	.section	.debug_info		;off: 1103
	.data.w	.Ldw_str_begin+720
	.data.b	140,4
	.data.b	26
	.data.b	1
	.data.w	dummp
	.data.w	__ghs_eofn_dummp
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

	.section	.debug_frame		;off: 648
	.data.b	20,0,0,0
	.data.w	.Ldw_frame_begin
	.data.w	dummp
	.data.w	__ghs_eofn_dummp-dummp
	.data.b	1
	.data.w	.LDW57
	.data.b	0
	.data.b	0
	.data.b	0
	.section	.debug_line		;off: 880
	.data.b	0,5,2
	.data.w	dummp
	.data.b	6
	.data.b	3
	.data.b	142,4
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,5,2
	.data.w	__ghs_eofn_dummp
	.data.b	3
	.data.b	5
	.data.b	2
	.data.b	0
	.data.b	1
	.data.b	0,1,1
	.section	.debug_info		;off: 1134
	.data.b	34
	.data.w	.LDW47
	.data.w	.LDW57

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
	.data.b	24
	.data.b	2
	.data.b	3
	.data.b	13
	.data.b	3
	.data.b	1
	.data.b	38
	.data.b	65,83,77,95,86,79,76,65,84,73,76,69,32,95,95,97,115,109,32,118,111,108,97,116,105,108,101,0
	.data.b	1
	.data.b	59
	.data.b	65,84,84,82,95,78,65,75,69,68,32,95,95,97,116,116,114,105,98,117,116,101,95,95,40,40,110,97,107,101,100,41,41,0
	.data.b	1
	.data.b	64
	.data.b	87,69,65,75,70,85,78,67,32,95,95,97,116,116,114,105,98,117,116,101,95,95,40,40,119,101,97,107,41,41,0
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	25
	.data.b	4
	.data.b	4
	.data.b	3
	.data.b	26
	.data.b	5
	.data.b	4
	.data.b	1
	.data.b	28
	.data.b	83,68,75,95,83,84,65,82,84,95,83,69,67,95,73,78,73,84,95,86,65,82,95,73,82,81,95,86,69,67,84,79,82,32,0
	.data.b	3
	.data.b	29
	.data.b	6
	.data.b	1
	.data.b	51
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	112
	.data.b	73,78,83,73,68,69,95,83,68,75,95,83,84,65,82,84,95,83,69,67,95,73,78,73,84,95,86,65,82,95,73,82,81,95,86,69,67,84,79,82,32,0
	.data.b	1
	.data.b	115
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	32
	.data.b	83,68,75,95,83,84,79,80,95,83,69,67,95,73,78,73,84,95,86,65,82,95,73,82,81,95,86,69,67,84,79,82,32,0
	.data.b	3
	.data.b	34
	.data.b	6
	.data.b	1
	.data.b	51
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	37
	.data.b	83,68,75,95,83,84,65,82,84,95,83,69,67,95,73,78,73,84,95,86,65,82,95,69,88,67,69,80,84,73,79,78,95,82,69,71,95,73,78,70,79,32,0
	.data.b	3
	.data.b	39
	.data.b	6
	.data.b	1
	.data.b	51
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	170,1
	.data.b	73,78,83,73,68,69,95,83,68,75,95,83,84,65,82,84,95,83,69,67,95,73,78,73,84,95,86,65,82,95,69,88,67,69,80,84,73,79,78,95,82,69,71,95,73,78,70,79,32,0
	.data.b	1
	.data.b	173,1
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	56
	.data.b	83,68,75,95,83,84,79,80,95,83,69,67,95,73,78,73,84,95,86,65,82,95,69,88,67,69,80,84,73,79,78,95,82,69,71,95,73,78,70,79,32,0
	.data.b	3
	.data.b	58
	.data.b	6
	.data.b	1
	.data.b	51
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	61
	.data.b	83,68,75,95,83,84,65,82,84,95,83,69,67,95,69,88,67,69,80,84,73,79,78,95,72,65,78,68,76,69,82,32,0
	.data.b	3
	.data.b	63
	.data.b	6
	.data.b	1
	.data.b	51
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	1
	.data.b	228,1
	.data.b	73,78,83,73,68,69,95,83,68,75,95,83,84,65,82,84,95,83,69,67,95,69,88,67,69,80,84,73,79,78,95,72,65,78,68,76,69,82,32,0
	.data.b	1
	.data.b	231,1
	.data.b	77,69,77,77,65,80,95,77,65,84,67,72,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	1
	.data.b	150,4
	.data.b	83,68,75,95,83,84,79,80,95,83,69,67,95,69,88,67,69,80,84,73,79,78,95,72,65,78,68,76,69,82,32,0
	.data.b	3
	.data.b	152,4
	.data.b	6
	.data.b	1
	.data.b	51
	.data.b	77,69,77,77,65,80,95,69,82,82,79,82,32,0
	.data.b	4
	.data.b	4
	.data.b	0
	.section	.debug_abbrev		;off: 152
	.data.b	0
