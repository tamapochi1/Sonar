################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/cg_src/r_cg_bsc.c \
../src/cg_src/r_cg_bsc_user.c \
../src/cg_src/r_cg_cgc.c \
../src/cg_src/r_cg_cgc_user.c \
../src/cg_src/r_cg_hardware_setup.c \
../src/cg_src/r_cg_riic.c \
../src/cg_src/r_cg_riic_user.c \
../src/cg_src/r_cg_scifa.c \
../src/cg_src/r_cg_scifa_user.c 

COMPILER_OBJS += \
src/cg_src/r_cg_bsc.obj \
src/cg_src/r_cg_bsc_user.obj \
src/cg_src/r_cg_cgc.obj \
src/cg_src/r_cg_cgc_user.obj \
src/cg_src/r_cg_hardware_setup.obj \
src/cg_src/r_cg_riic.obj \
src/cg_src/r_cg_riic_user.obj \
src/cg_src/r_cg_scifa.obj \
src/cg_src/r_cg_scifa_user.obj 

C_DEPS += \
src/cg_src/r_cg_bsc.d \
src/cg_src/r_cg_bsc_user.d \
src/cg_src/r_cg_cgc.d \
src/cg_src/r_cg_cgc_user.d \
src/cg_src/r_cg_hardware_setup.d \
src/cg_src/r_cg_riic.d \
src/cg_src/r_cg_riic_user.d \
src/cg_src/r_cg_scifa.d \
src/cg_src/r_cg_scifa_user.d 

# Each subdirectory must supply rules for building sources it contributes
src/cg_src/%.obj: ../src/cg_src/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx -MM -MP -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" -isa=rxv2 -fpu -include="C:\Program Files (x86)\Renesas\RX\2_7_0\include","F:\Git\Sonar\e2Projects\Sonar\r_bsp","F:\Git\Sonar\e2Projects\Sonar\src","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\driver\inc","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\hw\inc","F:\Git\Sonar\e2Projects\Sonar\r_config","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc\src\inc" -lang=c99 -nomessage -debug -nologo  "$<"
	ccrx -isa=rxv2 -fpu -include="C:\Program Files (x86)\Renesas\RX\2_7_0\include","F:\Git\Sonar\e2Projects\Sonar\r_bsp","F:\Git\Sonar\e2Projects\Sonar\src","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\driver\inc","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\hw\inc","F:\Git\Sonar\e2Projects\Sonar\r_config","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc\src\inc" -lang=c99 -nomessage -output=obj -obj_path="src/cg_src" -debug -nologo "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

