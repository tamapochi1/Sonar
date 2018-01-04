################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../r_usb_pcdc/src/r_usb_pcdc_driver.c 

COMPILER_OBJS += \
r_usb_pcdc/src/r_usb_pcdc_driver.obj 

C_DEPS += \
r_usb_pcdc/src/r_usb_pcdc_driver.d 

# Each subdirectory must supply rules for building sources it contributes
r_usb_pcdc/src/%.obj: ../r_usb_pcdc/src/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx -MM -MP -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" -isa=rxv2 -fpu -include="C:\Program Files (x86)\Renesas\RX\2_7_0\include","F:\Git\Sonar\e2Projects\Sonar\r_bsp","F:\Git\Sonar\e2Projects\Sonar\src","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\driver\inc","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\hw\inc","F:\Git\Sonar\e2Projects\Sonar\r_config","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc\src\inc" -lang=c99 -nomessage -debug -nologo  "$<"
	ccrx -isa=rxv2 -fpu -include="C:\Program Files (x86)\Renesas\RX\2_7_0\include","F:\Git\Sonar\e2Projects\Sonar\r_bsp","F:\Git\Sonar\e2Projects\Sonar\src","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\driver\inc","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\hw\inc","F:\Git\Sonar\e2Projects\Sonar\r_config","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc\src\inc" -lang=c99 -nomessage -output=obj -obj_path="r_usb_pcdc/src" -debug -nologo "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

