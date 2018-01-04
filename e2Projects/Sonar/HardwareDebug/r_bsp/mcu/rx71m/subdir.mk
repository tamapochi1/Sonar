################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../r_bsp/mcu/rx71m/cpu.c \
../r_bsp/mcu/rx71m/locking.c \
../r_bsp/mcu/rx71m/mcu_clocks.c \
../r_bsp/mcu/rx71m/mcu_init.c \
../r_bsp/mcu/rx71m/mcu_interrupts.c \
../r_bsp/mcu/rx71m/mcu_locks.c \
../r_bsp/mcu/rx71m/mcu_mapped_interrupts.c 

COMPILER_OBJS += \
r_bsp/mcu/rx71m/cpu.obj \
r_bsp/mcu/rx71m/locking.obj \
r_bsp/mcu/rx71m/mcu_clocks.obj \
r_bsp/mcu/rx71m/mcu_init.obj \
r_bsp/mcu/rx71m/mcu_interrupts.obj \
r_bsp/mcu/rx71m/mcu_locks.obj \
r_bsp/mcu/rx71m/mcu_mapped_interrupts.obj 

C_DEPS += \
r_bsp/mcu/rx71m/cpu.d \
r_bsp/mcu/rx71m/locking.d \
r_bsp/mcu/rx71m/mcu_clocks.d \
r_bsp/mcu/rx71m/mcu_init.d \
r_bsp/mcu/rx71m/mcu_interrupts.d \
r_bsp/mcu/rx71m/mcu_locks.d \
r_bsp/mcu/rx71m/mcu_mapped_interrupts.d 

# Each subdirectory must supply rules for building sources it contributes
r_bsp/mcu/rx71m/%.obj: ../r_bsp/mcu/rx71m/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx -MM -MP -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" -isa=rxv2 -fpu -include="C:\Program Files (x86)\Renesas\RX\2_7_0\include","F:\Git\Sonar\e2Projects\Sonar\r_bsp","F:\Git\Sonar\e2Projects\Sonar\src","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\driver\inc","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\hw\inc","F:\Git\Sonar\e2Projects\Sonar\r_config","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc\src\inc" -lang=c99 -nomessage -debug -nologo  "$<"
	ccrx -isa=rxv2 -fpu -include="C:\Program Files (x86)\Renesas\RX\2_7_0\include","F:\Git\Sonar\e2Projects\Sonar\r_bsp","F:\Git\Sonar\e2Projects\Sonar\src","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\driver\inc","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\hw\inc","F:\Git\Sonar\e2Projects\Sonar\r_config","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc\src\inc" -lang=c99 -nomessage -output=obj -obj_path="r_bsp/mcu/rx71m" -debug -nologo "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

