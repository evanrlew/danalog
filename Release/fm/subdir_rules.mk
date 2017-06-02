################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
fm/envelope.obj: ../fm/envelope.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O2 --include_path="C:/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/evan/workspace_v5_5/danalog/Release" --include_path="C:/ti/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/rtdx/include/c5500" --define=c5535 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="fm/envelope.pp" --obj_directory="fm" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

fm/fm.obj: ../fm/fm.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O2 --include_path="C:/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/evan/workspace_v5_5/danalog/Release" --include_path="C:/ti/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/rtdx/include/c5500" --define=c5535 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="fm/fm.pp" --obj_directory="fm" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

fm/ringbuf.obj: ../fm/ringbuf.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O2 --include_path="C:/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/evan/workspace_v5_5/danalog/Release" --include_path="C:/ti/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/rtdx/include/c5500" --define=c5535 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="fm/ringbuf.pp" --obj_directory="fm" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


