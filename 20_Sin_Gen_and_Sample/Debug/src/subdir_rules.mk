################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/TA_PWM.obj: ../src/TA_PWM.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"E:/ti/ccsv5/tools/compiler/msp430_4.1.1/bin/cl430" -vmsp --abi=coffabi -g --include_path="D:/workspace/msp430G2/20_Sin_Gen_and_Sample/src" --include_path="E:/ti/ccsv5/ccs_base/msp430/include" --include_path="E:/ti/ccsv5/tools/compiler/msp430_4.1.1/include" --define=__MSP430G2553__ --diag_warning=225 --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="src/TA_PWM.pp" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


