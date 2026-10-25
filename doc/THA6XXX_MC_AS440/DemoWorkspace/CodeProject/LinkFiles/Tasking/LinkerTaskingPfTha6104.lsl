/**************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: LinkerAdsPf.scat
 * Author:    01766
 * Version:   v0.1
 * Date:     2024/11/29
 * Description: This file startup the system.
 * Others:
 * History:
 * Date          Author    Modified
 * 2024/11/29    01766     create
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
        PFLASH1_NORMAL          0x40600000  (407 TO 406) 0x40600000 - 0x40800000 (3MB TO 2MB)          AXI access PF1 address(Cacheable)
        DFLASH_NORMAL           0x44000000                0x44000000 - 0x44040000 (512KB TO 256K)        AXI access DF address(Cacheable)
        GMU0_DEVICE             0x82000000                0x82000000 - 0x8200A000 (256K TO 40k) AXI access global memory address(Non-Cacheable)
        GMU1_DEVICE             0x82020000                0x8200A000 - 0x82014000 (128K TO 40K)         AXI access global memory address(Non-Cacheable)
        PFLASH0_DEVICE          0x90400000                0x90400000 - 0x90600000 (3MB TO 2MB)          AXI access PF0 address(Non-Cacheable)
        PFLASH1_DEVICE          0x90600000 (907 TO 906)   0x90600000 - 0x90800000 (3MB TO 2MB)          AXI access PF1 address(Non-Cacheable)
        DFLASH_DEVICE           0x94000000                0x94000000 - 0x94040000 (512KB TO 256K)        AXI access DF address(Non-Cacheable)
        LMU2_DEVICE             0xC00D0000                0xC00D0000 - 0xC00D4000 (16KB)         AXI access LMU address(Non-Cacheable)

**********************************************************************************************************************/
#define STARTUP_ADDRESS                0x00000000
#define CPUXATCM_ADDRESS               0x00000000
#define CPUXATCM_SIZE                  32K
#define CPUXCTCM_ADDRESS               0x00200000
#define CPUXCTCM_SIZE                  128k

#define PFLASH0_NORMAL_ADDRESS         0x40400000
#define PFLASH1_NORMAL_ADDRESS         0x40600000

#define DFLASH_NORMAL_ADDRESS         0x44000000
#define DFLASH_NORMAL_SIZE            256k
#define LMU2_DEVICE_ADDRESS            0xC00D0000
#define LMU2_DEVICE_SIZE               16k


#define LMU2_NORMAL_ADDRESS            0x10058000
#define LMU2_NORMAL_SIZE               16K

#define GMU_DEVICE_ADDRESS             0x82000000
#define GMU_DEVICE_SIZE                48K

#define GMU_NORMAL_UNDEFINE_ADDRESS    0x1000C000
#define GMU_NORMAL_UNDEFINE_SIZE       32K
#define CPU0BTCM_ADDRESS               0x30100000
#define CPU0BTCM_SIZE                  0x39000
#define CPU0_STACK_ADDRESS             0x30139000
#define CORE0_USER_STACK_OFFSET        0x39000
#define CORE0_USER_STACK_SIZE          0x1000
#define CORE0_HYP_STACK_OFFSET         0x3A000
#define CORE0_HYP_STACK_SIZE           0x1000
#define CORE0_KERNEL_STACK_OFFSET      0x3B000
#define CORE0_KERNEL_STACK_SIZE        0x1000
#define CORE0_ABORT_STACK_OFFSET       0x3C000
#define CORE0_ABORT_STACK_SIZE         0x1000
#define CORE0_UNDEFINED_STACK_OFFSET   0x3D000
#define CORE0_UNDEFINED_STACK_SIZE     0x1000
#define CORE0_IRQ_STACK_OFFSET         0x3E000
#define CORE0_IRQ_STACK_SIZE           0x1000
#define CORE0_FIQ_STACK_OFFSET         0x3F000
#define CORE0_FIQ_STACK_SIZE           0x1000
#define CPU0_STACK_SIZE                0X7000


#define CPUXPFLASH0_ADDRESS            0x08000000
#define CPUXPFLASH0_SIZE               2M
#define CPUXPFLASH1_ADDRESS            0x08200000
#define CPUXPFLASH1_SIZE               2M

architecture ARM
{
    endianness
    {
        little;
        big;
    }

    space linear
    {
        id = 1;
        mau = 8;
        map (size = 4G, dest = bus:local_bus);
    }

    bus local_bus
    {
        mau = 8;
        width = 32;
    }
}

/* Entry points for stack size estimation */
#define __STACK_ENTRY_POINTS          "Start"

section_setup ::linear
{
    copytable
    (
        align = 4,
        copy_unit = 1,
        dest = linear
    );

    start_address
    (
        symbol = "Start"
    );
}

memory CPUXATCM
{
    mau = 8;
    type = ram;
    size = CPUXATCM_SIZE;
    map ( size = CPUXATCM_SIZE, dest_offset=STARTUP_ADDRESS, dest=bus:ARM:local_bus);
}

memory CPUXCTCM
{
    mau = 8;
    type = ram;
    size = CPUXCTCM_SIZE;
    map ( size = CPUXCTCM_SIZE, dest_offset=CPUXCTCM_ADDRESS, dest=bus:ARM:local_bus);
}

memory GMU_NORMAL_UNDEFINE
{
    mau = 8;
    type = ram;
    size = GMU_NORMAL_UNDEFINE_SIZE;
    map ( size = GMU_NORMAL_UNDEFINE_SIZE, dest_offset=GMU_NORMAL_UNDEFINE_ADDRESS, dest=bus:ARM:local_bus);
}

memory LMU2_NORMAL
{
    mau = 8;
    type = ram;
    size = LMU2_NORMAL_SIZE;
    map ( size = LMU2_NORMAL_SIZE, dest_offset=LMU2_NORMAL_ADDRESS, dest=bus:ARM:local_bus);
}

memory LMU2_DEVICE
{
    mau = 8;
    type = ram;
    size = LMU2_DEVICE_SIZE;
    map ( size = LMU2_DEVICE_SIZE, dest_offset=LMU2_DEVICE_ADDRESS, dest=bus:ARM:local_bus);
}


memory GMU_DEVICE
{
    mau = 8;
    type = ram;
    size = GMU_DEVICE_SIZE;
    map ( size = GMU_DEVICE_SIZE, dest_offset=GMU_DEVICE_ADDRESS, dest=bus:ARM:local_bus);
}

memory CPU0BTCM
{
    mau = 8;
    type = ram;
    size = CPU0BTCM_SIZE;
    map ( size = CPU0BTCM_SIZE, dest_offset=CPU0BTCM_ADDRESS, dest=bus:ARM:local_bus);
}

memory DFLASH_NORMAL
{
    mau = 8;
    type = rom;
    size = DFLASH_NORMAL_SIZE;
    map ( size = DFLASH_NORMAL_SIZE, dest_offset=DFLASH_NORMAL_ADDRESS, dest=bus:ARM:local_bus);
}

memory CPUXPFLASH0
{
    mau = 8;
    type = rom;
    size = CPUXPFLASH0_SIZE;
    map ( size = CPUXPFLASH0_SIZE, dest_offset=CPUXPFLASH0_ADDRESS, dest=bus:ARM:local_bus);
}

memory CPUXPFLASH1
{
    mau = 8;
    type = rom;
    size = CPUXPFLASH1_SIZE;
    map ( size = CPUXPFLASH1_SIZE, dest_offset=CPUXPFLASH1_ADDRESS, dest=bus:ARM:local_bus);
}

section_layout ARM::linear
{
    /* CPUXATCM sections */
    group CPUXATCM_SECTION
    {
        group INT_DEFAULT_VECTOR_TABLE_RUN (ordered, contiguous, align = 64, attributes=rwx, run_addr=mem:CPUXATCM, copy)
        {
            select ".text.init_default_vector";
        }
        group INT_VECTOR_TABLE_RUN (ordered, contiguous, align = 64, attributes=rwx, run_addr=mem:CPUXATCM)
        {
            select ".data.IRQ_init_vector";
        }
        group CODE_CLONE_RUN (ordered, contiguous, align = 64, attributes=rwx, run_addr=mem:CPUXATCM, copy)
        {
            select ".text.private_clone_code";
        }
    }

    /*CPUXCTCM sections*/
    group CPUXCTCM_SECTION
    {
        group DATA_CLONE_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:CPUXCTCM)
        {
            select ".data.exceptionRegInfo";
            select ".data.private_clone_data";
        }
        group BSS_CLONE_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:CPUXCTCM)
        {
            select ".bss.private_clone_bss";
        }
    }

    /*GMU_NORMAL_UNDEFINE sections*/
    group GMU_NORMAL_UNDEFINE_SECTION
    {
        group UNDEFINE_RAM_DATA_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:GMU_NORMAL_UNDEFINE)
        {
            select ".data.global_data";
            select ".data.mcal_data";
            select ".data.mcal_data_asil_d_bool";
            select ".data.mcal_data_asil_d_8";
            select ".data.mcal_data_asil_d_16";
            select ".data.mcal_data_asil_d_32";
            select ".data.mcal_data_asil_d_unspecified";
            select ".data";
            select ".data.sdk_data";
            select ".data.sdk_data_asil_d_bool";
            select ".data.sdk_data_asil_d_8";
            select ".data.sdk_data_asil_d_16";
            select ".data.sdk_data_asil_d_32";
            select ".data.sdk_data_asil_d_unspecified";            
        }
        group UNDEFINE_RAM_BSS_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:GMU_NORMAL_UNDEFINE)
        {
            select ".bss.global_bss";
            select ".bss.mcal_bss_asil_d_bool";
            select ".bss.mcal_bss_asil_d_8";
            select ".bss.mcal_bss_asil_d_16";
            select ".bss.mcal_bss_asil_d_32";
            select ".bss.mcal_bss_asil_d_unspecified";
            select ".bss.mcal_cleared";
            select ".bss.mcal_bss";         
            select ".bss";
            select ".bss.sdk_bss_asil_d_bool";
            select ".bss.sdk_bss_asil_d_8";
            select ".bss.sdk_bss_asil_d_16";
            select ".bss.sdk_bss_asil_d_32";
            select ".bss.sdk_bss_asil_d_unspecified";
            select ".bss.sdk_cleared";
            select ".bss.sdk_bss";            
        }
        group UNCLEAR_RAM_BSS_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:GMU_NORMAL_UNDEFINE)
        {
            select ".bss.unclear_bss";
            select ".bss.mcal_no_init_asil_d_bool";
            select ".bss.mcal_no_init_asil_d_8";
            select ".bss.mcal_no_init_asil_d_16";
            select ".bss.mcal_no_init_asil_d_32";
            select ".bss.mcal_no_init_asil_d_unspecified";
            select ".bss.sdk_no_init_asil_d_bool";
            select ".bss.sdk_no_init_asil_d_8";
            select ".bss.sdk_no_init_asil_d_16";
            select ".bss.sdk_no_init_asil_d_32";
            select ".bss.sdk_no_init_asil_d_unspecified";            
        }
    }

    /*LMU2_NORMAL sections*/
    group LMU2_NORMAL
    {
        group LMU2_CACHED_DATA_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:LMU2_NORMAL)
        {
            select ".data.mcal_data_asil_d_bool_lmu2";
            select ".data.mcal_data_asil_d_8_lmu2";
            select ".data.mcal_data_asil_d_16_lmu2";
            select ".data.mcal_data_asil_d_32_lmu2";
            select ".data.mcal_data_asil_d_unspecified_lmu2";
        }
        group LMU2_CACHED_BSS_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:LMU2_NORMAL)
        {
            select ".bss.mcal_bss_asil_d_bool_lmu2";
            select ".bss.mcal_bss_asil_d_8_lmu2";
            select ".bss.mcal_bss_asil_d_16_lmu2";
            select ".bss.mcal_bss_asil_d_32_lmu2";
            select ".bss.mcal_bss_asil_d_unspecified_lmu2";
        }
    }

    /*LMU2_DEVICE sections*/
    group LMU2_DEVICE
    {
        group LMU2_UNCACHED_DATA_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:LMU2_DEVICE)
        {
            select ".data.mcal_data_asil_d_bool_lmu2_uncached";
            select ".data.mcal_data_asil_d_8_lmu2_uncached";
            select ".data.mcal_data_asil_d_16_lmu2_uncached";
            select ".data.mcal_data_asil_d_32_lmu2_uncached";
            select ".data.mcal_data_asil_d_unspecified_lmu2_uncached";
            select ".data.lmu2_uncached_data";
            select ".data.sdk_data_asil_d_bool_lmu2_uncached";
            select ".data.sdk_data_asil_d_8_lmu2_uncached";
            select ".data.sdk_data_asil_d_16_lmu2_uncached";
            select ".data.sdk_data_asil_d_32_lmu2_uncached";
            select ".data.sdk_data_asil_d_unspecified_lmu2_uncached";            
        }
        group LMU2_UNCACHED_BSS_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:LMU2_DEVICE)
        {
            select ".bss.mcal_bss_asil_d_bool_lmu2_uncached";
            select ".bss.mcal_bss_asil_d_8_lmu2_uncached";
            select ".bss.mcal_bss_asil_d_16_lmu2_uncached";
            select ".bss.mcal_bss_asil_d_32_lmu2_uncached";
            select ".bss.mcal_bss_asil_d_unspecified_lmu2_uncached";
        }
    }


    /*CPU0BTCM sections*/
    group CPU0BTCM
    {
        group PRIVATE_CODE_CORE0_RUN (ordered, contiguous, align = 64, attributes=rwx, run_addr=mem:CPU0BTCM, copy)
        {
            select ".text.private_Core0_code";
            select ".text.mcal_ramcode_asil_d_core0";
            select ".text.mcal_text_asil_d_core0";
            select ".text.mcal_text_fast_asil_d_core0";
            select ".text.mcal_text_callout_asil_d_core0";
            select ".text.sdk_ramcode_asil_d_core0";
            select ".text.sdk_text_asil_d_core0";
            select ".text.sdk_text_fast_asil_d_core0";
            select ".text.sdk_text_callout_asil_d_core0";

        }
        group PRIVATE_DATA_CORE0_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:CPU0BTCM)
        {
            select ".data.private_Core0_data";
            select ".data.mcal_data_asil_d_bool_core0";
            select ".data.mcal_data_asil_d_8_core0";
            select ".data.mcal_data_asil_d_16_core0";
            select ".data.mcal_data_asil_d_32_core0";
            select ".data.mcal_data_asil_d_unspecified_core0";
            select ".data.sdk_data_asil_d_bool_core0";
            select ".data.sdk_data_asil_d_8_core0";
            select ".data.sdk_data_asil_d_16_core0";
            select ".data.sdk_data_asil_d_32_core0";
            select ".data.sdk_data_asil_d_unspecified_core0";              
        }
        group PRIVATE_BSS_CORE0_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:CPU0BTCM)
        {
            select ".bss.private_Core0_bss";
            select ".bss.private_bss_Core0";
            select ".bss.mcal_bss_asil_d_bool_core0";
            select ".bss.mcal_bss_asil_d_8_core0";
            select ".bss.mcal_bss_asil_d_16_core0";
            select ".bss.mcal_bss_asil_d_32_core0";
            select ".bss.mcal_bss_asil_d_unspecified_core0";
            select ".bss.sdk_bss_asil_d_bool_core0";
            select ".bss.sdk_bss_asil_d_8_core0";
            select ".bss.sdk_bss_asil_d_16_core0";
            select ".bss.sdk_bss_asil_d_32_core0";
            select ".bss.sdk_bss_asil_d_unspecified_core0";            
        }
        group PRIVATE_NO_INIT_CORE0_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:CPU0BTCM)
        {
            select ".bss.mcal_no_init_asil_d_bool_core0";
            select ".bss.mcal_no_init_asil_d_8_core0";
            select ".bss.mcal_no_init_asil_d_16_core0";
            select ".bss.mcal_no_init_asil_d_32_core0";
            select ".bss.mcal_no_init_asil_d_unspecified_core0";
            select ".bss.mcal_no_init_asil_d_bool_uncached_core0";
            select ".bss.mcal_no_init_asil_d_8_uncached_core0";
            select ".bss.mcal_no_init_asil_d_16_uncached_core0";
            select ".bss.mcal_no_init_asil_d_32_uncached_core0";
            select ".bss.mcal_no_init_asil_d_unspecified_uncached_core0"; 
        }
    }

    /*GMU_DEVICE sections*/
    group GMU_DEVICE
    {
        group RAM_CODE_RUN (ordered, contiguous, align = 64, attributes=rwx, run_addr=mem:GMU_DEVICE, copy)
        {
            select ".text.mcal_text_fast_asil_d";
            select ".text.mcal_ramcode_asil_d";
        }
        group GLOBAL_UNCACHED_DATA_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:GMU_DEVICE)
        {
            select ".data.uncached_data";
            select ".data.mcal_data_asil_d_bool_uncached";
            select ".data.mcal_data_asil_d_8_uncached";
            select ".data.mcal_data_asil_d_16_uncached";
            select ".data.mcal_data_asil_d_32_uncached";    
            select ".data.mcal_data_asil_d_unspecified_uncached";
            select ".data.sdk_data_asil_d_bool_uncached";
            select ".data.sdk_data_asil_d_8_uncached";
            select ".data.sdk_data_asil_d_16_uncached";
            select ".data.sdk_data_asil_d_32_uncached";    
            select ".data.sdk_data_asil_d_unspecified_uncached";            
        }
        group GLOBAL_UNCACHED_BSS_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:GMU_DEVICE)
        {
            select ".bss.uncached_bss";
            select ".bss.mcal_bss_asil_d_bool_uncached";
            select ".bss.mcal_bss_asil_d_8_uncached";
            select ".bss.mcal_bss_asil_d_16_uncached";
            select ".bss.mcal_bss_asil_d_32_uncached";
            select ".bss.mcal_bss_asil_d_unspecified_uncached";
            select ".bss.sdk_bss_asil_d_bool_uncached";
            select ".bss.sdk_bss_asil_d_8_uncached";
            select ".bss.sdk_bss_asil_d_16_uncached";
            select ".bss.sdk_bss_asil_d_32_uncached";
            select ".bss.sdk_bss_asil_d_unspecified_uncached";            
        }
        group GLOBAL_UNCACHED_NOINIT_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:GMU_DEVICE)
        {
            select ".bss.mcal_no_init_asil_d_bool_uncached";
            select ".bss.mcal_no_init_asil_d_8_uncached";
            select ".bss.mcal_no_init_asil_d_16_uncached";
            select ".bss.mcal_no_init_asil_d_32_uncached";
            select ".bss.mcal_no_init_asil_d_unspecified_uncached";
        }
    }

    group CPUXPFLASH0_SECTION
    {
        group INT_DEFAULT_VECTOR_TABLE_LOAD (ordered, contiguous, align = 64, attributes=rx, fill=0, load_addr=mem:CPUXPFLASH0, run_addr=CPUXPFLASH0_ADDRESS)
        {
            select ".text.init_default_vector";
        }
        group INT_VECTOR_TABLE_LOAD (ordered, contiguous, align = 64, attributes=r, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".data.IRQ_init_vector";
        }
        group CODE_CLONE_LOAD (ordered, contiguous, align = 64, attributes=rx, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".text.private_clone_code";
        }
        group DATA_CLONE_LOAD (ordered, contiguous, align = 64, attributes=r, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".data.exceptionRegInfo";
            select ".data.private_clone_data";
        }
        group UNDEFINE_RAM_DATA_LOAD (ordered, contiguous, align = 64, attributes=r, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".data.global_data";
            select ".data.mcal_data";
            select ".data.mcal_data_asil_d_bool";
            select ".data.mcal_data_asil_d_8";
            select ".data.mcal_data_asil_d_16";
            select ".data.mcal_data_asil_d_32";
            select ".data.mcal_data_asil_d_unspecified";
            select ".data";
            select ".data.sdk_data";
            select ".data.sdk_data_asil_d_bool";
            select ".data.sdk_data_asil_d_8";
            select ".data.sdk_data_asil_d_16";
            select ".data.sdk_data_asil_d_32";
            select ".data.sdk_data_asil_d_unspecified";            
        }

        group LMU2_CACHED_DATA_LOAD (ordered, contiguous, align = 64, attributes=r, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".data.mcal_data_asil_d_bool_lmu2";
            select ".data.mcal_data_asil_d_8_lmu2";
            select ".data.mcal_data_asil_d_16_lmu2";
            select ".data.mcal_data_asil_d_32_lmu2";
            select ".data.mcal_data_asil_d_unspecified_lmu2";
        }
        group LMU2_UNCACHED_DATA_LOAD (ordered, contiguous, align = 64, attributes=r, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".data.mcal_data_asil_d_bool_lmu2_uncached";
            select ".data.mcal_data_asil_d_8_lmu2_uncached";
            select ".data.mcal_data_asil_d_16_lmu2_uncached";
            select ".data.mcal_data_asil_d_32_lmu2_uncached";
            select ".data.mcal_data_asil_d_unspecified_lmu2_uncached";
            select ".data.lmu2_uncached_data";
            select ".data.sdk_data_asil_d_bool_lmu2_uncached";
            select ".data.sdk_data_asil_d_8_lmu2_uncached";
            select ".data.sdk_data_asil_d_16_lmu2_uncached";
            select ".data.sdk_data_asil_d_32_lmu2_uncached";
            select ".data.sdk_data_asil_d_unspecified_lmu2_uncached";            
        }
        
        group PRIVATE_CODE_CORE0_LOAD (ordered, contiguous, align = 64, attributes=rx, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".text.private_Core0_code";
            select ".text.mcal_ramcode_asil_d_core0";
            select ".text.mcal_text_asil_d_core0";
            select ".text.mcal_text_fast_asil_d_core0";
            select ".text.mcal_text_callout_asil_d_core0";
            select ".text.sdk_ramcode_asil_d_core0";
            select ".text.sdk_text_asil_d_core0";
            select ".text.sdk_text_fast_asil_d_core0";
            select ".text.sdk_text_callout_asil_d_core0";            
        }
        group PRIVATE_DATA_CORE0_LOAD (ordered, contiguous, align = 64, attributes=r, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".data.private_Core0_data";
            select ".data.mcal_data_asil_d_bool_core0";
            select ".data.mcal_data_asil_d_8_core0";
            select ".data.mcal_data_asil_d_16_core0";
            select ".data.mcal_data_asil_d_32_core0";
            select ".data.mcal_data_asil_d_unspecified_core0"; 
            select ".data.sdk_data_asil_d_bool_core0";
            select ".data.sdk_data_asil_d_8_core0";
            select ".data.sdk_data_asil_d_16_core0";
            select ".data.sdk_data_asil_d_32_core0";
            select ".data.sdk_data_asil_d_unspecified_core0";            
        }
        
        group RAM_CODE_LOAD (ordered, contiguous, align = 64, attributes=rx, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".text.mcal_text_fast_asil_d";
            select ".text.mcal_ramcode_asil_d";
        }
        group GLOBAL_UNCACHED_DATA_LOAD (ordered, contiguous, align = 64, attributes=r, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".data.uncached_data";
            select ".data.mcal_data_asil_d_bool_uncached";
            select ".data.mcal_data_asil_d_8_uncached";
            select ".data.mcal_data_asil_d_16_uncached";
            select ".data.mcal_data_asil_d_32_uncached";    
            select ".data.mcal_data_asil_d_unspecified_uncached";
            select ".data.sdk_data_asil_d_bool_uncached";
            select ".data.sdk_data_asil_d_8_uncached";
            select ".data.sdk_data_asil_d_16_uncached";
            select ".data.sdk_data_asil_d_32_uncached";    
            select ".data.sdk_data_asil_d_unspecified_uncached";            
        }

        /************* Only place in PFLASH *************/
        group EX_CODE (ordered, contiguous, align = 64, attributes=rx, fill=0, run_addr=mem:CPUXPFLASH0)
        {
            select ".text.exceptionHandler";
            select ".text.mcal_text_asil_d";
            select ".text.mcal_text_callout_asil_d";
            select ".text.user_code";
            select ".text";
            select ".text.sdk_text_asil_d"; 
            select ".text.sdk_text_callout_asil_d";             
        }
        group EX_CONST_DATA (ordered, contiguous, align = 64, attributes=r, fill=0, run_addr=mem:CPUXPFLASH0)
        {
            select ".rodata.mcal_text_asil_d";
            select ".rodata.mcal_const_cfg_asil_d_bool"; 
            select ".rodata.mcal_const_cfg_asil_d_8"; 
            select ".rodata.mcal_const_cfg_asil_d_16"; 
            select ".rodata.mcal_const_cfg_asil_d_32"; 
            select ".rodata.mcal_const_cfg_asil_d_unspecified";
            select ".rodata.mcal_const_asil_d_bool"; 
            select ".rodata.mcal_const_asil_d_8"; 
            select ".rodata.mcal_const_asil_d_16"; 
            select ".rodata.mcal_const_asil_d_32"; 
            select ".rodata.mcal_const_asil_d_unspecified";
            select ".rodata.mcal_const_cfg_asil_d_bool_core0"; 
            select ".rodata.mcal_const_cfg_asil_d_8_core0"; 
            select ".rodata.mcal_const_cfg_asil_d_16_core0"; 
            select ".rodata.mcal_const_cfg_asil_d_32_core0"; 
            select ".rodata.mcal_const_cfg_asil_d_unspecified_core0"; 
            select ".rodata.mcal_const_asil_d_bool_core0"; 
            select ".rodata.mcal_const_asil_d_8_core0"; 
            select ".rodata.mcal_const_asil_d_16_core0"; 
            select ".rodata.mcal_const_asil_d_32_core0"; 
            select ".rodata.mcal_const_asil_d_unspecified_core0";
            select ".rodata";
            select ".rodata.sdk_const_cfg_asil_d_bool"; 
            select ".rodata.sdk_const_cfg_asil_d_8"; 
            select ".rodata.sdk_const_cfg_asil_d_16"; 
            select ".rodata.sdk_const_cfg_asil_d_32"; 
            select ".rodata.sdk_const_cfg_asil_d_unspecified";
            select ".rodata.sdk_const_asil_d_bool"; 
            select ".rodata.sdk_const_asil_d_8"; 
            select ".rodata.sdk_const_asil_d_16"; 
            select ".rodata.sdk_const_asil_d_32"; 
            select ".rodata.sdk_const_asil_d_unspecified";
            select ".rodata.sdk_const_cfg_asil_d_bool_core0"; 
            select ".rodata.sdk_const_cfg_asil_d_8_core0"; 
            select ".rodata.sdk_const_cfg_asil_d_16_core0"; 
            select ".rodata.sdk_const_cfg_asil_d_32_core0"; 
            select ".rodata.sdk_const_cfg_asil_d_unspecified_core0"; 
            select ".rodata.sdk_const_asil_d_bool_core0"; 
            select ".rodata.sdk_const_asil_d_8_core0"; 
            select ".rodata.sdk_const_asil_d_16_core0"; 
            select ".rodata.sdk_const_asil_d_32_core0"; 
            select ".rodata.sdk_const_asil_d_unspecified_core0";             
        }
        

    }

    /* DFLASH_NORMAL */
    group DFLASH_NORMAL
    {
        group DFLASH_DATA_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:DFLASH_NORMAL)
        {
            select ".data.dflash_data";
        }
    }	
}

section_setup ARM::linear
{
    /* Core0 */
    stack "CPU0_CORE0_USER_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU0_CORE0_HYP_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU0_CORE0_KERNEL_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU0_CORE0_ABORT_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU0_CORE0_UNDEFINED_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU0_CORE0_IRQ_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU0_CORE0_FIQ_STACK" (min_size = 1k, fixed, align = 8);

}

/* Stack section_layout block */
section_layout ARM::linear
{
    /*Fixed memory Allocations for core 0 stack memory*/
    group (ordered)
    {
        group CORE0_USER_STACK(align = 8, run_addr = mem:CPU0BTCM[CORE0_USER_STACK_OFFSET])
        {
            stack "CPU0_CORE0_USER_STACK" (size = CORE0_USER_STACK_SIZE);
        }
        "__CORE0_USER_STACK"= CPU0BTCM_ADDRESS + CORE0_USER_STACK_OFFSET;
        "__CORE0_USER_STACK_END"=CPU0BTCM_ADDRESS + CORE0_USER_STACK_OFFSET + CORE0_USER_STACK_SIZE;
        group CORE0_HYP_STACK(align = 8, run_addr = mem:CPU0BTCM[CORE0_HYP_STACK_OFFSET])
        {
            stack "CPU0_CORE0_HYP_STACK" (size = CORE0_HYP_STACK_SIZE);
        }
        "__CORE0_HYP_STACK"= CPU0BTCM_ADDRESS + CORE0_HYP_STACK_OFFSET;
        "__CORE0_HYP_STACK_END"=CPU0BTCM_ADDRESS + CORE0_HYP_STACK_OFFSET + CORE0_HYP_STACK_SIZE;
        group CORE0_KERNEL_STACK(align = 8, run_addr = mem:CPU0BTCM[CORE0_KERNEL_STACK_OFFSET])
        {
            stack "CPU0_CORE0_KERNEL_STACK" (size = CORE0_KERNEL_STACK_SIZE);
        }
        "__CORE0_KERNEL_STACK"= CPU0BTCM_ADDRESS + CORE0_KERNEL_STACK_OFFSET;
        "__CORE0_KERNEL_STACK_END"=CPU0BTCM_ADDRESS + CORE0_KERNEL_STACK_OFFSET + CORE0_KERNEL_STACK_SIZE;
        group CORE0_ABORT_STACK(align = 8, run_addr = mem:CPU0BTCM[CORE0_ABORT_STACK_OFFSET])
        {
            stack "CPU0_CORE0_ABORT_STACK" (size = CORE0_ABORT_STACK_SIZE);
        }
        "__CORE0_ABORT_STACK"= CPU0BTCM_ADDRESS + CORE0_ABORT_STACK_OFFSET;
        "__CORE0_ABORT_STACK_END"=CPU0BTCM_ADDRESS + CORE0_ABORT_STACK_OFFSET + CORE0_ABORT_STACK_SIZE;
        group CORE0_UNDEFINED_STACK(align = 8, run_addr = mem:CPU0BTCM[CORE0_UNDEFINED_STACK_OFFSET])
        {
            stack "CPU0_CORE0_UNDEFINED_STACK" (size = CORE0_UNDEFINED_STACK_SIZE);
        }
        "__CORE0_UNDEFINED_STACK"= CPU0BTCM_ADDRESS + CORE0_UNDEFINED_STACK_OFFSET;
        "__CORE0_UNDEFINED_STACK_END"=CPU0BTCM_ADDRESS + CORE0_UNDEFINED_STACK_OFFSET + CORE0_UNDEFINED_STACK_SIZE;
        group CORE0_IRQ_STACK(align = 8, run_addr = mem:CPU0BTCM[CORE0_IRQ_STACK_OFFSET])
        {
            stack "CPU0_CORE0_IRQ_STACK" (size = CORE0_IRQ_STACK_SIZE);
        }
        "__CORE0_IRQ_STACK"= CPU0BTCM_ADDRESS + CORE0_IRQ_STACK_OFFSET;
        "__CORE0_IRQ_STACK_END"=CPU0BTCM_ADDRESS + CORE0_IRQ_STACK_OFFSET + CORE0_IRQ_STACK_SIZE;
        group CORE0_FIQ_STACK(align = 8, run_addr = mem:CPU0BTCM[CORE0_FIQ_STACK_OFFSET])
        {
            stack "CPU0_CORE0_FIQ_STACK" (size = CORE0_FIQ_STACK_SIZE);
        }
        "__CORE0_FIQ_STACK"= CPU0BTCM_ADDRESS + CORE0_FIQ_STACK_OFFSET;
        "__CORE0_FIQ_STACK_END"=CPU0BTCM_ADDRESS + CORE0_FIQ_STACK_OFFSET + CORE0_FIQ_STACK_SIZE;
    }

    "__BSS_CLONE" = "_lc_gb_BSS_CLONE_RUN";
    "__BSS_CLONE_END" = "_lc_ge_BSS_CLONE_RUN";
    "__CODE_CLONE" = "_lc_gb_CODE_CLONE_RUN";
    "__CODE_CLONE_END" = "_lc_ge_CODE_CLONE_RUN";
    "__CODE_CLONE_LOAD_ADDRESS" = "_lc_gb_CODE_CLONE_LOAD";
    "__DATA_CLONE" = "_lc_gb_DATA_CLONE_RUN";
    "__DATA_CLONE_END" = "_lc_ge_DATA_CLONE_RUN";
    "__DATA_CLONE_LOAD_ADDRESS" = "_lc_gb_DATA_CLONE_LOAD";

    "__GLOBAL_UNCACHED_BSS" = "_lc_gb_GLOBAL_UNCACHED_BSS_RUN";
    "__GLOBAL_UNCACHED_BSS_END" = "_lc_ge_GLOBAL_UNCACHED_BSS_RUN";

    "__GLOBAL_UNCACHED_DATA" = "_lc_gb_GLOBAL_UNCACHED_DATA_RUN";
    "__GLOBAL_UNCACHED_DATA_END" = "_lc_ge_GLOBAL_UNCACHED_DATA_RUN";
    "__GLOBAL_UNCACHED_DATA_LOAD_ADDRESS" = "_lc_gb_GLOBAL_UNCACHED_DATA_LOAD";

    "__INT_VECTOR_TABLE" = "_lc_gb_INT_DEFAULT_VECTOR_TABLE_RUN";
    "__INT_VECTOR_TABLE_END" = "_lc_ge_INT_DEFAULT_VECTOR_TABLE_RUN";
    "__INT_VECTOR_TABLE_LOAD_ADDRESS" = "_lc_gb_INT_DEFAULT_VECTOR_TABLE_LOAD";


    "__LMU2_CACHED_BSS" = "_lc_gb_LMU2_CACHED_BSS_RUN";
    "__LMU2_CACHED_BSS_END" = "_lc_ge_LMU2_CACHED_BSS_RUN";

    "__LMU2_CACHED_DATA" = "_lc_gb_LMU2_CACHED_DATA_RUN";
    "__LMU2_CACHED_DATA_END" = "_lc_ge_LMU2_CACHED_DATA_RUN";
    "__LMU2_CACHED_DATA_LOAD_ADDRESS" = "_lc_gb_LMU2_CACHED_DATA_LOAD";

    "__LMU2_UNCACHED_BSS" = "_lc_gb_LMU2_UNCACHED_BSS_RUN";
    "__LMU2_UNCACHED_BSS_END" = "_lc_ge_LMU2_UNCACHED_BSS_RUN";

    "__LMU2_UNCACHED_DATA" = "_lc_gb_LMU2_UNCACHED_DATA_RUN";
    "__LMU2_UNCACHED_DATA_END" = "_lc_ge_LMU2_UNCACHED_DATA_RUN";
    "__LMU2_UNCACHED_DATA_LOAD_ADDRESS" = "_lc_gb_LMU2_UNCACHED_DATA_LOAD";


    "__PRIVATE_BSS_CORE0" = "_lc_gb_PRIVATE_BSS_CORE0_RUN";
    "__PRIVATE_BSS_CORE0_END" = "_lc_ge_PRIVATE_BSS_CORE0_RUN";

    "__PRIVATE_CODE_CORE0" = "_lc_gb_PRIVATE_CODE_CORE0_RUN";
    "__PRIVATE_CODE_CORE0_END" = "_lc_ge_PRIVATE_CODE_CORE0_RUN";
    "__PRIVATE_CODE_CORE0_LOAD_ADDRESS" = "_lc_gb_PRIVATE_CODE_CORE0_LOAD";

    "__PRIVATE_DATA_CORE0" = "_lc_gb_PRIVATE_DATA_CORE0_RUN";
    "__PRIVATE_DATA_CORE0_END" = "_lc_ge_PRIVATE_DATA_CORE0_RUN";
    "__PRIVATE_DATA_CORE0_LOAD_ADDRESS" = "_lc_gb_PRIVATE_DATA_CORE0_LOAD";

    "__UNCLEAR_RAM_BSS" = "_lc_gb_UNCLEAR_RAM_BSS_RUN";
    "__UNCLEAR_RAM_BSS_END" = "_lc_ge_UNCLEAR_RAM_BSS_RUN";

    "__UNDEFINE_RAM_BSS" = "_lc_gb_UNDEFINE_RAM_BSS_RUN";
    "__UNDEFINE_RAM_BSS_END" = "_lc_ge_UNDEFINE_RAM_BSS_RUN";

    "__UNDEFINE_RAM_DATA" = "_lc_gb_UNDEFINE_RAM_DATA_RUN";
    "__UNDEFINE_RAM_DATA_END" = "_lc_ge_UNDEFINE_RAM_DATA_RUN";
    "__UNDEFINE_RAM_DATA_LOAD_ADDRESS" = "_lc_gb_UNDEFINE_RAM_DATA_LOAD";

}


