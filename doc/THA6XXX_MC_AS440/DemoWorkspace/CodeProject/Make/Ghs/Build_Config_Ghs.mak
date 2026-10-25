#****************************************************************************************************
#*   FileName              : Build_Config_Ghs.mak
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
#*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
#*   All Rights Reserved.
#*
#****************************************************************************************************
#
#****************************************************************************************************
#**                          Revision Control History                                              **
#****************************************************************************************************
#*
# 
#*
#****************************************************************************************************


# Do not change there path when you build project via "Build.bat"
# Update these paths, when you use IAR toolchain and these paths are incorrect
ifeq ($(GHS_DIR),)
    GHS_DIR := C:/ghs/comp_202314
    $(shell echo Default GHS_DIR selected: $(GHS_DIR) 1>&2)
endif

FLOATTYPE :=-fhard 
# Linker files
ifeq ($(DERIVATIVE),THA6412)
    LINKER_FILE := LinkerGhsPfTha6412.ld
    DEFCHIP :=THA6_THA6412	
else  ifeq ($(DERIVATIVE),THA6206)
	LINKER_FILE = LinkerGhsPf.ld
	DEFCHIP :=THA6_THA6206
    ifeq ($(DERIVATIVE_SUB),)

	else
		DEFCHIP :=THA6_THA6206D
	endif

else
    LINKER_FILE := LinkerGhsPfTha6104.ld
    DEFCHIP :=THA6_THA6104
	FLOATTYPE :=-fhard \
	           -fsingle

endif



# DTHUMBEN :=THUMB_ENABLE
# DTHUMBEN :=THUMB_DISABLE

THUMB_EN :=thumb

ifeq ($(DTHUMBEN),THUMB_DISABLE)
    THUMB_EN :=nothumb
endif


#****************************************************************************************************
# GHS toolchain build directive

# -cpu=cortexr52 \THA6206 Armv8-R architecture in AArch32 state  THA6206 Cortex-R52
# -fpu=vfpv3 \ The hardware floating-point operation function is enabled by default, and R52 uses version VFPV3
# -fhard \ open hard folat
#-c99\ 
# -O0	\close optimize
# -littleendian  
# -c  compiler only
# -I  include files
# 	-dwarf2 \ -Wall \ output debug info -G \all warrnig
# 
# -preprocess_assembly_files \   Control whether to preprocess assembly files with standard extensions such as. s and. asm.
# -align8 \8-byte alignment, Double, etc. will occupy 64 bits
# --gnu_asm \Supports embedded assembly syntax
# --no_commons \Global variables that are not explicitly initialized will be placed in COMMON, and when linked, the data inside will be reassigned to different sections



#****************************************************************************************************

CC=ccarm
LD=ccarm
AR=ax
# conflict 
# -O0 		--no_slash_comment \

CFLAGS = \
	-littleendian	\
	-Wall \
	-$(THUMB_EN) \
	-D$(DEFCHIP) \
	-D$(DTHUMBEN) \
	-cpu=cortexr52 \
	-align8 \
	$(FLOATTYPE) \
	-c99 \
	-Osize	\
	--gnu_asm \
	-G \
	-dwarf2 \
	--no_commons \
	-DAUTOSAR_OS_NOT_USED \
	-nofloatsingle \
	--ghstd=last \
	-dual_debug \
	--long_long \
	-keeptempfiles \
	-Wimplicit-int \
	-Wshadow \
	-Wtrigraphs \
	-Wundef \
	--no_short_enum \
	--unsigned_chars \
	--unsigned_fields \
	--no_exceptions \
	-nofarcalls \
	-no_misalign_pack \
	--prototype_errors \
	--incorrect_pragma_warnings \
	-argcheck=normal \
	-globalcheck=normal \
	-globalcheck_qualifiers \
	--diag_error=1,9,39,42,47,61,62,63,68,69,120,144,152,161,167,172,175,187,193,301,549,991,1512,1513,1514,1515,1547,1702,1704,1713,1721,1728,1732,1736,1844  \
	--no_slash_comment \
	--c++17
	
#	-nothumb \






LDFLAGS = \
	-nostartfiles \
	-cpu=cortexr52 \
	-align8 \
	$(FLOATTYPE) \
	-full_debug_info \
	-hex=$(HEXFILE) \
	-e=Start \
	-G \
	-map \
	-keepmap \
	-Manx \
	-dual_debug \
	-dwarf2 \
	-delete \
	-ignore_debug_references \
	--preprocess_linker_directive_full \
	-argcheck=normal \
	-globalcheck=normal \
	-globalcheck_qualifiers \
	--diag_error=283,545,587



# Link file rule
$(TARGET) : $(OUT_FILES)  
	@$(LD)  $^  $(LDFLAGS) -T $(LINKER_PATH)/$(LINKER_FILE) -o $@
	
# C file build rule.
$(BUILD_PATH)/%.o : %.c
	@$(CC) -c $(CFLAGS) $(addprefix -I, $(INCLUDE_DIRS)) -o $@ -c $<
