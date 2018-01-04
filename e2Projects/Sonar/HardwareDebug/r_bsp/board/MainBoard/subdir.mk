################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../r_bsp/board/MainBoard/dbsct.c \
../r_bsp/board/MainBoard/hwsetup.c \
../r_bsp/board/MainBoard/lowlvl.c \
../r_bsp/board/MainBoard/lowsrc.c \
../r_bsp/board/MainBoard/resetprg.c \
../r_bsp/board/MainBoard/sbrk.c \
../r_bsp/board/MainBoard/vecttbl.c 

COMPILER_OBJS += \
r_bsp/board/MainBoard/dbsct.obj \
r_bsp/board/MainBoard/hwsetup.obj \
r_bsp/board/MainBoard/lowlvl.obj \
r_bsp/board/MainBoard/lowsrc.obj \
r_bsp/board/MainBoard/resetprg.obj \
r_bsp/board/MainBoard/sbrk.obj \
r_bsp/board/MainBoard/vecttbl.obj 

C_DEPS += \
r_bsp/board/MainBoard/dbsct.d \
r_bsp/board/MainBoard/hwsetup.d \
r_bsp/board/MainBoard/lowlvl.d \
r_bsp/board/MainBoard/lowsrc.d \
r_bsp/board/MainBoard/resetprg.d \
r_bsp/board/MainBoard/sbrk.d \
r_bsp/board/MainBoard/vecttbl.d 

# Each subdirectory must supply rules for building sources it contributes
r_bsp/board/MainBoard/%.obj: ../r_bsp/board/MainBoard/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx -MM -MP -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" -isa=rxv2 -fpu -include="C:\Program Files (x86)\Renesas\RX\2_7_0\include","F:\Git\Sonar\e2Projects\Sonar\r_bsp","F:\Git\Sonar\e2Projects\Sonar\src","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\driver\inc","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\hw\inc","F:\Git\Sonar\e2Projects\Sonar\r_config","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc\src\inc" -lang=c99 -nomessage -debug -nologo  "$<"
	ccrx -isa=rxv2 -fpu -include="C:\Program Files (x86)\Renesas\RX\2_7_0\include","F:\Git\Sonar\e2Projects\Sonar\r_bsp","F:\Git\Sonar\e2Projects\Sonar\src","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\driver\inc","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\hw\inc","F:\Git\Sonar\e2Projects\Sonar\r_config","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc\src\inc" -lang=c99 -nomessage -output=obj -obj_path="r_bsp/board/MainBoard" -debug -nologo "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

