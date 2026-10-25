#****************************************************************************************************
#*   FileName              : Build_Config_Iar.mak
#*
#*   Platform              : AUTOSAR
#*
#*   Peripheral            : None
#*
#*   brief                 : This file contains makefile build toolchain for IAR. 
#*                           This file is only a Demo for user and is not part of the production code
#*                           deliverables.
#*
#*   Autosar Version       : 4.4.0
#*
#*   Build Version         : Cortex-R52+/THA6xxx
#*
#*   Copyright (c) 2021, Beijing Tongxin Microelectroics Co., Ltd.
#*   All Rights Reserved.
#*
#****************************************************************************************************
#
#****************************************************************************************************
#**                          Revision Control History                                              **
#****************************************************************************************************
#*
#*   V1.0.0:  28-Jun-2023 : Create for IAR toolchain
#*
#****************************************************************************************************

# Do not change there path when you build project via "Build.bat"
# Update these paths, when you use IAR toolchain and these paths are incorrect
ifeq ($(IAR_DIR),)
    IAR_DIR := C:\Program Files\IAR Systems\Embedded Workbench 9.2 EWARM FS 9.50.3\arm\bin
    $(shell echo Default IAR_DIR selected: $(IAR_DIR) 1>&2)
endif
FLOATTYPE :=--cpu=Cortex-R52 \
            --fpu=VFPv5


# Linker files
ifeq ($(DERIVATIVE),THA6412)
    LINKER_FILE := LinkerIarPfTha6412.icf
    DEFCHIP :=THA6_THA6412
else  ifeq ($(DERIVATIVE),THA6206)
	LINKER_FILE = LinkerIarPf.icf
	DEFCHIP :=THA6_THA6206
    ifeq ($(DERIVATIVE_SUB),)

	else
		DEFCHIP :=THA6_THA6206D
	endif
else
    LINKER_FILE := LinkerIarPfTha6104.icf
    DEFCHIP :=THA6_THA6104 
	
# none: No FPU (default)
#fp-architecture: Base variant of the specified architecture
# fp-architecture-SP: Single-precision variant
# fp-architecture_D16: Variant with 16 D registers
# fp_architecture_Fp16: Variant with half-precision extensions
# !!! IAR 90.50.3 do not support Single-precision variant !!!
	FLOATTYPE :=--cpu=Cortex-R52.no_neon \
            --fpu=fp-VFPv5-SP

endif



CC := $(IAR_DIR)/iccarm.exe
LD := $(IAR_DIR)/ilinkarm.exe
AR := $(IAR_DIR)/iasmarm.exe
FE := $(IAR_DIR)/ielftool.exe

CFLAGS = \
	--arm \
	$(FLOATTYPE) \
	--silent \
	-On \
	--endian=little \
	--debug \
	-DAUTOSAR_OS_NOT_USED \
    -D$(DEFCHIP) \
	--dlib_config normal \
	-e 



# --no_mem_idioms \
--no_wrap_diagnostics \
	--c89  \

LDFLAGS = \
	$(FLOATTYPE) \
    --entry Start \
    --no_wrap_diagnostics \
	--semihosting \
	--config $(LINKER_PATH)/$(LINKER_FILE) 

ASMFLAGS = \
    --cpu Cortex-R52 \
    --cpu_mode arm \
	-D__ICCARM__


# Link file rule
$(TARGET) : $(OUT_FILES) $(LINKER_PATH)\$(LINKER_FILE)
	@$(LD) $(LDFLAGS) $(OUT_FILES) --map $(MAPFILE) -o $@
	$(FE) --bin $(TARGET) $(BINARY)
	$(FE) --ihex $(TARGET) $(HEXFILE)
	
# C file build rule.
$(BUILD_PATH)/%.o : %.c
	@$(CC) $(CFLAGS) $(addprefix -I, $(INCLUDE_DIRS)) -o $@ -c $<

# Assembly file build rule.
# $(BUILD_PATH)/%.o : %.s
# 	@$(AR) $(ASMFLAGS) $(addprefix -I, $(INCLUDE_DIRS)) -o $@ -c $<
