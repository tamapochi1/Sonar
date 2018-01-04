################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../r_usb_basic/src/hw/r_usb_creg_abs.c \
../r_usb_basic/src/hw/r_usb_creg_access.c \
../r_usb_basic/src/hw/r_usb_dma.c \
../r_usb_basic/src/hw/r_usb_hostelectrical.c \
../r_usb_basic/src/hw/r_usb_hreg_abs.c \
../r_usb_basic/src/hw/r_usb_hreg_access.c \
../r_usb_basic/src/hw/r_usb_preg_abs.c \
../r_usb_basic/src/hw/r_usb_preg_access.c \
../r_usb_basic/src/hw/r_usb_rx_mcu.c 

COMPILER_OBJS += \
r_usb_basic/src/hw/r_usb_creg_abs.obj \
r_usb_basic/src/hw/r_usb_creg_access.obj \
r_usb_basic/src/hw/r_usb_dma.obj \
r_usb_basic/src/hw/r_usb_hostelectrical.obj \
r_usb_basic/src/hw/r_usb_hreg_abs.obj \
r_usb_basic/src/hw/r_usb_hreg_access.obj \
r_usb_basic/src/hw/r_usb_preg_abs.obj \
r_usb_basic/src/hw/r_usb_preg_access.obj \
r_usb_basic/src/hw/r_usb_rx_mcu.obj 

C_DEPS += \
r_usb_basic/src/hw/r_usb_creg_abs.d \
r_usb_basic/src/hw/r_usb_creg_access.d \
r_usb_basic/src/hw/r_usb_dma.d \
r_usb_basic/src/hw/r_usb_hostelectrical.d \
r_usb_basic/src/hw/r_usb_hreg_abs.d \
r_usb_basic/src/hw/r_usb_hreg_access.d \
r_usb_basic/src/hw/r_usb_preg_abs.d \
r_usb_basic/src/hw/r_usb_preg_access.d \
r_usb_basic/src/hw/r_usb_rx_mcu.d 

# Each subdirectory must supply rules for building sources it contributes
r_usb_basic/src/hw/%.obj: ../r_usb_basic/src/hw/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx -MM -MP -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" -isa=rxv2 -fpu -include="C:\Program Files (x86)\Renesas\RX\2_7_0\include","F:\Git\Sonar\e2Projects\Sonar\r_bsp","F:\Git\Sonar\e2Projects\Sonar\src","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\driver\inc","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\hw\inc","F:\Git\Sonar\e2Projects\Sonar\r_config","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc\src\inc" -lang=c99 -nomessage -debug -nologo  "$<"
	ccrx -isa=rxv2 -fpu -include="C:\Program Files (x86)\Renesas\RX\2_7_0\include","F:\Git\Sonar\e2Projects\Sonar\r_bsp","F:\Git\Sonar\e2Projects\Sonar\src","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\driver\inc","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\hw\inc","F:\Git\Sonar\e2Projects\Sonar\r_config","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc\src\inc" -lang=c99 -nomessage -output=obj -obj_path="r_usb_basic/src/hw" -debug -nologo "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

