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
CPUXATCM                0x00000000                0x00000000 - 0x00010000 (64K)          local access CPUXATCM address
CPUXCTCM                0x00200000                0x00200000 - 0x00210000 (64K)          local access CPUXCTCM address set  it as internel address for CPU0 and cpu1 in startup code.
C1CPUXATCM              0x00000000                0x00000000 - 0x00010000 (64K)          local access Cluster1 CPUXATCM address
C1CPUXBTCM              0x00100000                0x00100000 - 0x00118000 (96K)          local access Cluster1 CPUXBTCM address invalid
C1CPUXCTCM              0x00200000                0x00200000 - 0x00210000 (64K)          local access Cluster1 CPUXCTCM address set  it as internel address for CPU0 and cpu1 in startup code.
CPUXPFLASH0             0x08000000                0x08000000 - 0x08300000 (3MB)          local access PF0 address
CPUXPFLASH1             0x08300000                0x08300000 - 0x08600000 (3MB)          local access PF1 address
CPUXPFLASH2             0x08600000                0x08600000 - 0x08900000 (3MB)          local access PF0 address
CPUXPFLASH3             0x08900000                0x08900000 - 0x08C00000 (3MB)          local access PF0 address
GMU0_NORMAL             0x10000000                0x10000000 - 0x10020000 (256K TO 128K) AXI access global memory address(Cacheable)
GMU1_NORMAL             0x10000000                0x10020000 - 0x10040000 (128K)         AXI access global memory address(Cacheable)
LMU1_NORMAL             0x10054000                0x10054000 - 0x10058000 (16k)          AXI Cacheable
LMU2_NORMAL             0x10058000                0x10058000 - 0x1005C000 (16k)          AXI Cacheable
LMU3_NORMAL             0x1005C000                0x1005C000 - 0x10060000 (16k)          AXI Cacheable
CPU0ATCM                0x30000000                0x30000000 - 0x30010000 (64K)          AXI access CPU0ATCM address
CPU0BTCM                0x30100000                0x30100000 - 0x3013C000 (192K TO 240K) AXI access CPU0BTCM address   set  it as internel address for CPU0 in startup code.
CPU0CTCM                0x30200000                0x30200000 - 0x30210000 (64K)          AXI access CPU0CTCM address
CPU1ATCM                0x30400000                0x30400000 - 0x30410000 (64K)          AXI access CPU1ATCM address
CPU1BTCM                0x30500000                0x30500000 - 0x3053C000 (192K TO 240K) AXI access CPU1BTCM address  set it as  internel address for CPU1 in startup code.
CPU1CTCM                0x30600000                0x30600000 - 0x30610000 (64K)          AXI access CPU1CTCM address
CPU2ATCM                0x31000000                0x31000000 - 0x31010000 (64K)          AXI access CPU2ATCM address
CPU2BTCM                0x31100000                0x31100000 - 0x31118000 (96K)          AXI access CPU2BTCM address  set it as  internel address for CPU1 in startup code.
CPU2CTCM                0x31200000                0x31200000 - 0x31210000 (64K)          AXI access CPU2CTCM address
CPU3ATCM                0x31400000                0x31400000 - 0x31410000 (64K)          AXI access CPU2ATCM address
CPU3BTCM                0x31500000                0x31500000 - 0x31518000 (96K)          AXI access CPU2BTCM address  set it as  internel address for CPU1 in startup code.
CPU3CTCM                0x31600000                0x31600000 - 0x31610000 (64K)          AXI access CPU2CTCM address
PFLASH0_NORMAL          0x40400000                0x40400000 - 0x40700000 (3MB)          AXI access PF0 address(Cacheable)
PFLASH1_NORMAL          0x40700000                0x40700000 - 0x40A00000 (3MB)          AXI access PF1 address(Cacheable)
PFLASH2_NORMAL          0x40A00000                0x40A00000 - 0x40D00000 (3MB)          AXI access PF2 address(Cacheable)
PFLASH3_NORMAL          0x40D00000                0x40D00000 - 0x41000000 (3MB)          AXI access PF3 address(Cacheable)
DFLASH_NORMAL           0x44000000                0x44000000 - 0x44080000 (512KB)        AXI access DF address(Cacheable)
GMU0_DEVICE             0x82000000                0x82000000 - 0x82020000 (256K TO 128K) AXI access global memory address(Non-Cacheable)
GMU1_DEVICE             0x82020000                0x82020000 - 0x82040000 (128K)         AXI access global memory address(Non-Cacheable)
PFLASH0_DEVICE          0x90400000                0x90400000 - 0x90700000 (3MB)          AXI access PF0 address(Non-Cacheable)
PFLASH1_DEVICE          0x90700000                0x90700000 - 0x90A00000 (3MB)          AXI access PF1 address(Non-Cacheable)
PFLASH2_DEVICE          0x90A00000                0x90A00000 - 0x90D00000 (3MB)          AXI access PF0 address(Non-Cacheable)
PFLASH3_DEVICE          0x90D00000                0x90D00000 - 0x91000000 (3MB)          AXI access PF1 address(Non-Cacheable)
DFLASH_DEVICE           0x94000000                0x94000000 - 0x94080000 (512KB)        AXI access DF address(Non-Cacheable)
LMU1_DEVICE             0xB0020000                0xB0020000 - 0xB0024000 (16KB)         AXI access LMU address(Non-Cacheable)
LMU2_DEVICE             0xC00D0000                0xC00D0000 - 0xC00D4000 (16KB)         AXI access LMU address(Non-Cacheable)
LMU3_DEVICE             0xD0040000                0xD0040000 - 0xD0044000 (16KB)         AXI access LMU address(Non-Cacheable)
**********************************************************************************************************************/
#define STARTUP_ADDRESS                0x00000000
#define CPUXATCM_ADDRESS               0x00000000
#define CPUXATCM_SIZE                  64k
#define CPUXCTCM_ADDRESS               0x00200000
#define CPUXCTCM_SIZE                  64k

#define PFLASH0_NORMAL_ADDRESS         0x40400000
#define PFLASH1_NORMAL_ADDRESS         0x40700000
#define DFLASH_MEMORY_ADDRESS          0x44000000
#define DFLASH_NORMAL_ADDRESS          0x44000000
#define DFLASH_NORMAL_SIZE             512k
#define LMU1_DEVICE_ADDRESS            0xB0020000
#define LMU1_DEVICE_SIZE               16k
#define LMU2_DEVICE_ADDRESS            0xC00D0000
#define LMU2_DEVICE_SIZE               16k
#define LMU3_DEVICE_ADDRESS            0xD0040000
#define LMU3_DEVICE_SIZE               16k
#define LMU1_NORMAL_ADDRESS            0x10054000
#define LMU1_NORMAL_SIZE               16K
#define LMU2_NORMAL_ADDRESS            0x10058000
#define LMU2_NORMAL_SIZE               16K
#define LMU3_NORMAL_ADDRESS            0x1005C000
#define LMU3_NORMAL_SIZE               16K
#define GMU_DEVICE_ADDRESS             0x82000000
#define GMU_DEVICE_SIZE                128K

#define GMU_NORMAL_UNDEFINE_ADDRESS    0x10020000
#define GMU_NORMAL_UNDEFINE_SIZE       128K
#define CPU0BTCM_ADDRESS               0x30100000
#define CPU0BTCM_SIZE                  0X35000
#define CPU0_STACK_ADDRESS             0x30135000
#define CORE0_USER_STACK_OFFSET        0x35000
#define CORE0_USER_STACK_SIZE          0x1000
#define CORE0_HYP_STACK_OFFSET         0x36000
#define CORE0_HYP_STACK_SIZE           0x1000
#define CORE0_KERNEL_STACK_OFFSET      0x37000
#define CORE0_KERNEL_STACK_SIZE        0x1000
#define CORE0_ABORT_STACK_OFFSET       0x38000
#define CORE0_ABORT_STACK_SIZE         0x1000
#define CORE0_UNDEFINED_STACK_OFFSET   0x39000
#define CORE0_UNDEFINED_STACK_SIZE     0x1000
#define CORE0_IRQ_STACK_OFFSET         0x3A000
#define CORE0_IRQ_STACK_SIZE           0x1000
#define CORE0_FIQ_STACK_OFFSET         0x3B000
#define CORE0_FIQ_STACK_SIZE           0x1000
#define CPU0_STACK_SIZE                0X7000

#define CPU1BTCM_ADDRESS               0x30500000
#define CPU1BTCM_SIZE                  0X35000
#define CPU1_STACK_ADDRESS             0x30535000
#define CORE1_USER_STACK_OFFSET        0x35000
#define CORE1_USER_STACK_SIZE          0x1000
#define CORE1_HYP_STACK_OFFSET         0x36000
#define CORE1_HYP_STACK_SIZE           0x1000
#define CORE1_KERNEL_STACK_OFFSET      0x37000
#define CORE1_KERNEL_STACK_SIZE        0x1000
#define CORE1_ABORT_STACK_OFFSET       0x38000
#define CORE1_ABORT_STACK_SIZE         0x1000
#define CORE1_UNDEFINED_STACK_OFFSET   0x39000
#define CORE1_UNDEFINED_STACK_SIZE     0x1000
#define CORE1_IRQ_STACK_OFFSET         0x3A000
#define CORE1_IRQ_STACK_SIZE           0x1000
#define CORE1_FIQ_STACK_OFFSET         0x3B000
#define CORE1_FIQ_STACK_SIZE           0x1000
#define CPU1_STACK_SIZE                0X7000

#define CPU2BTCM_ADDRESS               0x31100000
#define CPU2BTCM_SIZE                  0X11000
#define CPU2_STACK_ADDRESS             0x31111000
#define CORE2_USER_STACK_OFFSET        0X11000
#define CORE2_USER_STACK_SIZE          0x1000
#define CORE2_HYP_STACK_OFFSET         0x12000
#define CORE2_HYP_STACK_SIZE           0x1000
#define CORE2_KERNEL_STACK_OFFSET      0x13000
#define CORE2_KERNEL_STACK_SIZE        0x1000
#define CORE2_ABORT_STACK_OFFSET       0x14000
#define CORE2_ABORT_STACK_SIZE         0x1000
#define CORE2_UNDEFINED_STACK_OFFSET   0x15000
#define CORE2_UNDEFINED_STACK_SIZE     0x1000
#define CORE2_IRQ_STACK_OFFSET         0x16000
#define CORE2_IRQ_STACK_SIZE           0x1000
#define CORE2_FIQ_STACK_OFFSET         0x17000
#define CORE2_FIQ_STACK_SIZE           0x1000
#define CPU2_STACK_SIZE                0X7000

#define CPU3BTCM_ADDRESS               0x31500000
#define CPU3BTCM_SIZE                  0X11000
#define CPU3_STACK_ADDRESS             0x31511000
#define CORE3_USER_STACK_OFFSET        0x11000
#define CORE3_USER_STACK_SIZE          0x1000
#define CORE3_HYP_STACK_OFFSET         0x12000
#define CORE3_HYP_STACK_SIZE           0x1000
#define CORE3_KERNEL_STACK_OFFSET      0x13000
#define CORE3_KERNEL_STACK_SIZE        0x1000
#define CORE3_ABORT_STACK_OFFSET       0x14000
#define CORE3_ABORT_STACK_SIZE         0x1000
#define CORE3_UNDEFINED_STACK_OFFSET   0x15000
#define CORE3_UNDEFINED_STACK_SIZE     0x1000
#define CORE3_IRQ_STACK_OFFSET         0x16000
#define CORE3_IRQ_STACK_SIZE           0x1000
#define CORE3_FIQ_STACK_OFFSET         0x17000
#define CORE3_FIQ_STACK_SIZE           0x1000
#define CPU3_STACK_SIZE                0X7000

#define CPUXPFLASH0_ADDRESS            0x08000000
#define CPUXPFLASH0_SIZE               3M
#define CPUXPFLASH1_ADDRESS            0x08300000
#define CPUXPFLASH1_SIZE               3M
#define CPUXPFLASH2_ADDRESS            0x08600000
#define CPUXPFLASH2_SIZE               3M
#define CPUXPFLASH3_ADDRESS            0x08900000
#define CPUXPFLASH3_SIZE               3M

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

memory LMU1_NORMAL
{
    mau = 8;
    type = ram;
    size = LMU1_NORMAL_SIZE;
    map ( size = LMU1_NORMAL_SIZE, dest_offset=LMU1_NORMAL_ADDRESS, dest=bus:ARM:local_bus);
}
memory DFLASH_NORMAL
{
    mau = 8;
    type = rom;
    size = DFLASH_NORMAL_SIZE;
    map ( size = DFLASH_NORMAL_SIZE, dest_offset=DFLASH_NORMAL_ADDRESS, dest=bus:ARM:local_bus);
}

memory LMU2_NORMAL
{
    mau = 8;
    type = ram;
    size = LMU2_NORMAL_SIZE;
    map ( size = LMU2_NORMAL_SIZE, dest_offset=LMU2_NORMAL_ADDRESS, dest=bus:ARM:local_bus);
}

memory LMU3_NORMAL
{
    mau = 8;
    type = ram;
    size = LMU3_NORMAL_SIZE;
    map ( size = LMU3_NORMAL_SIZE, dest_offset=LMU3_NORMAL_ADDRESS, dest=bus:ARM:local_bus);
}

memory LMU1_DEVICE
{
    mau = 8;
    type = ram;
    size = LMU1_DEVICE_SIZE;
    map ( size = LMU1_DEVICE_SIZE, dest_offset=LMU1_DEVICE_ADDRESS, dest=bus:ARM:local_bus);
}

memory LMU2_DEVICE
{
    mau = 8;
    type = ram;
    size = LMU2_DEVICE_SIZE;
    map ( size = LMU2_DEVICE_SIZE, dest_offset=LMU2_DEVICE_ADDRESS, dest=bus:ARM:local_bus);
}

memory LMU3_DEVICE
{
    mau = 8;
    type = ram;
    size = LMU3_DEVICE_SIZE;
    map ( size = LMU3_DEVICE_SIZE, dest_offset=LMU3_DEVICE_ADDRESS, dest=bus:ARM:local_bus);
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

memory CPU1BTCM
{
    mau = 8;
    type = ram;
    size = CPU1BTCM_SIZE;
    map ( size = CPU1BTCM_SIZE, dest_offset=CPU1BTCM_ADDRESS, dest=bus:ARM:local_bus);
}

memory CPU2BTCM
{
    mau = 8;
    type = ram;
    size = CPU2BTCM_SIZE;
    map ( size = CPU2BTCM_SIZE, dest_offset=CPU2BTCM_ADDRESS, dest=bus:ARM:local_bus);
}

memory CPU3BTCM
{
    mau = 8;
    type = ram;
    size = CPU3BTCM_SIZE;
    map ( size = CPU3BTCM_SIZE, dest_offset=CPU3BTCM_ADDRESS, dest=bus:ARM:local_bus);
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

memory CPUXPFLASH2
{
    mau = 8;
    type = rom;
    size = CPUXPFLASH2_SIZE;
    map ( size = CPUXPFLASH2_SIZE, dest_offset=CPUXPFLASH2_ADDRESS, dest=bus:ARM:local_bus);
}

memory CPUXPFLASH3
{
    mau = 8;
    type = rom;
    size = CPUXPFLASH3_SIZE;
    map ( size = CPUXPFLASH3_SIZE, dest_offset=CPUXPFLASH3_ADDRESS, dest=bus:ARM:local_bus);
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
    /*LMU1_NORMAL sections*/
    group LMU1_NORMAL
    {
        group LMU1_CACHED_DATA_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:LMU1_NORMAL)
        {
            select ".data.mcal_data_asil_d_bool_lmu1";
            select ".data.mcal_data_asil_d_8_lmu1";
            select ".data.mcal_data_asil_d_16_lmu1";
            select ".data.mcal_data_asil_d_32_lmu1";
            select ".data.mcal_data_asil_d_unspecified_lmu1";
        }
        group LMU1_CACHED_BSS_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:LMU1_NORMAL)
        {
            select ".bss.mcal_bss_asil_d_bool_lmu1";
            select ".bss.mcal_bss_asil_d_8_lmu1";
            select ".bss.mcal_bss_asil_d_16_lmu1";
            select ".bss.mcal_bss_asil_d_32_lmu1";
            select ".bss.mcal_bss_asil_d_unspecified_lmu1";
        }
    }

    /*LMU1_DEVICE sections*/
    group LMU1_DEVICE
    {
        group LMU1_UNCACHED_DATA_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:LMU1_DEVICE)
        {
            select ".data.mcal_data_asil_d_bool_lmu1_uncached";
            select ".data.mcal_data_asil_d_8_lmu1_uncached";
            select ".data.mcal_data_asil_d_16_lmu1_uncached";
            select ".data.mcal_data_asil_d_32_lmu1_uncached";
            select ".data.mcal_data_asil_d_unspecified_lmu1_uncached";
            select ".data.lmu1_uncached_data";
            select ".data.sdk_data_asil_d_bool_lmu1_uncached";
            select ".data.sdk_data_asil_d_8_lmu1_uncached";
            select ".data.sdk_data_asil_d_16_lmu1_uncached";
            select ".data.sdk_data_asil_d_32_lmu1_uncached";
            select ".data.sdk_data_asil_d_unspecified_lmu1_uncached";            
        }
        group LMU1_UNCACHED_BSS_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:LMU1_DEVICE)
        {
            select ".bss.mcal_bss_asil_d_bool_lmu1_uncached";
            select ".bss.mcal_bss_asil_d_8_lmu1_uncached";
            select ".bss.mcal_bss_asil_d_16_lmu1_uncached";
            select ".bss.mcal_bss_asil_d_32_lmu1_uncached";
            select ".bss.mcal_bss_asil_d_unspecified_lmu1_uncached";
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

    /*LMU3_NORMAL sections*/
    group LMU3_NORMAL
    {
        group LMU3_CACHED_DATA_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:LMU3_NORMAL)
        {
            select ".data.mcal_data_asil_d_bool_lmu3";
            select ".data.mcal_data_asil_d_8_lmu3";
            select ".data.mcal_data_asil_d_16_lmu3";
            select ".data.mcal_data_asil_d_32_lmu3";
            select ".data.mcal_data_asil_d_unspecified_lmu3";
        }
        group LMU3_CACHED_BSS_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:LMU3_NORMAL)
        {
            select ".bss.mcal_bss_asil_d_bool_lmu3";
            select ".bss.mcal_bss_asil_d_8_lmu3";
            select ".bss.mcal_bss_asil_d_16_lmu3";
            select ".bss.mcal_bss_asil_d_32_lmu3";
            select ".bss.mcal_bss_asil_d_unspecified_lmu3";
        }
    }

    /*LMU3_DEVICE sections*/
    group LMU3_DEVICE
    {
        group LMU3_UNCACHED_DATA_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:LMU3_DEVICE)
        {
            select ".data.mcal_data_asil_d_bool_lmu3_uncached";
            select ".data.mcal_data_asil_d_8_lmu3_uncached";
            select ".data.mcal_data_asil_d_16_lmu3_uncached";
            select ".data.mcal_data_asil_d_32_lmu3_uncached";
            select ".data.mcal_data_asil_d_unspecified_lmu3_uncached";
            select ".data.lmu3_uncached_data";
            select ".data.sdk_data_asil_d_bool_lmu3_uncached";
            select ".data.sdk_data_asil_d_8_lmu3_uncached";
            select ".data.sdk_data_asil_d_16_lmu3_uncached";
            select ".data.sdk_data_asil_d_32_lmu3_uncached";
            select ".data.sdk_data_asil_d_unspecified_lmu3_uncached";
        }
        group LMU3_UNCACHED_BSS_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:LMU3_DEVICE)
        {
            select ".bss.mcal_bss_asil_d_bool_lmu3_uncached";
            select ".bss.mcal_bss_asil_d_8_lmu3_uncached";
            select ".bss.mcal_bss_asil_d_16_lmu3_uncached";
            select ".bss.mcal_bss_asil_d_32_lmu3_uncached";
            select ".bss.mcal_bss_asil_d_unspecified_lmu3_uncached";
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

    /*CPU1BTCM sections*/
    group CPU1BTCM
    {
        group PRIVATE_CODE_CORE1_RUN (ordered, contiguous, align = 64, attributes=rwx, run_addr=mem:CPU1BTCM, copy)
        {
            select ".text.mcal_ramcode_asil_d_core1";
            select ".text.mcal_text_fast_asil_d_core1";
            select ".text.private_Core1_code";
            select ".text.private_code_Core1";
            select ".text.sdk_ramcode_asil_d_core1";
            select ".text.sdk_text_fast_asil_d_core1";            
        }
        group PRIVATE_DATA_CORE1_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:CPU1BTCM)
        {
            select ".data.private_Core1_data";
            select ".data.mcal_data_asil_d_bool_core1";
            select ".data.mcal_data_asil_d_8_core1";
            select ".data.mcal_data_asil_d_16_core1";
            select ".data.mcal_data_asil_d_32_core1";
            select ".data.mcal_data_asil_d_unspecified_core1";
            select ".data.sdk_data_asil_d_bool_core1";
            select ".data.sdk_data_asil_d_8_core1";
            select ".data.sdk_data_asil_d_16_core1";
            select ".data.sdk_data_asil_d_32_core1";
            select ".data.sdk_data_asil_d_unspecified_core1";            
        }
        group PRIVATE_BSS_CORE1_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:CPU1BTCM)
        {
            select ".bss.private_Core1_bss";
            select ".bss.mcal_bss_asil_d_bool_core1";
            select ".bss.mcal_bss_asil_d_8_core1";
            select ".bss.mcal_bss_asil_d_16_core1";
            select ".bss.mcal_bss_asil_d_32_core1";
            select ".bss.mcal_bss_asil_d_unspecified_core1";
            select ".bss.sdk_bss_asil_d_bool_core1";
            select ".bss.sdk_bss_asil_d_8_core1";
            select ".bss.sdk_bss_asil_d_16_core1";
            select ".bss.sdk_bss_asil_d_32_core1";
            select ".bss.sdk_bss_asil_d_unspecified_core1";            
        }
        group PRIVATE_NO_INIT_CORE1_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:CPU1BTCM)
        {
            select ".bss.mcal_no_init_asil_d_bool_core1";
            select ".bss.mcal_no_init_asil_d_8_core1";
            select ".bss.mcal_no_init_asil_d_16_core1";
            select ".bss.mcal_no_init_asil_d_32_core1";
            select ".bss.mcal_no_init_asil_d_unspecified_core1";
            select ".bss.mcal_no_init_asil_d_bool_uncached_core1";
            select ".bss.mcal_no_init_asil_d_8_uncached_core1";
            select ".bss.mcal_no_init_asil_d_16_uncached_core1";
            select ".bss.mcal_no_init_asil_d_32_uncached_core1";
            select ".bss.mcal_no_init_asil_d_unspecified_uncached_core1";
        }
    }

    /*CPU2BTCM sections*/
    group CPU2BTCM
    {
        group PRIVATE_CODE_CORE2_RUN (ordered, contiguous, align = 64, attributes=rwx, run_addr=mem:CPU2BTCM, copy)
        {
            select ".text.mcal_ramcode_asil_d_core2";
            select ".text.mcal_text_fast_asil_d_core2";
            select ".text.private_Core2_code";
            select ".text.private_code_Core2";
            select ".text.sdk_ramcode_asil_d_core2";
            select ".text.sdk_text_fast_asil_d_core2";            
        }
        group PRIVATE_DATA_CORE2_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:CPU2BTCM)
        {
            select ".data.private_Core2_data";
            select ".data.mcal_data_asil_d_bool_core2";
            select ".data.mcal_data_asil_d_8_core2";
            select ".data.mcal_data_asil_d_16_core2";
            select ".data.mcal_data_asil_d_32_core2";
            select ".data.mcal_data_asil_d_unspecified_core2";
            select ".data.sdk_data_asil_d_bool_core2";
            select ".data.sdk_data_asil_d_8_core2";
            select ".data.sdk_data_asil_d_16_core2";
            select ".data.sdk_data_asil_d_32_core2";
            select ".data.sdk_data_asil_d_unspecified_core2";            
        }
        group PRIVATE_BSS_CORE2_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:CPU2BTCM)
        {
            select ".bss.private_Core2_bss";
            select ".bss.mcal_bss_asil_d_bool_core2";
            select ".bss.mcal_bss_asil_d_8_core2";
            select ".bss.mcal_bss_asil_d_16_core2";
            select ".bss.mcal_bss_asil_d_32_core2";
            select ".bss.mcal_bss_asil_d_unspecified_core2";
            select ".bss.sdk_bss_asil_d_bool_core2";
            select ".bss.sdk_bss_asil_d_8_core2";
            select ".bss.sdk_bss_asil_d_16_core2";
            select ".bss.sdk_bss_asil_d_32_core2";
            select ".bss.sdk_bss_asil_d_unspecified_core2";            
        }
        group PRIVATE_NO_INIT_CORE2_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:CPU2BTCM)
        {
            select ".bss.mcal_no_init_asil_d_bool_core2";
            select ".bss.mcal_no_init_asil_d_8_core2";
            select ".bss.mcal_no_init_asil_d_16_core2";
            select ".bss.mcal_no_init_asil_d_32_core2";
            select ".bss.mcal_no_init_asil_d_unspecified_core2";
            select ".bss.mcal_no_init_asil_d_bool_uncached_core2";
            select ".bss.mcal_no_init_asil_d_8_uncached_core2";
            select ".bss.mcal_no_init_asil_d_16_uncached_core2";
            select ".bss.mcal_no_init_asil_d_32_uncached_core2";
            select ".bss.mcal_no_init_asil_d_unspecified_uncached_core2";
        }
    }

    /*CPU3BTCM sections*/
    group CPU3BTCM
    {
        group PRIVATE_CODE_CORE3_RUN (ordered, contiguous, align = 64, attributes=rwx, run_addr=mem:CPU3BTCM, copy)
        {
            select ".text.mcal_ramcode_asil_d_core3";
            select ".text.mcal_text_fast_asil_d_core3";
            select ".text.private_Core3_code";
            select ".text.private_code_Core3";
            select ".text.sdk_ramcode_asil_d_core3";
            select ".text.sdk_text_fast_asil_d_core3";            
        }
        group PRIVATE_DATA_CORE3_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:CPU3BTCM)
        {
            select ".data.private_Core3_data";
            select ".data.mcal_data_asil_d_bool_core3";
            select ".data.mcal_data_asil_d_8_core3";
            select ".data.mcal_data_asil_d_16_core3";
            select ".data.mcal_data_asil_d_32_core3";
            select ".data.mcal_data_asil_d_unspecified_core3";
            select ".data.sdk_data_asil_d_bool_core3";
            select ".data.sdk_data_asil_d_8_core3";
            select ".data.sdk_data_asil_d_16_core3";
            select ".data.sdk_data_asil_d_32_core3";
            select ".data.sdk_data_asil_d_unspecified_core3";            
        }
        group PRIVATE_BSS_CORE3_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:CPU3BTCM)
        {
            select ".bss.private_Core3_bss";
            select ".bss.mcal_bss_asil_d_bool_core3";
            select ".bss.mcal_bss_asil_d_8_core3";
            select ".bss.mcal_bss_asil_d_16_core3";
            select ".bss.mcal_bss_asil_d_32_core3";
            select ".bss.mcal_bss_asil_d_unspecified_core3";
            select ".bss.sdk_bss_asil_d_bool_core3";
            select ".bss.sdk_bss_asil_d_8_core3";
            select ".bss.sdk_bss_asil_d_16_core3";
            select ".bss.sdk_bss_asil_d_32_core3";
            select ".bss.sdk_bss_asil_d_unspecified_core3";            
        }
        group PRIVATE_NO_INIT_CORE3_RUN (ordered, contiguous, align = 64, attributes=rw, run_addr=mem:CPU3BTCM)
        {
            select ".bss.mcal_no_init_asil_d_bool_core3";
            select ".bss.mcal_no_init_asil_d_8_core3";
            select ".bss.mcal_no_init_asil_d_16_core3";
            select ".bss.mcal_no_init_asil_d_32_core3";
            select ".bss.mcal_no_init_asil_d_unspecified_core3";
            select ".bss.mcal_no_init_asil_d_bool_uncached_core3";
            select ".bss.mcal_no_init_asil_d_8_uncached_core3";
            select ".bss.mcal_no_init_asil_d_16_uncached_core3";
            select ".bss.mcal_no_init_asil_d_32_uncached_core3";
            select ".bss.mcal_no_init_asil_d_unspecified_uncached_core3";
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
        group LMU1_CACHED_DATA_LOAD (ordered, contiguous, align = 64, attributes=r, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".data.mcal_data_asil_d_bool_lmu1";
            select ".data.mcal_data_asil_d_8_lmu1";
            select ".data.mcal_data_asil_d_16_lmu1";
            select ".data.mcal_data_asil_d_32_lmu1";
            select ".data.mcal_data_asil_d_unspecified_lmu1";
        }
        group LMU1_UNCACHED_DATA_LOAD (ordered, contiguous, align = 64, attributes=r, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".data.mcal_data_asil_d_bool_lmu1_uncached";
            select ".data.mcal_data_asil_d_8_lmu1_uncached";
            select ".data.mcal_data_asil_d_16_lmu1_uncached";
            select ".data.mcal_data_asil_d_32_lmu1_uncached";
            select ".data.mcal_data_asil_d_unspecified_lmu1_uncached";
            select ".data.lmu1_uncached_data";
            select ".data.sdk_data_asil_d_bool_lmu1_uncached";
            select ".data.sdk_data_asil_d_8_lmu1_uncached";
            select ".data.sdk_data_asil_d_16_lmu1_uncached";
            select ".data.sdk_data_asil_d_32_lmu1_uncached";
            select ".data.sdk_data_asil_d_unspecified_lmu1_uncached";            
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
        group LMU3_CACHED_DATA_LOAD (ordered, contiguous, align = 64, attributes=r, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".data.mcal_data_asil_d_bool_lmu3";
            select ".data.mcal_data_asil_d_8_lmu3";
            select ".data.mcal_data_asil_d_16_lmu3";
            select ".data.mcal_data_asil_d_32_lmu3";
            select ".data.mcal_data_asil_d_unspecified_lmu3";
        }
        group LMU3_UNCACHED_DATA_LOAD (ordered, contiguous, align = 64, attributes=r, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".data.mcal_data_asil_d_bool_lmu3_uncached";
            select ".data.mcal_data_asil_d_8_lmu3_uncached";
            select ".data.mcal_data_asil_d_16_lmu3_uncached";
            select ".data.mcal_data_asil_d_32_lmu3_uncached";
            select ".data.mcal_data_asil_d_unspecified_lmu3_uncached";
            select ".data.lmu3_uncached_data";
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
        group PRIVATE_CODE_CORE1_LOAD (ordered, contiguous, align = 64, attributes=rx, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".text.mcal_ramcode_asil_d_core1";
            select ".text.mcal_text_fast_asil_d_core1";
            select ".text.private_Core1_code";
            select ".text.private_code_Core1";
            select ".text.sdk_ramcode_asil_d_core1";
            select ".text.sdk_text_fast_asil_d_core1";            
        }
        group PRIVATE_DATA_CORE1_LOAD (ordered, contiguous, align = 64, attributes=r, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".data.private_Core1_data";
            select ".data.mcal_data_asil_d_bool_core1";
            select ".data.mcal_data_asil_d_8_core1";
            select ".data.mcal_data_asil_d_16_core1";
            select ".data.mcal_data_asil_d_32_core1";
            select ".data.mcal_data_asil_d_unspecified_core1";
            select ".data.sdk_data_asil_d_bool_core1";
            select ".data.sdk_data_asil_d_8_core1";
            select ".data.sdk_data_asil_d_16_core1";
            select ".data.sdk_data_asil_d_32_core1";
            select ".data.sdk_data_asil_d_unspecified_core1";            
        }
        group PRIVATE_CODE_CORE2_LOAD (ordered, contiguous, align = 64, attributes=rx, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".text.mcal_ramcode_asil_d_core2";
            select ".text.mcal_text_fast_asil_d_core2";
            select ".text.private_Core2_code";
            select ".text.private_code_Core2";
            select ".text.sdk_ramcode_asil_d_core2";
            select ".text.sdk_text_fast_asil_d_core2";            
        }
        group PRIVATE_DATA_CORE2_LOAD (ordered, contiguous, align = 64, attributes=r, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".data.private_Core2_data";
            select ".data.mcal_data_asil_d_bool_core2";
            select ".data.mcal_data_asil_d_8_core2";
            select ".data.mcal_data_asil_d_16_core2";
            select ".data.mcal_data_asil_d_32_core2";
            select ".data.mcal_data_asil_d_unspecified_core2";
            select ".data.sdk_data_asil_d_bool_core2";
            select ".data.sdk_data_asil_d_8_core2";
            select ".data.sdk_data_asil_d_16_core2";
            select ".data.sdk_data_asil_d_32_core2";
            select ".data.sdk_data_asil_d_unspecified_core2";            
        }
        group PRIVATE_CODE_CORE3_LOAD (ordered, contiguous, align = 64, attributes=rx, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".text.mcal_ramcode_asil_d_core3";
            select ".text.mcal_text_fast_asil_d_core3";
            select ".text.private_Core3_code";
            select ".text.private_code_Core3";
            select ".text.sdk_ramcode_asil_d_core3";
            select ".text.sdk_text_fast_asil_d_core3";            
        }
        group PRIVATE_DATA_CORE3_LOAD (ordered, contiguous, align = 64, attributes=r, fill=0, load_addr=mem:CPUXPFLASH0)
        {
            select ".data.private_Core3_data";
            select ".data.mcal_data_asil_d_bool_core3";
            select ".data.mcal_data_asil_d_8_core3";
            select ".data.mcal_data_asil_d_16_core3";
            select ".data.mcal_data_asil_d_32_core3";
            select ".data.mcal_data_asil_d_unspecified_core3";
            select ".data.sdk_data_asil_d_bool_core3";
            select ".data.sdk_data_asil_d_8_core3";
            select ".data.sdk_data_asil_d_16_core3";
            select ".data.sdk_data_asil_d_32_core3";
            select ".data.sdk_data_asil_d_unspecified_core3";            
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
            select ".text.sdk_text_asil_d_core1";
            select ".text.sdk_text_callout_asil_d_core1";
            select ".text.sdk_text_asil_d_core2";
            select ".text.sdk_text_callout_asil_d_core2";
            select ".text.sdk_text_asil_d_core3";
            select ".text.sdk_text_callout_asil_d_core3";            
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
            select ".rodata.sdk_const_asil_d_unspecified  ";
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
            select ".rodata.sdk_const_cfg_asil_d_bool_core1"; 
            select ".rodata.sdk_const_cfg_asil_d_8_core1"; 
            select ".rodata.sdk_const_cfg_asil_d_16_core1"; 
            select ".rodata.sdk_const_cfg_asil_d_32_core1"; 
            select ".rodata.sdk_const_cfg_asil_d_unspecified_core1"; 
            select ".rodata.sdk_const_asil_d_bool_core1"; 
            select ".rodata.sdk_const_asil_d_8_core1"; 
            select ".rodata.sdk_const_asil_d_16_core1"; 
            select ".rodata.sdk_const_asil_d_32_core1"; 
            select ".rodata.sdk_const_asil_d_unspecified_core1"; 
            select ".rodata.sdk_const_cfg_asil_d_bool_core2"; 
            select ".rodata.sdk_const_cfg_asil_d_8_core2"; 
            select ".rodata.sdk_const_cfg_asil_d_16_core2"; 
            select ".rodata.sdk_const_cfg_asil_d_32_core2"; 
            select ".rodata.sdk_const_cfg_asil_d_unspecified_core2"; 
            select ".rodata.sdk_const_asil_d_bool_core2"; 
            select ".rodata.sdk_const_asil_d_8_core2"; 
            select ".rodata.sdk_const_asil_d_16_core2"; 
            select ".rodata.sdk_const_asil_d_32_core2"; 
            select ".rodata.sdk_const_asil_d_unspecified_core2"; 
            select ".rodata.sdk_const_cfg_asil_d_bool_core3"; 
            select ".rodata.sdk_const_cfg_asil_d_8_core3"; 
            select ".rodata.sdk_const_cfg_asil_d_16_core3"; 
            select ".rodata.sdk_const_cfg_asil_d_32_core3"; 
            select ".rodata.sdk_const_cfg_asil_d_unspecified_core3"; 
            select ".rodata.sdk_const_asil_d_bool_core3"; 
            select ".rodata.sdk_const_asil_d_8_core3"; 
            select ".rodata.sdk_const_asil_d_16_core3"; 
            select ".rodata.sdk_const_asil_d_32_core3"; 
            select ".rodata.sdk_const_asil_d_unspecified_core3";             
        }
        group EX_CODE_CORE1 (ordered, contiguous, align = 64, attributes=rx, fill=0, run_addr=mem:CPUXPFLASH0)
        {
            select ".text.mcal_text_asil_d_core1";
            select ".text.mcal_text_callout_asil_d_core1";
        }
        group EX_CONST_DATA_CORE1 (ordered, contiguous, align = 64, attributes=r, fill=0, run_addr=mem:CPUXPFLASH0)
        {
            select ".rodata.mcal_const_cfg_asil_d_bool_core1";
            select ".rodata.mcal_const_cfg_asil_d_8_core1";
            select ".rodata.mcal_const_cfg_asil_d_16_core1";
            select ".rodata.mcal_const_cfg_asil_d_32_core1";
            select ".rodata.mcal_const_cfg_asil_d_unspecified_core1";
            select ".rodata.mcal_const_asil_d_bool_core1";
            select ".rodata.mcal_const_asil_d_8_core1";
            select ".rodata.mcal_const_asil_d_16_core1";
            select ".rodata.mcal_const_asil_d_32_core1";
            select ".rodata.mcal_const_asil_d_unspecified_core1";
        }
        group EX_CODE_CORE2 (ordered, contiguous, align = 64, attributes=rx, fill=0, run_addr=mem:CPUXPFLASH0)
        {
            select ".text.mcal_text_asil_d_core2";
            select ".text.mcal_text_callout_asil_d_core2";
        }
        group EX_CONST_DATA_CORE2 (ordered, contiguous, align = 64, attributes=r, fill=0, run_addr=mem:CPUXPFLASH0)
        {
            select ".rodata.mcal_const_cfg_asil_d_bool_core2";
            select ".rodata.mcal_const_cfg_asil_d_8_core2";
            select ".rodata.mcal_const_cfg_asil_d_16_core2";
            select ".rodata.mcal_const_cfg_asil_d_32_core2";
            select ".rodata.mcal_const_cfg_asil_d_unspecified_core2";
            select ".rodata.mcal_const_asil_d_bool_core2";
            select ".rodata.mcal_const_asil_d_8_core2";
            select ".rodata.mcal_const_asil_d_16_core2";
            select ".rodata.mcal_const_asil_d_32_core2";
            select ".rodata.mcal_const_asil_d_unspecified_core2";
        }
        group EX_CODE_CORE3 (ordered, contiguous, align = 64, attributes=rx, fill=0, run_addr=mem:CPUXPFLASH0)
        {
            select ".text.mcal_text_asil_d_core3";
            select ".text.mcal_text_callout_asil_d_core3";
        }
        group EX_CONST_DATA_CORE3 (ordered, contiguous, align = 64, attributes=r, fill=0, run_addr=mem:CPUXPFLASH0)
        {
            select ".rodata.mcal_const_cfg_asil_d_bool_core3";
            select ".rodata.mcal_const_cfg_asil_d_8_core3";
            select ".rodata.mcal_const_cfg_asil_d_16_core3";
            select ".rodata.mcal_const_cfg_asil_d_32_core3";
            select ".rodata.mcal_const_cfg_asil_d_unspecified_core3";
            select ".rodata.mcal_const_asil_d_bool_core3";
            select ".rodata.mcal_const_asil_d_8_core3";
            select ".rodata.mcal_const_asil_d_16_core3";
            select ".rodata.mcal_const_asil_d_32_core3";
            select ".rodata.mcal_const_asil_d_unspecified_core3";
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

    /* Core1 */
    stack "CPU1_CORE1_USER_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU1_CORE1_HYP_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU1_CORE1_KERNEL_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU1_CORE1_ABORT_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU1_CORE1_UNDEFINED_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU1_CORE1_IRQ_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU1_CORE1_FIQ_STACK" (min_size = 1k, fixed, align = 8);

    /* Core2 */
    stack "CPU2_CORE2_USER_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU2_CORE2_HYP_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU2_CORE2_KERNEL_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU2_CORE2_ABORT_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU2_CORE2_UNDEFINED_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU2_CORE2_IRQ_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU2_CORE2_FIQ_STACK" (min_size = 1k, fixed, align = 8);

    /* Core3 */
    stack "CPU3_CORE3_USER_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU3_CORE3_HYP_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU3_CORE3_KERNEL_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU3_CORE3_ABORT_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU3_CORE3_UNDEFINED_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU3_CORE3_IRQ_STACK" (min_size = 1k, fixed, align = 8);
    stack "CPU3_CORE3_FIQ_STACK" (min_size = 1k, fixed, align = 8);
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

    /*Fixed memory Allocations for core 1 stack memory*/
    group (ordered)
    {
        group CORE1_USER_STACK(align = 8, run_addr = mem:CPU1BTCM[CORE1_USER_STACK_OFFSET])
        {
            stack "CPU1_CORE1_USER_STACK" (size = CORE1_USER_STACK_SIZE);
        }
        "__CORE1_USER_STACK"= CPU1BTCM_ADDRESS + CORE1_USER_STACK_OFFSET;
        "__CORE1_USER_STACK_END"=CPU1BTCM_ADDRESS + CORE1_USER_STACK_OFFSET + CORE1_USER_STACK_SIZE;
        group CORE1_HYP_STACK(align = 8, run_addr = mem:CPU1BTCM[CORE1_HYP_STACK_OFFSET])
        {
            stack "CPU1_CORE1_HYP_STACK" (size = CORE1_HYP_STACK_SIZE);
        }
        "__CORE1_HYP_STACK"= CPU1BTCM_ADDRESS + CORE1_HYP_STACK_OFFSET;
        "__CORE1_HYP_STACK_END"=CPU1BTCM_ADDRESS + CORE1_HYP_STACK_OFFSET + CORE1_HYP_STACK_SIZE;
        group CORE1_KERNEL_STACK(align = 8, run_addr = mem:CPU1BTCM[CORE1_KERNEL_STACK_OFFSET])
        {
            stack "CPU1_CORE1_KERNEL_STACK" (size = CORE1_KERNEL_STACK_SIZE);
        }
        "__CORE1_KERNEL_STACK"= CPU1BTCM_ADDRESS + CORE1_KERNEL_STACK_OFFSET;
        "__CORE1_KERNEL_STACK_END"=CPU1BTCM_ADDRESS + CORE1_KERNEL_STACK_OFFSET + CORE1_KERNEL_STACK_SIZE;
        group CORE1_ABORT_STACK(align = 8, run_addr = mem:CPU1BTCM[CORE1_ABORT_STACK_OFFSET])
        {
            stack "CPU1_CORE1_ABORT_STACK" (size = CORE1_ABORT_STACK_SIZE);
        }
        "__CORE1_ABORT_STACK"= CPU1BTCM_ADDRESS + CORE1_ABORT_STACK_OFFSET;
        "__CORE1_ABORT_STACK_END"=CPU1BTCM_ADDRESS + CORE1_ABORT_STACK_OFFSET + CORE1_ABORT_STACK_SIZE;
        group CORE1_UNDEFINED_STACK(align = 8, run_addr = mem:CPU1BTCM[CORE1_UNDEFINED_STACK_OFFSET])
        {
            stack "CPU1_CORE1_UNDEFINED_STACK" (size = CORE1_UNDEFINED_STACK_SIZE);
        }
        "__CORE1_UNDEFINED_STACK"= CPU1BTCM_ADDRESS + CORE1_UNDEFINED_STACK_OFFSET;
        "__CORE1_UNDEFINED_STACK_END"=CPU1BTCM_ADDRESS + CORE1_UNDEFINED_STACK_OFFSET + CORE1_UNDEFINED_STACK_SIZE;
        group CORE1_IRQ_STACK(align = 8, run_addr = mem:CPU1BTCM[CORE1_IRQ_STACK_OFFSET])
        {
            stack "CPU1_CORE1_IRQ_STACK" (size = CORE1_IRQ_STACK_SIZE);
        }
        "__CORE1_IRQ_STACK"= CPU1BTCM_ADDRESS + CORE1_IRQ_STACK_OFFSET;
        "__CORE1_IRQ_STACK_END"=CPU1BTCM_ADDRESS + CORE1_IRQ_STACK_OFFSET + CORE1_IRQ_STACK_SIZE;
        group CORE1_FIQ_STACK(align = 8, run_addr = mem:CPU1BTCM[CORE1_FIQ_STACK_OFFSET])
        {
            stack "CPU1_CORE1_FIQ_STACK" (size = CORE1_FIQ_STACK_SIZE);
        }
        "__CORE1_FIQ_STACK"= CPU1BTCM_ADDRESS + CORE1_FIQ_STACK_OFFSET;
        "__CORE1_FIQ_STACK_END"=CPU1BTCM_ADDRESS + CORE1_FIQ_STACK_OFFSET + CORE1_FIQ_STACK_SIZE;
    }

    /*Fixed memory Allocations for core 2 stack memory*/
    group (ordered)
    {
        group CORE2_USER_STACK(align = 8, run_addr = mem:CPU2BTCM[CORE2_USER_STACK_OFFSET])
        {
            stack "CPU2_CORE2_USER_STACK" (size = CORE2_USER_STACK_SIZE);
        }
        "__CORE2_USER_STACK"= CPU2BTCM_ADDRESS + CORE2_USER_STACK_OFFSET;
        "__CORE2_USER_STACK_END"=CPU2BTCM_ADDRESS + CORE2_USER_STACK_OFFSET + CORE2_USER_STACK_SIZE;
        group CORE2_HYP_STACK(align = 8, run_addr = mem:CPU2BTCM[CORE2_HYP_STACK_OFFSET])
        {
            stack "CPU2_CORE2_HYP_STACK" (size = CORE2_HYP_STACK_SIZE);
        }
        "__CORE2_HYP_STACK"= CPU2BTCM_ADDRESS + CORE2_HYP_STACK_OFFSET;
        "__CORE2_HYP_STACK_END"=CPU2BTCM_ADDRESS + CORE2_HYP_STACK_OFFSET + CORE2_HYP_STACK_SIZE;
        group CORE2_KERNEL_STACK(align = 8, run_addr = mem:CPU2BTCM[CORE2_KERNEL_STACK_OFFSET])
        {
            stack "CPU2_CORE2_KERNEL_STACK" (size = CORE2_KERNEL_STACK_SIZE);
        }
        "__CORE2_KERNEL_STACK"= CPU2BTCM_ADDRESS + CORE2_KERNEL_STACK_OFFSET;
        "__CORE2_KERNEL_STACK_END"=CPU2BTCM_ADDRESS + CORE2_KERNEL_STACK_OFFSET + CORE2_KERNEL_STACK_SIZE;
        group CORE2_ABORT_STACK(align = 8, run_addr = mem:CPU2BTCM[CORE2_ABORT_STACK_OFFSET])
        {
            stack "CPU2_CORE2_ABORT_STACK" (size = CORE2_ABORT_STACK_SIZE);
        }
        "__CORE2_ABORT_STACK"= CPU2BTCM_ADDRESS + CORE2_ABORT_STACK_OFFSET;
        "__CORE2_ABORT_STACK_END"=CPU2BTCM_ADDRESS + CORE2_ABORT_STACK_OFFSET + CORE2_ABORT_STACK_SIZE;
        group CORE2_UNDEFINED_STACK(align = 8, run_addr = mem:CPU2BTCM[CORE2_UNDEFINED_STACK_OFFSET])
        {
            stack "CPU2_CORE2_UNDEFINED_STACK" (size = CORE2_UNDEFINED_STACK_SIZE);
        }
        "__CORE2_UNDEFINED_STACK"= CPU2BTCM_ADDRESS + CORE2_UNDEFINED_STACK_OFFSET;
        "__CORE2_UNDEFINED_STACK_END"=CPU2BTCM_ADDRESS + CORE2_UNDEFINED_STACK_OFFSET + CORE2_UNDEFINED_STACK_SIZE;
        group CORE2_IRQ_STACK(align = 8, run_addr = mem:CPU2BTCM[CORE2_IRQ_STACK_OFFSET])
        {
            stack "CPU2_CORE2_IRQ_STACK" (size = CORE2_IRQ_STACK_SIZE);
        }
        "__CORE2_IRQ_STACK"= CPU2BTCM_ADDRESS + CORE2_IRQ_STACK_OFFSET;
        "__CORE2_IRQ_STACK_END"=CPU2BTCM_ADDRESS + CORE2_IRQ_STACK_OFFSET + CORE2_IRQ_STACK_SIZE;
        group CORE2_FIQ_STACK(align = 8, run_addr = mem:CPU2BTCM[CORE2_FIQ_STACK_OFFSET])
        {
            stack "CPU2_CORE2_FIQ_STACK" (size = CORE2_FIQ_STACK_SIZE);
        }
        "__CORE2_FIQ_STACK"= CPU2BTCM_ADDRESS + CORE2_FIQ_STACK_OFFSET;
        "__CORE2_FIQ_STACK_END"=CPU2BTCM_ADDRESS + CORE2_FIQ_STACK_OFFSET + CORE2_FIQ_STACK_SIZE;
    }

    /*Fixed memory Allocations for core 3 stack memory*/
    group (ordered)
    {
        group CORE3_USER_STACK(align = 8, run_addr = mem:CPU3BTCM[CORE3_USER_STACK_OFFSET])
        {
            stack "CPU3_CORE3_USER_STACK" (size = CORE3_USER_STACK_SIZE);
        }
        "__CORE3_USER_STACK"= CPU3BTCM_ADDRESS + CORE3_USER_STACK_OFFSET;
        "__CORE3_USER_STACK_END"=CPU3BTCM_ADDRESS + CORE3_USER_STACK_OFFSET + CORE3_USER_STACK_SIZE;
        group CORE3_HYP_STACK(align = 8, run_addr = mem:CPU3BTCM[CORE3_HYP_STACK_OFFSET])
        {
            stack "CPU3_CORE3_HYP_STACK" (size = CORE3_HYP_STACK_SIZE);
        }
        "__CORE3_HYP_STACK"= CPU3BTCM_ADDRESS + CORE3_HYP_STACK_OFFSET;
        "__CORE3_HYP_STACK_END"=CPU3BTCM_ADDRESS + CORE3_HYP_STACK_OFFSET + CORE3_HYP_STACK_SIZE;
        group CORE3_KERNEL_STACK(align = 8, run_addr = mem:CPU3BTCM[CORE3_KERNEL_STACK_OFFSET])
        {
            stack "CPU3_CORE3_KERNEL_STACK" (size = CORE3_KERNEL_STACK_SIZE);
        }
        "__CORE3_KERNEL_STACK"= CPU3BTCM_ADDRESS + CORE3_KERNEL_STACK_OFFSET;
        "__CORE3_KERNEL_STACK_END"=CPU3BTCM_ADDRESS + CORE3_KERNEL_STACK_OFFSET + CORE3_KERNEL_STACK_SIZE;
        group CORE3_ABORT_STACK(align = 8, run_addr = mem:CPU3BTCM[CORE3_ABORT_STACK_OFFSET])
        {
            stack "CPU3_CORE3_ABORT_STACK" (size = CORE3_ABORT_STACK_SIZE);
        }
        "__CORE3_ABORT_STACK"= CPU3BTCM_ADDRESS + CORE3_ABORT_STACK_OFFSET;
        "__CORE3_ABORT_STACK_END"=CPU3BTCM_ADDRESS + CORE3_ABORT_STACK_OFFSET + CORE3_ABORT_STACK_SIZE;
        group CORE3_UNDEFINED_STACK(align = 8, run_addr = mem:CPU3BTCM[CORE3_UNDEFINED_STACK_OFFSET])
        {
            stack "CPU3_CORE3_UNDEFINED_STACK" (size = CORE3_UNDEFINED_STACK_SIZE);
        }
        "__CORE3_UNDEFINED_STACK"= CPU3BTCM_ADDRESS + CORE3_UNDEFINED_STACK_OFFSET;
        "__CORE3_UNDEFINED_STACK_END"=CPU3BTCM_ADDRESS + CORE3_UNDEFINED_STACK_OFFSET + CORE3_UNDEFINED_STACK_SIZE;
        group CORE3_IRQ_STACK(align = 8, run_addr = mem:CPU3BTCM[CORE3_IRQ_STACK_OFFSET])
        {
            stack "CPU3_CORE3_IRQ_STACK" (size = CORE3_IRQ_STACK_SIZE);
        }
        "__CORE3_IRQ_STACK"= CPU3BTCM_ADDRESS + CORE3_IRQ_STACK_OFFSET;
        "__CORE3_IRQ_STACK_END"=CPU3BTCM_ADDRESS + CORE3_IRQ_STACK_OFFSET + CORE3_IRQ_STACK_SIZE;
        group CORE3_FIQ_STACK(align = 8, run_addr = mem:CPU3BTCM[CORE3_FIQ_STACK_OFFSET])
        {
            stack "CPU3_CORE3_FIQ_STACK" (size = CORE3_FIQ_STACK_SIZE);
        }
        "__CORE3_FIQ_STACK"= CPU3BTCM_ADDRESS + CORE3_FIQ_STACK_OFFSET;
        "__CORE3_FIQ_STACK_END"=CPU3BTCM_ADDRESS + CORE3_FIQ_STACK_OFFSET + CORE3_FIQ_STACK_SIZE;
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

    "__LMU1_CACHED_BSS" = "_lc_gb_LMU1_CACHED_BSS_RUN";
    "__LMU1_CACHED_BSS_END" = "_lc_ge_LMU1_CACHED_BSS_RUN";

    "__LMU1_CACHED_DATA" = "_lc_gb_LMU1_CACHED_DATA_RUN";
    "__LMU1_CACHED_DATA_END" = "_lc_ge_LMU1_CACHED_DATA_RUN";
    "__LMU1_CACHED_DATA_LOAD_ADDRESS" = "_lc_gb_LMU1_CACHED_DATA_LOAD";

    "__LMU1_UNCACHED_BSS" = "_lc_gb_LMU1_UNCACHED_BSS_RUN";
    "__LMU1_UNCACHED_BSS_END" = "_lc_ge_LMU1_UNCACHED_BSS_RUN";

    "__LMU1_UNCACHED_DATA" = "_lc_gb_LMU1_UNCACHED_DATA_RUN";
    "__LMU1_UNCACHED_DATA_END" = "_lc_ge_LMU1_UNCACHED_DATA_RUN";
    "__LMU1_UNCACHED_DATA_LOAD_ADDRESS" = "_lc_gb_LMU1_UNCACHED_DATA_LOAD";

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

    "__LMU3_CACHED_BSS" = "_lc_gb_LMU3_CACHED_BSS_RUN";
    "__LMU3_CACHED_BSS_END" = "_lc_ge_LMU3_CACHED_BSS_RUN";

    "__LMU3_CACHED_DATA" = "_lc_gb_LMU3_CACHED_DATA_RUN";
    "__LMU3_CACHED_DATA_END" = "_lc_ge_LMU3_CACHED_DATA_RUN";
    "__LMU3_CACHED_DATA_LOAD_ADDRESS" = "_lc_gb_LMU3_CACHED_DATA_LOAD";

    "__LMU3_UNCACHED_BSS" = "_lc_gb_LMU3_UNCACHED_BSS_RUN";
    "__LMU3_UNCACHED_BSS_END" = "_lc_ge_LMU3_UNCACHED_BSS_RUN";

    "__LMU3_UNCACHED_DATA" = "_lc_gb_LMU3_UNCACHED_DATA_RUN";
    "__LMU3_UNCACHED_DATA_END" = "_lc_ge_LMU3_UNCACHED_DATA_RUN";
    "__LMU3_UNCACHED_DATA_LOAD_ADDRESS" = "_lc_gb_LMU3_UNCACHED_DATA_LOAD";

    "__PRIVATE_BSS_CORE0" = "_lc_gb_PRIVATE_BSS_CORE0_RUN";
    "__PRIVATE_BSS_CORE0_END" = "_lc_ge_PRIVATE_BSS_CORE0_RUN";

    "__PRIVATE_CODE_CORE0" = "_lc_gb_PRIVATE_CODE_CORE0_RUN";
    "__PRIVATE_CODE_CORE0_END" = "_lc_ge_PRIVATE_CODE_CORE0_RUN";
    "__PRIVATE_CODE_CORE0_LOAD_ADDRESS" = "_lc_gb_PRIVATE_CODE_CORE0_LOAD";

    "__PRIVATE_DATA_CORE0" = "_lc_gb_PRIVATE_DATA_CORE0_RUN";
    "__PRIVATE_DATA_CORE0_END" = "_lc_ge_PRIVATE_DATA_CORE0_RUN";
    "__PRIVATE_DATA_CORE0_LOAD_ADDRESS" = "_lc_gb_PRIVATE_DATA_CORE0_LOAD";

    "__PRIVATE_BSS_CORE1" = "_lc_gb_PRIVATE_BSS_CORE1_RUN";
    "__PRIVATE_BSS_CORE1_END" = "_lc_ge_PRIVATE_BSS_CORE1_RUN";

    "__PRIVATE_CODE_CORE1" = "_lc_gb_PRIVATE_CODE_CORE1_RUN";
    "__PRIVATE_CODE_CORE1_END" = "_lc_ge_PRIVATE_CODE_CORE1_RUN";
    "__PRIVATE_CODE_CORE1_LOAD_ADDRESS" = "_lc_gb_PRIVATE_CODE_CORE1_LOAD";

    "__PRIVATE_DATA_CORE1" = "_lc_gb_PRIVATE_DATA_CORE1_RUN";
    "__PRIVATE_DATA_CORE1_END" = "_lc_ge_PRIVATE_DATA_CORE1_RUN";
    "__PRIVATE_DATA_CORE1_LOAD_ADDRESS" = "_lc_gb_PRIVATE_DATA_CORE1_LOAD";

    "__PRIVATE_BSS_CORE2" = "_lc_gb_PRIVATE_BSS_CORE2_RUN";
    "__PRIVATE_BSS_CORE2_END" = "_lc_ge_PRIVATE_BSS_CORE2_RUN";

    "__PRIVATE_CODE_CORE2" = "_lc_gb_PRIVATE_CODE_CORE2_RUN";
    "__PRIVATE_CODE_CORE2_END" = "_lc_ge_PRIVATE_CODE_CORE2_RUN";
    "__PRIVATE_CODE_CORE2_LOAD_ADDRESS" = "_lc_gb_PRIVATE_CODE_CORE2_LOAD";

    "__PRIVATE_DATA_CORE2" = "_lc_gb_PRIVATE_DATA_CORE2_RUN";
    "__PRIVATE_DATA_CORE2_END" = "_lc_ge_PRIVATE_DATA_CORE2_RUN";
    "__PRIVATE_DATA_CORE2_LOAD_ADDRESS" = "_lc_gb_PRIVATE_DATA_CORE2_LOAD";

    "__PRIVATE_BSS_CORE3" = "_lc_gb_PRIVATE_BSS_CORE3_RUN";
    "__PRIVATE_BSS_CORE3_END" = "_lc_ge_PRIVATE_BSS_CORE3_RUN";

    "__PRIVATE_CODE_CORE3" = "_lc_gb_PRIVATE_CODE_CORE3_RUN";
    "__PRIVATE_CODE_CORE3_END" = "_lc_ge_PRIVATE_CODE_CORE3_RUN";
    "__PRIVATE_CODE_CORE3_LOAD_ADDRESS" = "_lc_gb_PRIVATE_CODE_CORE3_LOAD";

    "__PRIVATE_DATA_CORE3" = "_lc_gb_PRIVATE_DATA_CORE3_RUN";
    "__PRIVATE_DATA_CORE3_END" = "_lc_ge_PRIVATE_DATA_CORE3_RUN";
    "__PRIVATE_DATA_CORE3_LOAD_ADDRESS" = "_lc_gb_PRIVATE_DATA_CORE3_LOAD";

    "__UNCLEAR_RAM_BSS" = "_lc_gb_UNCLEAR_RAM_BSS_RUN";
    "__UNCLEAR_RAM_BSS_END" = "_lc_ge_UNCLEAR_RAM_BSS_RUN";

    "__UNDEFINE_RAM_BSS" = "_lc_gb_UNDEFINE_RAM_BSS_RUN";
    "__UNDEFINE_RAM_BSS_END" = "_lc_ge_UNDEFINE_RAM_BSS_RUN";

    "__UNDEFINE_RAM_DATA" = "_lc_gb_UNDEFINE_RAM_DATA_RUN";
    "__UNDEFINE_RAM_DATA_END" = "_lc_ge_UNDEFINE_RAM_DATA_RUN";
    "__UNDEFINE_RAM_DATA_LOAD_ADDRESS" = "_lc_gb_UNDEFINE_RAM_DATA_LOAD";

}


