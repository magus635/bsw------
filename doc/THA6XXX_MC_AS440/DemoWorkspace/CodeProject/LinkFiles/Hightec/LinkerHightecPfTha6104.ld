/**************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: LinkerHightecPf.ld
 * Description: This file linker file for Hightec toolchain.
 * Others:
 * History:
 *  Date          Author    Modified      Version
 ************************************************************************************************/

/******* Memory ************** Start Address ****************************    End Address *******************************
        CPUXATCM                0x00000000                0x00000000 - 0x00008000 (64K to 32KB)  local access CPUXATCM address
        CPUXCTCM                0x00200000                0x00200000 - 0x00220000 (64K TO 128KB) local access CPUXCTCM address set  it as internel address for CPU0 and cpu1 in startup code.
        C1CPUXATCM              0x00000000                0x00000000 - 0x00010000 (64K)          local access Cluster1 CPUXATCM address 
        C1CPUXBTCM              0x00100000                0x00100000 - 0x00118000 (96K)          local access Cluster1 CPUXBTCM address invalid
        C1CPUXCTCM              0x00200000                0x00200000 - 0x00220000 (64K to 128k)          local access Cluster1 CPUXCTCM address set  it as internel address for CPU0 and cpu1 in startup code.
        CPUXPFLASH0             0x08000000                0x08000000 - 0x08200000 (3MB TO 2MB)          local access PF0 address
        CPUXPFLASH1             0x08200000  (83 TO 82)    0x08200000 - 0x08400000 (3MB TO 2MB)          local access PF1 address
        GMU0_NORMAL             0x10000000                0x10000000 - 0x1000A000 (256K TO 40K) AXI access global memory address(Cacheable)
        GMU1_NORMAL             0x10000000                0x1000A000 - 0x10014000 (128K TO 40K)         AXI access global memory address(Cacheable)
        LMU2_NORMAL             0x10058000                0x10058000 - 0x1005C000 (16k)          AXI Cacheable
        CPU0ATCM                0x30000000                0x30000000 - 0x30008000 (64K TO 32K)          AXI access CPU0ATCM address
        CPU0BTCM                0x30100000                0x30100000 - 0x30140000 (192K TO 256K) AXI access CPU0BTCM address   set  it as internel address for CPU0 in startup code.
        CPU0CTCM                0x30200000                0x30200000 - 0x30220000 (64K to 128k)          AXI access CPU0CTCM address
        PFLASH0_NORMAL          0x40400000                0x40400000 - 0x40600000 (3MB TO 2MB)          AXI access PF0 address(Cacheable)
        PFLASH1_NORMAL          0x40600000 (407 TO 406) 0x40600000 - 0x40800000 (3MB TO 2MB)          AXI access PF1 address(Cacheable)
        DFLASH_NORMAL           0x44000000                0x44000000 - 0x44040000 (512KB TO 256K)        AXI access DF address(Cacheable)
        GMU0_DEVICE             0x82000000                0x82000000 - 0x8200A000 (256K TO 40k) AXI access global memory address(Non-Cacheable)
        GMU1_DEVICE             0x82020000                0x8200A000 - 0x82014000 (128K TO 40K)         AXI access global memory address(Non-Cacheable)
        PFLASH0_DEVICE          0x90400000                0x90400000 - 0x90600000 (3MB TO 2MB)          AXI access PF0 address(Non-Cacheable)
        PFLASH1_DEVICE          0x90600000 (907 TO 906)   0x90600000 - 0x90800000 (3MB TO 2MB)          AXI access PF1 address(Non-Cacheable)
        DFLASH_DEVICE           0x94000000                0x94000000 - 0x94040000 (512KB TO 256K)        AXI access DF address(Non-Cacheable)
        LMU2_DEVICE             0xC00D0000                0xC00D0000 - 0xC00D4000 (16KB)         AXI access LMU address(Non-Cacheable)

**********************************************************************************************************************/

MEMORY {
    STARTUP_ADDRESS(rwx)                 : ORIGIN = 0x00000000, LENGTH = 32K
    CPUXCTCM_ADDRESS(rw)                : ORIGIN = 0x00200000, LENGTH = 128k
    CPUXPFLASH0(rx)                      : ORIGIN = 0x08000000, LENGTH = 2M
    CPUXPFLASH1(rx)                      : ORIGIN = 0x08200000, LENGTH = 2M
    GMU_NORMAL_UNDEFINE_ADDRESS(rwx)     : ORIGIN = 0x1000C000, LENGTH = 32K
    LMU2_NORMAL_ADDRESS(rw)             : ORIGIN = 0x10058000, LENGTH = 16K
    CPU0BTCM_ADDRESS(rwx)                : ORIGIN = 0x30100000, LENGTH = 0X39000
    CPU0_STACK_ADDRESS(rw)              : ORIGIN = 0x30139000, LENGTH = 0X7000    
    PFLASH0_NORMAL_ADDRESS(rx)          : ORIGIN = 0x40400000, LENGTH = 2M     
    PFLASH1_NORMAL_ADDRESS(rx)          : ORIGIN = 0x40600000, LENGTH = 2M      
    GMU_DEVICE_ADDRESS(rwx)              : ORIGIN = 0x82000000, LENGTH = 48K
    LMU2_DEVICE_ADDRESS(rw)            : ORIGIN = 0xC00D0000, LENGTH = 16K
    DFLASH_NORMAL(r)                : ORIGIN = 0x44000000, LENGTH = 512K       
}


SECTIONS
{
/*CPUXATCM*/
    INT_VECTOR_TABLE :
    {          
        . = ALIGN(64);
        *(first .init_default_vector)
        . = ALIGN(64);
        *exception.o(.IRQ_init_vector)
        . = ALIGN(64);
    } > STARTUP_ADDRESS AT > CPUXPFLASH0 =0xFFFFFFFF

    CODE_CLONE  :
    {          
        . = ALIGN(64);
        *(.private_clone_code)
        . = ALIGN(64);
    } > STARTUP_ADDRESS  AT > CPUXPFLASH0 =0xFFFFFFFF

/*CPUXCTCM*/
    DATA_CLONE :
    {          
        . = ALIGN(64);
        *exception.o(.exceptionRegInfo)
        *(.private_clone_data)
        . = ALIGN(64);
    } > CPUXCTCM_ADDRESS  AT > CPUXPFLASH0 =0xFFFFFFFF

    BSS_CLONE   :
    {          
        . = ALIGN(64);
        *(.private_clone_bss)
        . = ALIGN(64);
    } > CPUXCTCM_ADDRESS  =0xFFFFFFFF

/*GMU_NORMAL*/

    UNDEFINE_RAM_DATA   :
    {          
        . = ALIGN(64);
        *(.data)
        *(.data.*)
        *(.global_data)
        *(.mcal_data)
        *(.mcal_data_asil_d_bool)
        *(.mcal_data_asil_d_8)
        *(.mcal_data_asil_d_16)
        *(.mcal_data_asil_d_32)
        *(.mcal_data_asil_d_unspecified)            
        *(.sdk_data)
        *(.sdk_data_asil_d_bool)
        *(.sdk_data_asil_d_8)
        *(.sdk_data_asil_d_16)
        *(.sdk_data_asil_d_32)
        *(.sdk_data_asil_d_unspecified)                                         
        . = ALIGN(64);
    } > GMU_NORMAL_UNDEFINE_ADDRESS  AT > CPUXPFLASH0 =0xFFFFFFFF

    UNDEFINE_RAM_BSS   :
    {          
        . = ALIGN(64);
        *(.bss)        
        *(.bss.*)        
        *(.global_bss)
        *(.mcal_bss_asil_d_bool)
        *(.mcal_bss_asil_d_8)
        *(.mcal_bss_asil_d_16)
        *(.mcal_bss_asil_d_32)
        *(.mcal_bss_asil_d_unspecified)
        *(.mcal_cleared)
        *(.mcal_bss)        
        *(.sdk_bss_asil_d_bool)
        *(.sdk_bss_asil_d_8)
        *(.sdk_bss_asil_d_16)
        *(.sdk_bss_asil_d_32)
        *(.sdk_bss_asil_d_unspecified)
        *(.sdk_cleared)
        *(.sdk_bss)
        . = ALIGN(64);
    } > GMU_NORMAL_UNDEFINE_ADDRESS =0xFFFFFFFF 
    UNCLEAR_RAM_BSS  :
    {          
        . = ALIGN(64);
        *(.unclear_bss)
        *(.mcal_no_init_asil_d_bool)
        *(.mcal_no_init_asil_d_8)
        *(.mcal_no_init_asil_d_16)
        *(.mcal_no_init_asil_d_32)
        *(.mcal_no_init_asil_d_unspecified)
        *(.sdk_no_init_asil_d_bool)
        *(.sdk_no_init_asil_d_8)
        *(.sdk_no_init_asil_d_16)
        *(.sdk_no_init_asil_d_32)
        *(.sdk_no_init_asil_d_unspecified)
        . = ALIGN(64);
    } > GMU_NORMAL_UNDEFINE_ADDRESS =0xFFFFFFFF 


/*LMU*/

    LMU2_CACHED_DATA   :
    {          
        . = ALIGN(64);
        *(.mcal_data_asil_d_bool_lmu2)
        *(.mcal_data_asil_d_8_lmu2)
        *(.mcal_data_asil_d_16_lmu2)
        *(.mcal_data_asil_d_32_lmu2)
        *(.mcal_data_asil_d_unspecified_lmu2)         
        . = ALIGN(64);
    } > LMU2_NORMAL_ADDRESS  AT > CPUXPFLASH0 =0xFFFFFFFF

    LMU2_CACHED_BSS   :
    {          
        . = ALIGN(64);
        *(.mcal_bss_asil_d_bool_lmu2)
        *(.mcal_bss_asil_d_8_lmu2)
        *(.mcal_bss_asil_d_16_lmu2)
        *(.mcal_bss_asil_d_32_lmu2)
        *(.mcal_bss_asil_d_unspecified_lmu2)     
        . = ALIGN(64);
    } > LMU2_NORMAL_ADDRESS =0xFFFFFFFF 


/* CPU0BTCM */
    PRIVATE_CODE_CORE0   :
    {          
        . = ALIGN(64);
        *(.private_Core0_code)
        *(.mcal_ramcode_asil_d_core0)
        *(.mcal_text_asil_d_core0)
        *(.mcal_text_fast_asil_d_core0)
        *(.mcal_text_callout_asil_d_core0)
        *(.sdk_ramcode_asil_d_core0)
        *(.sdk_text_asil_d_core0)
        *(.sdk_text_fast_asil_d_core0)
        *(.sdk_text_callout_asil_d_core0)
        . = ALIGN(64);
    } > CPU0BTCM_ADDRESS  AT > CPUXPFLASH0 =0xFFFFFFFF

    PRIVATE_DATA_CORE0  :
    {          
        . = ALIGN(64);
        *(.private_Core0_data)
        *(.mcal_data_asil_d_bool_core0)
        *(.mcal_data_asil_d_8_core0)
        *(.mcal_data_asil_d_16_core0)
        *(.mcal_data_asil_d_32_core0)
        *(.mcal_data_asil_d_unspecified_core0)        
        *(.sdk_data_asil_d_bool_core0)
        *(.sdk_data_asil_d_8_core0)
        *(.sdk_data_asil_d_16_core0)
        *(.sdk_data_asil_d_32_core0)
        *(.sdk_data_asil_d_unspecified_core0)
        . = ALIGN(64);
    } > CPU0BTCM_ADDRESS  AT > CPUXPFLASH0 =0xFFFFFFFF

    PRIVATE_BSS_CORE0  :
    {          . = ALIGN(64);

        *(.private_Core0_bss)
        *(.private_bss_Core0)
        *(.mcal_bss_asil_d_bool_core0)
        *(.mcal_bss_asil_d_8_core0)
        *(.mcal_bss_asil_d_16_core0)
        *(.mcal_bss_asil_d_32_core0)
        *(.mcal_bss_asil_d_unspecified_core0)        
        *(.sdk_bss_asil_d_bool_core0)
        *(.sdk_bss_asil_d_8_core0)
        *(.sdk_bss_asil_d_16_core0)
        *(.sdk_bss_asil_d_32_core0)
        *(.sdk_bss_asil_d_unspecified_core0)
        . = ALIGN(64);
    } > CPU0BTCM_ADDRESS =0xFFFFFFFF

    PRIVATE_NO_INIT_CORE0 :
    {          . = ALIGN(64);

        *(.mcal_no_init_asil_d_bool_core0)
        *(.mcal_no_init_asil_d_8_core0)
        *(.mcal_no_init_asil_d_16_core0)
        *(.mcal_no_init_asil_d_32_core0)
        *(.mcal_no_init_asil_d_unspecified_core0)
        *(.mcal_no_init_asil_d_bool_uncached_core0)
        *(.mcal_no_init_asil_d_8_uncached_core0)
        *(.mcal_no_init_asil_d_16_uncached_core0)
        *(.mcal_no_init_asil_d_32_uncached_core0)
        *(.mcal_no_init_asil_d_unspecified_uncached_core0)    
        . = ALIGN(64);
    } > CPU0BTCM_ADDRESS 

    CORE0_USERSTACK (NOLOAD) :{.=ALIGN(8);. += 0x1000;.=ALIGN(8);}>CPU0_STACK_ADDRESS                          /* Set core0 userstack at 0x30209000~0x30208000 length is 4KB */
    CORE0_KERNEL_STACK (NOLOAD) :{.=ALIGN(8);. += 0x1000;.=ALIGN(8);}>CPU0_STACK_ADDRESS                       /* Set core0 kernelstack at 0x3020B000~0x3020A000 length is 4KB */
    CORE0_HYP_STACK (NOLOAD) :{.=ALIGN(8);. += 0x1000;.=ALIGN(8);}>CPU0_STACK_ADDRESS                          /* Set core0 Hypervisor stack at 0x3020A000~0x30209000 length is 4KB */
    CORE0_ABORT_STACK (NOLOAD) :{.=ALIGN(8);. += 0x1000;.=ALIGN(8);}>CPU0_STACK_ADDRESS                        /* Set core0 abortlstack at 0x3020C000~0x3020B000 length is 4KB */
    CORE0_UNDEFINED_STACK (NOLOAD) :{.=ALIGN(8);. += 0x1000;.=ALIGN(8);}>CPU0_STACK_ADDRESS                   /* Set core0 undefinedlstack at 0x3020D000~0x3020C000 length is 4KB */
    CORE0_IRQ_STACK (NOLOAD) :{.=ALIGN(8);. += 0x1000;.=ALIGN(8);}>CPU0_STACK_ADDRESS                          /* Set core0 irqlstack at 0x3020E000~0x3020D000 length is 4KB */
    CORE0_FIRQ_STACK (NOLOAD) :{.=ALIGN(8);. += 0x1000;.=ALIGN(8);}>CPU0_STACK_ADDRESS                         /* Set core0 firqlstack at 0x3020F000~0x3020E000 length is 4KB */


    __CORE0_USER_STACK_ADDRESS_START            = ADDR(CORE0_USERSTACK);
    __CORE0_USER_STACK_ADDRESS_END              = ADDR(CORE0_USERSTACK) + SIZEOF(CORE0_USERSTACK);
    __CORE0_HYP_STACK_ADDRESS_START             = ADDR(CORE0_HYP_STACK);
    __CORE0_HYP_STACK_ADDRESS_END               = ADDR(CORE0_HYP_STACK) + SIZEOF(CORE0_HYP_STACK);
    __CORE0_KERNEL_STACK_ADDRESS_START          = ADDR(CORE0_KERNEL_STACK);
    __CORE0_KERNEL_STACK_ADDRESS_END            = ADDR(CORE0_KERNEL_STACK) + SIZEOF(CORE0_KERNEL_STACK);
    __CORE0_ABORT_STACK_ADDRESS_START           = ADDR(CORE0_ABORT_STACK);
    __CORE0_ABORT_STACK_ADDRESS_END             = ADDR(CORE0_ABORT_STACK) + SIZEOF(CORE0_ABORT_STACK);
    __CORE0_UNDEFINED_STACK_ADDRESS_START       = ADDR(CORE0_UNDEFINED_STACK);
    __CORE0_UNDEFINED_STACK_ADDRESS_END         = ADDR(CORE0_UNDEFINED_STACK) + SIZEOF(CORE0_UNDEFINED_STACK);
    __CORE0_IRQ_STACK_ADDRESS_START             = ADDR(CORE0_IRQ_STACK);
    __CORE0_IRQ_STACK_ADDRESS_END               = ADDR(CORE0_IRQ_STACK) + SIZEOF(CORE0_IRQ_STACK);
    __CORE0_FIQ_STACK_ADDRESS_START             = ADDR(CORE0_FIRQ_STACK);
    __CORE0_FIQ_STACK_ADDRESS_END               = ADDR(CORE0_FIRQ_STACK) + SIZEOF(CORE0_FIRQ_STACK);



/*GMU_DEVICE*/
    RAM_CODE  :
    {          . = ALIGN(64);

      *(.mcal_text_fast_asil_d)
      *(.mcal_ramcode_asil_d)
        . = ALIGN(64);
    } > GMU_DEVICE_ADDRESS  AT > CPUXPFLASH0 =0xFFFFFFFF 


    GLOBAL_UNCACHED_DATA  :
    {          . = ALIGN(64);

        *(.uncached_data)
        *(.mcal_data_asil_d_bool_uncached)
        *(.mcal_data_asil_d_8_uncached)
        *(.mcal_data_asil_d_16_uncached)
        *(.mcal_data_asil_d_32_uncached)    
        *(.mcal_data_asil_d_unspecified_uncached)
        *(.sdk_data_asil_d_bool_uncached)
        *(.sdk_data_asil_d_8_uncached)
        *(.sdk_data_asil_d_16_uncached)
        *(.sdk_data_asil_d_32_uncached)    
        *(.sdk_data_asil_d_unspecified_uncached)
        . = ALIGN(64);
    } > GMU_DEVICE_ADDRESS  AT > CPUXPFLASH0 =0xFFFFFFFF 


    GLOBAL_UNCACHED_BSS  :
    {          . = ALIGN(64);

        *(.uncached_bss)
        *(.mcal_bss_asil_d_bool_uncached)
        *(.mcal_bss_asil_d_8_uncached)
        *(.mcal_bss_asil_d_16_uncached)
        *(.mcal_bss_asil_d_32_uncached)
        *(.mcal_bss_asil_d_unspecified_uncached)
        *(.sdk_bss_asil_d_bool_uncached)
        *(.sdk_bss_asil_d_8_uncached)
        *(.sdk_bss_asil_d_16_uncached)
        *(.sdk_bss_asil_d_32_uncached)
        *(.sdk_bss_asil_d_unspecified_uncached)
        . = ALIGN(64);
    } > GMU_DEVICE_ADDRESS =0xFFFFFFFF
    GLOBAL_UNCACHED_NOINIT :
    {          . = ALIGN(64);

        *(.mcal_no_init_asil_d_bool_uncached)
        *(.mcal_no_init_asil_d_8_uncached)
        *(.mcal_no_init_asil_d_16_uncached)
        *(.mcal_no_init_asil_d_32_uncached)
        *(.mcal_no_init_asil_d_unspecified_uncached)
        . = ALIGN(64);
    } > GMU_DEVICE_ADDRESS =0xFFFFFFFF

/*GMU DEVICE*/

    LMU2_UNCACHED_DATA   :
    {          . = ALIGN(64);

        *(.mcal_data_asil_d_bool_lmu2_uncached)
        *(.mcal_data_asil_d_8_lmu2_uncached)
        *(.mcal_data_asil_d_16_lmu2_uncached)
        *(.mcal_data_asil_d_32_lmu2_uncached)
        *(.mcal_data_asil_d_unspecified_lmu2_uncached)
        *(.lmu2_uncached_data)                                             ; To store the globle uncached variables that used in RAM store in Flash.
        *(.lmu2_uncached_data.*)                                           ; The address is 0xC00D0000~0xC00D3FFF,length is 16KB.
        *(.sdk_data_asil_d_bool_lmu2_uncached)
        *(.sdk_data_asil_d_8_lmu2_uncached)
        *(.sdk_data_asil_d_16_lmu2_uncached)
        *(.sdk_data_asil_d_32_lmu2_uncached)
        *(.sdk_data_asil_d_unspecified_lmu2_uncached)
        . = ALIGN(64);
    } > LMU2_DEVICE_ADDRESS  AT > CPUXPFLASH0 =0xFFFFFFFF 


    LMU2_UNCACHED_BSS  :
    {          . = ALIGN(64);

        *(.mcal_bss_asil_d_bool_lmu2_uncached)
        *(.mcal_bss_asil_d_8_lmu2_uncached)
        *(.mcal_bss_asil_d_16_lmu2_uncached)
        *(.mcal_bss_asil_d_32_lmu2_uncached)
        *(.mcal_bss_asil_d_unspecified_lmu2_uncached)
        . = ALIGN(64);
    } > LMU2_DEVICE_ADDRESS =0xFFFFFFFF

/*PFLASH0_NORMAL*/


    EX_CODE   :
    {          
        . = ALIGN(64);
        *(.user_code)
        *(.text )
        *(.text.* )
        *exception.o(.exceptionHandler)
        *(.mcal_text_asil_d) 
        *(.mcal_text_callout_asil_d)
        *(.sdk_text_asil_d) 
        *(.sdk_text_callout_asil_d)
        . = ALIGN(64);
    } >CPUXPFLASH0  =0xFFFFFFFF 

    EX_CONST_DATA  :
    {          . = ALIGN(64);

        *(.rodata)
        *(.rodata.*)
        *(.mcal_const_*) 
        *(.mcal_const_cfg_asil_d_bool) 
        *(.mcal_const_cfg_asil_d_8) 
        *(.mcal_const_cfg_asil_d_16) 
        *(.mcal_const_cfg_asil_d_32) 
        *(.mcal_const_cfg_asil_d_unspecified)
        *(.mcal_const_asil_d_bool) 
        *(.mcal_const_asil_d_8) 
        *(.mcal_const_asil_d_16) 
        *(.mcal_const_asil_d_32) 
        *(.mcal_const_asil_d_unspecified)
        *(.mcal_const_cfg_asil_d_bool_core0) 
        *(.mcal_const_cfg_asil_d_8_core0) 
        *(.mcal_const_cfg_asil_d_16_core0) 
        *(.mcal_const_cfg_asil_d_32_core0) 
        *(.mcal_const_cfg_asil_d_unspecified_core0) 
        *(.mcal_const_asil_d_bool_core0) 
        *(.mcal_const_asil_d_8_core0) 
        *(.mcal_const_asil_d_16_core0) 
        *(.mcal_const_asil_d_32_core0) 
        *(.mcal_const_asil_d_unspecified_core0)         
        *(.sdk_const_cfg_asil_d_bool) 
        *(.sdk_const_cfg_asil_d_8) 
        *(.sdk_const_cfg_asil_d_16) 
        *(.sdk_const_cfg_asil_d_32) 
        *(.sdk_const_cfg_asil_d_unspecified)
        *(.sdk_const_asil_d_bool) 
        *(.sdk_const_asil_d_8) 
        *(.sdk_const_asil_d_16) 
        *(.sdk_const_asil_d_32) 
        *(.sdk_const_asil_d_unspecified  )
        *(.sdk_const_cfg_asil_d_bool_core0) 
        *(.sdk_const_cfg_asil_d_8_core0) 
        *(.sdk_const_cfg_asil_d_16_core0) 
        *(.sdk_const_cfg_asil_d_32_core0) 
        *(.sdk_const_cfg_asil_d_unspecified_core0) 
        *(.sdk_const_asil_d_bool_core0) 
        *(.sdk_const_asil_d_8_core0) 
        *(.sdk_const_asil_d_16_core0) 
        *(.sdk_const_asil_d_32_core0) 
        *(.sdk_const_asil_d_unspecified_core0) 
        . = ALIGN(64);
    } > CPUXPFLASH0 =0xFFFFFFFF
    

    /DISCARD/ : { 
        *(.ARM.exidx) 
    } 
    DFLASH_DATA :
    {
        . = ALIGN(64);
        *(.dflash_data)
        . = ALIGN(64);        
    } > DFLASH_NORMAL =0xFFFFFFFF

    __GLOBAL_UNCACHED_BSS_ADDRESS_START             = ADDR(GLOBAL_UNCACHED_BSS);
    __GLOBAL_UNCACHED_BSS_ADDRESS_END               = ADDR(GLOBAL_UNCACHED_BSS) + SIZEOF(GLOBAL_UNCACHED_BSS);


    __LMU2_UNCACHED_BSS_ADDRESS_START             = ADDR(LMU2_UNCACHED_BSS);
    __LMU2_UNCACHED_BSS_ADDRESS_END               = ADDR(LMU2_UNCACHED_BSS) + SIZEOF(LMU2_UNCACHED_BSS);

    __INT_VECTOR_TABLE_ADDRESS_START                = ADDR(INT_VECTOR_TABLE);
    __INT_VECTOR_TABLE_ADDRESS_END                  = ADDR(INT_VECTOR_TABLE) + SIZEOF(INT_VECTOR_TABLE);
    __INT_VECTOR_TABLE_LOAD_ADDRESS_START           = LOADADDR(INT_VECTOR_TABLE);


    __CODE_CLONE_ADDRESS_START              = ADDR(CODE_CLONE);
    __CODE_CLONE_ADDRESS_END                = ADDR(CODE_CLONE) + SIZEOF(CODE_CLONE);
    __CODE_CLONE_LOAD_ADDRESS_START         = LOADADDR(CODE_CLONE);


    __DATA_CLONE_ADDRESS_START              = ADDR(DATA_CLONE);
    __DATA_CLONE_ADDRESS_END                = ADDR(DATA_CLONE) + SIZEOF(DATA_CLONE);
    __DATA_CLONE_LOAD_ADDRESS_START         = LOADADDR(DATA_CLONE);

    __BSS_CLONE_ADDRESS_START               = ADDR(BSS_CLONE);
    __BSS_CLONE_ADDRESS_END                 = ADDR(BSS_CLONE) + SIZEOF(BSS_CLONE);


    __PRIVATE_CODE_CORE0_ADDRESS_START              = ADDR(PRIVATE_CODE_CORE0);
    __PRIVATE_CODE_CORE0_ADDRESS_END                = ADDR(PRIVATE_CODE_CORE0) + SIZEOF(PRIVATE_CODE_CORE0);
    __PRIVATE_CODE_CORE0_LOAD_ADDRESS_START         = LOADADDR(PRIVATE_CODE_CORE0);


    __PRIVATE_DATA_CORE0_ADDRESS_START              = ADDR(PRIVATE_DATA_CORE0);
    __PRIVATE_DATA_CORE0_ADDRESS_END                = ADDR(PRIVATE_DATA_CORE0) + SIZEOF(PRIVATE_DATA_CORE0);
    __PRIVATE_DATA_CORE0_LOAD_ADDRESS_START         = LOADADDR(PRIVATE_DATA_CORE0);

    __PRIVATE_BSS_CORE0_ADDRESS_START               = ADDR(PRIVATE_BSS_CORE0);
    __PRIVATE_BSS_CORE0_ADDRESS_END                 = ADDR(PRIVATE_BSS_CORE0) + SIZEOF(PRIVATE_BSS_CORE0);

    __UNDEFINE_RAM_DATA_ADDRESS_START               = ADDR(UNDEFINE_RAM_DATA);
    __UNDEFINE_RAM_DATA_ADDRESS_END                 = ADDR(UNDEFINE_RAM_DATA) + SIZEOF(UNDEFINE_RAM_DATA);
    __UNDEFINE_RAM_DATA_LOAD_ADDRESS_START          = LOADADDR(UNDEFINE_RAM_DATA);

    __LMU2_CACHED_DATA_ADDRESS_START               = ADDR(LMU2_CACHED_DATA);
    __LMU2_CACHED_DATA_ADDRESS_END                 = ADDR(LMU2_CACHED_DATA) + SIZEOF(LMU2_CACHED_DATA);
    __LMU2_CACHED_DATA_LOAD_ADDRESS_START          = LOADADDR(LMU2_CACHED_DATA);


    __UNDEFINE_RAM_BSS_ADDRESS_START                = ADDR(UNDEFINE_RAM_BSS);
    __UNDEFINE_RAM_BSS_ADDRESS_END                  = ADDR(UNDEFINE_RAM_BSS) + SIZEOF(UNDEFINE_RAM_BSS);

    __LMU2_CACHED_BSS_ADDRESS_START                = ADDR(LMU2_CACHED_BSS);
    __LMU2_CACHED_BSS_ADDRESS_END                  = ADDR(LMU2_CACHED_BSS) + SIZEOF(LMU2_CACHED_BSS);



    __UNCLEAR_RAM_BSS_ADDRESS_START                = ADDR(UNCLEAR_RAM_BSS);
    __UNCLEAR_RAM_BSS_ADDRESS_END                  = ADDR(UNCLEAR_RAM_BSS) + SIZEOF(UNCLEAR_RAM_BSS);

    __GLOBAL_UNCACHED_DATA_ADDRESS_START            = ADDR(GLOBAL_UNCACHED_DATA);
    __GLOBAL_UNCACHED_DATA_ADDRESS_END              = ADDR(GLOBAL_UNCACHED_DATA) + SIZEOF(GLOBAL_UNCACHED_DATA);
    __GLOBAL_UNCACHED_DATA_LOAD_ADDRESS_START       = LOADADDR(GLOBAL_UNCACHED_DATA);

    __LMU2_UNCACHED_DATA_ADDRESS_START            = ADDR(LMU2_UNCACHED_DATA);
    __LMU2_UNCACHED_DATA_ADDRESS_END              = ADDR(LMU2_UNCACHED_DATA) + SIZEOF(LMU2_UNCACHED_DATA);
    __LMU2_UNCACHED_DATA_LOAD_ADDRESS_START       = LOADADDR(LMU2_UNCACHED_DATA);


}
