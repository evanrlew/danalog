################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
pconfig/aic3204.obj: ../pconfig/aic3204.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O2 --include_path="C:/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/evan/workspace_v5_5/danalog/Release" --include_path="C:/ti/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/rtdx/include/c5500" --define=c5535 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="pconfig/aic3204.pp" --obj_directory="pconfig" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pconfig/i2s_dma.obj: ../pconfig/i2s_dma.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O2 --include_path="C:/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/evan/workspace_v5_5/danalog/Release" --include_path="C:/ti/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/rtdx/include/c5500" --define=c5535 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="pconfig/i2s_dma.pp" --obj_directory="pconfig" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

pconfig/spi_config.obj: ../pconfig/spi_config.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O2 --include_path="C:/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/evan/workspace_v5_5/danalog/Release" --include_path="C:/ti/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/rtdx/include/c5500" --define=c5535 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="pconfig/spi_config.pp" --obj_directory="pconfig" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


