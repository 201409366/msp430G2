################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
HW_filter/ADC10.obj: ../HW_filter/ADC10.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430/bin/cl430" -vmsp --abi=coffabi -g --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="F:/360yunpan/MSP430 Launchpad/Sin_Gen_and_Sample/TimerA_Test" --include_path="F:/360yunpan/MSP430 Launchpad/Sin_Gen_and_Sample/HW_filter" --include_path="C:/ti/ccsv5/tools/compiler/msp430/include" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="HW_filter/ADC10.pp" --obj_directory="HW_filter" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

HW_filter/filter.obj: ../HW_filter/filter.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430/bin/cl430" -vmsp --abi=coffabi -g --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="F:/360yunpan/MSP430 Launchpad/Sin_Gen_and_Sample/TimerA_Test" --include_path="F:/360yunpan/MSP430 Launchpad/Sin_Gen_and_Sample/HW_filter" --include_path="C:/ti/ccsv5/tools/compiler/msp430/include" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="HW_filter/filter.pp" --obj_directory="HW_filter" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


