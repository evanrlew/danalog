################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/c5500_4.4.1

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./audio/sintable.obj" \
"./audio/singen.obj" \
"./fm/ringbuf.obj" \
"./fm/fm.obj" \
"./fm/envelope.obj" \
"./io/midi_queue.obj" \
"./io/midi.obj" \
"./io/fetch_data.obj" \
"./pconfig/spi_config.obj" \
"./pconfig/i2s_dma.obj" \
"./pconfig/aic3204.obj" \
"./main.obj" \
"./hellocfg_c.obj" \
"./hellocfg.obj" \
-l"libc.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include pconfig/subdir_vars.mk
-include io/subdir_vars.mk
-include fm/subdir_vars.mk
-include audio/subdir_vars.mk
-include subdir_rules.mk
-include pconfig/subdir_rules.mk
-include io/subdir_rules.mk
-include fm/subdir_rules.mk
-include audio/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: danalog.out

# Tool invocations
danalog.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C5500 Linker'
	"C:/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O2 --define=c5535 --display_error_number --diag_warning=225 --ptrdiff_size=16 -z -m"danalog.map" --stack_size=0x200 --heap_size=0x400 -i"C:/ti/ccsv5/tools/compiler/c5500_4.4.1/lib" -i"C:/ti/ccsv5/tools/compiler/c5500_4.4.1/include" -i"C:/ti/bios_5_42_02_10/packages/ti/rtdx/lib/c5500" -i"C:/ti/bios_5_42_02_10/packages/ti/bios/lib" --reread_libs --display_error_number --warn_sections --xml_link_info="danalog_linkInfo.xml" --rom_model --sys_stacksize=0x200 -o "danalog.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C5500_EXECUTABLE_OUTPUTS__QUOTED)$(GEN_HDRS__QUOTED)$(GEN_MISC_FILES__QUOTED)$(GEN_FILES__QUOTED)$(GEN_CMDS__QUOTED) "danalog.out"
	-$(RM) "hellocfg_c.pp" "main.pp" "pconfig\aic3204.pp" "pconfig\i2s_dma.pp" "pconfig\spi_config.pp" "io\fetch_data.pp" "io\midi.pp" "io\midi_queue.pp" "fm\envelope.pp" "fm\fm.pp" "fm\ringbuf.pp" "audio\singen.pp" "audio\sintable.pp" 
	-$(RM) "hellocfg.pp" 
	-$(RM) "hellocfg.obj" "hellocfg_c.obj" "main.obj" "pconfig\aic3204.obj" "pconfig\i2s_dma.obj" "pconfig\spi_config.obj" "io\fetch_data.obj" "io\midi.obj" "io\midi_queue.obj" "fm\envelope.obj" "fm\fm.obj" "fm\ringbuf.obj" "audio\singen.obj" "audio\sintable.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

