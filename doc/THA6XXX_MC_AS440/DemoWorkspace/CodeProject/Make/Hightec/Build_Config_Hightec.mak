#****************************************************************************************************
#*   FileName              : Build_Config_hightec.mak
#*
#*   Platform              : AUTOSAR
#*
#*   Peripheral            : None
#*
#*   brief                 : This file contains makefile build toolchain for HIGHTEC. 
#*                           This file is only a Demo for user and is not part of the production code
#*                           deliverables.
#*
#*   Autosar Version       : 4.4.0
#*
#*   Build Version         : Cortex-R52/THA6
#*
#*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
#*   All Rights Reserved.     -nostdlib 
#*
#****************************************************************************************************
#
#****************************************************************************************************
#**                          Revision Control History                          **
#****************************************************************************************************
#*
# 
#*
#****************************************************************************************************
# Do not change there path when you build project via "Build.bat"
# Update these paths, when you use HIGHTEC toolchain and these paths are incorrect
ifeq ($(HIGHTEC_DIR),)
    HIGHTEC_DIR := C:\HighTec\toolchains\arm\v8.1.0\bin
    $(shell echo Default Hightec selected: $(HIGHTEC_DIR) 1>&2)
endif
FLOATTYPE :=-mfpu="neon-fp-armv8" 

# Linker files
ifeq ($(DERIVATIVE),THA6412)
    LINKER_FILE := LinkerHightecPfTha6412.ld
    DEFCHIP :=THA6_THA6412
else  ifeq ($(DERIVATIVE),THA6206)
    LINKER_FILE := LinkerHightecPf.ld
    DEFCHIP :=THA6_THA6206
    ifeq ($(DERIVATIVE_SUB),)

	else
		DEFCHIP :=THA6_THA6206D
	endif


else
    LINKER_FILE := LinkerHightecPfTha6104.ld
    DEFCHIP :=THA6_THA6104
    FLOATTYPE :=-mfpu="vfpv3xd" 
endif


#****************************************************************************************************
# HIGHTEC toolchain build directive
#****************************************************************************************************
CC := $(HIGHTEC_DIR)/clang.exe
LD := $(HIGHTEC_DIR)/ld.lld.exe
AR := $(HIGHTEC_DIR)/llvm-ar.exe
FE := $(HIGHTEC_DIR)/llvm-objcopy.exe


CFLAGS = \
    --target=arm-none-eabi \
    -mcpu=cortex-r52 \
    -march=armv8-r \
    -marm \
    -gdwarf-4 \
    -O0 \
    -fno-common \
    -fno-short-enums \
    -Wall \
    -Wextra \
    -DAUTOSAR_OS_NOT_USED \
    -D$(DEFCHIP) \
    -ffreestanding \
    -mfloat-abi="hard" \
    $(FLOATTYPE) \
    -mlittle-endian \
    -std=c99


LDFLAGS = \
    -mcpu=cortex-r52 \
    -march=armv8-r \
    -Wl,--gc-sections \
    -Wl,--entry=Start \
    -mfloat-abi="hard" \
	$(FLOATTYPE) \

ASMFLAGS = \
    -mcpu=cortex-r52 \
    -march=armv8-r \
    -x assembler-with-cpp \
    -marm \

# Link file rule
$(TARGET) : $(OUT_FILES)  $(LINKER_PATH)\$(LINKER_FILE)
	@$(CC)  $(OUT_FILES) $(LDFLAGS) -Wl,-T"$(LINKER_PATH)\$(LINKER_FILE)" -o $(TARGET) -Wl,--Map="$(MAPFILE)"
	$(FE) -O ihex $(TARGET) $(HEXFILE)

# C file build rule.
$(BUILD_PATH)/%.o : %.c
	@$(CC) -c $(CFLAGS) $(addprefix -I, $(INCLUDE_DIRS)) -o $@ $<

# Assembly file build rule.
# $(BUILD_PATH)/%.o : %.s
# 	@$(CC) -c $(ASMFLAGS) $(addprefix -I, $(INCLUDE_DIRS)) -o $@  $<
