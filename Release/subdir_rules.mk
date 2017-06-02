################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
hellocfg.cmd: ../hello.tcf
	@echo 'Building file: $<'
	@echo 'Invoking: TConf'
	"C:/ti/bios_5_42_02_10/xdctools/tconf" -b -Dconfig.importPath="C:/ti/bios_5_42_02_10/packages;" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hellocfg.s??: | hellocfg.cmd
hellocfg_c.c: | hellocfg.cmd
hellocfg.h: | hellocfg.cmd
hellocfg.h??: | hellocfg.cmd
hello.cdb: | hellocfg.cmd

hellocfg.obj: ./hellocfg.s?? $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O2 --include_path="C:/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/evan/workspace_v5_5/danalog/Release" --include_path="C:/ti/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/rtdx/include/c5500" --define=c5535 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="hellocfg.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

hellocfg_c.obj: ./hellocfg_c.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O2 --include_path="C:/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/evan/workspace_v5_5/danalog/Release" --include_path="C:/ti/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/rtdx/include/c5500" --define=c5535 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="hellocfg_c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv5/tools/compiler/c5500_4.4.1/bin/cl55" -v5515 --memory_model=large -O2 --include_path="C:/ti/ccsv5/tools/compiler/c5500_4.4.1/include" --include_path="C:/Users/evan/workspace_v5_5/danalog/Release" --include_path="C:/ti/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/rtdx/include/c5500" --define=c5535 --display_error_number --diag_warning=225 --ptrdiff_size=16 --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


