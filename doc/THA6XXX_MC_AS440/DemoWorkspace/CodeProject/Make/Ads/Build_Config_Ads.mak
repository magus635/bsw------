#****************************************************************************************************
#*   FileName			  : Build_Config_Ads.mak
#*
#*   Platform			  : AUTOSAR
#*
#*   Peripheral			: None
#*
#*   brief				 : This file contains makefile build toolchain for IAR. 
#*						   This file is only a Demo for user and is not part of the production code
#*						   deliverables.
#*
#*   Autosar Version	   : 4.4.0
#*
#*   Build Version		 : Cortex-R52+/THA6xxx
#*
#*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
#*   All Rights Reserved.
#*
#****************************************************************************************************
#
#****************************************************************************************************
#**						  Revision Control History											  **
#****************************************************************************************************
#*
# 
#*
#****************************************************************************************************
#****************************************************************************************************
#* Update ARM tool chain path that has been installed correctly
#****************************************************************************************************
ARM_TOOLS_CHAINS_PATH ?= C:/Program Files/Arm/Development Studio 2022.1

#****************************************************************************************************
#* Do not change there path when you build project via "Build.bat"
#****************************************************************************************************
ifeq ($(ARM_CONFIG_PATH),)
    export ARM_CONFIG_PATH := $(ARM_TOOLS_CHAINS_PATH)/sw/ARMCompiler6.18/bin
    $(shell echo Default ARM_CONFIG_PATH selected: $(ARM_CONFIG_PATH) 1>&2)
endif
ifeq ($(ARMLMD_LICENSE_FILE),)
    # Do not change it when you build project via "Build.bat"
    export ARMLMD_LICENSE_FILE := $(ARM_TOOLS_CHAINS_PATH)/ds_license.lic
    $(shell echo Default ARMLMD_LICENSE_FILE selected: $(ARMLMD_LICENSE_FILE) 1>&2)
endif
ifeq ($(ARM_PRODUCT_DEF),)
    # Do not change it when you build project via "Build.bat"
    export ARM_PRODUCT_DEF := $(ARM_TOOLS_CHAINS_PATH)/sw/mappings/gold.elmap
    $(shell echo Default ARM_PRODUCT_DEF selected: $(ARM_PRODUCT_DEF) 1>&2)
endif
FLOATTYPE :=-mfpu=neon-fp-armv8 
# Linker files
ifeq ($(DERIVATIVE),THA6412)
    LINKER_FILE := LinkerAdsPfTha6412.scat
    DEFCHIP :=THA6_THA6412
else  ifeq ($(DERIVATIVE),THA6206)
    LINKER_FILE := LinkerAdsPf.scat
    DEFCHIP :=THA6_THA6206

    ifeq ($(DERIVATIVE_SUB),)

    else
        DEFCHIP :=THA6_THA6206D
    endif



else
    LINKER_FILE := LinkerAdsPfTha6104.scat
    DEFCHIP :=THA6_THA6104
    #Enable the Armv7 VFPv3XD Floating-point Extension, for single precision only. Disable the Advanced SIMD extension
    FLOATTYPE :=-mfpu=vfpv3xd 

endif


# !!!MUST!!!  : Add ARM_CONFIG_PATH into path environment variable
export PATH := $(ARM_CONFIG_PATH):$(PATH)

#****************************************************************************************************
# ADS toolchain build directive	 -fstack-usage
#****************************************************************************************************
CC := armclang
LD := armlink
AR := armar
FE := fromelf

CFLAGS = \
    -mcpu=Cortex-R52 \
    --target=arm-arm-none-eabi \
    -marm \
    -mfloat-abi=hard \
    $(FLOATTYPE) \
    -DAUTOSAR_OS_NOT_USED \
    -D$(DEFCHIP) \
    -std=c99	\
    -O0	\
    -mlittle-endian	\
    -g \
    -Wall \


# Link file rule
$(TARGET) : $(OUT_FILES)  
	@$(LD)  $(OUT_FILES)  --symbols --load_addr_map_info --info veneers  --scatter=$(LINKER_PATH)\$(LINKER_FILE) --entry=Start -o $(TARGET) --info=totals --info=unused --diag_suppress=L6314 --no_startup --map  --list="$(MAPFILE)"
	$(FE) --i32combined --output=$(HEXFILE) $(TARGET) $@
	$(FE)  --bin -o $(BINARY) $@ 

# $(FE) --text -a -c --output=$(ASMFILE) $@

# C file build rule.
$(BUILD_PATH)/%.o : %.c
	@$(CC) -c $(CFLAGS) $(addprefix -I, $(INCLUDE_DIRS)) -o $@ $<

# Assembly file build rule.
# $(BUILD_PATH)/%.o : %.s
# 	@$(CC) -c $(CFLAGS) $(addprefix -I, $(INCLUDE_DIRS)) -x assembler-with-cpp -o $@  $<
