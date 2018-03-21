################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../r_usb_basic/src/driver/r_usb_cdataio.c \
../r_usb_basic/src/driver/r_usb_clibusbip.c \
../r_usb_basic/src/driver/r_usb_hbc.c \
../r_usb_basic/src/driver/r_usb_hcontrolrw.c \
../r_usb_basic/src/driver/r_usb_hdriver.c \
../r_usb_basic/src/driver/r_usb_hhubsys.c \
../r_usb_basic/src/driver/r_usb_hintfifo.c \
../r_usb_basic/src/driver/r_usb_hinthandler_usbip0.c \
../r_usb_basic/src/driver/r_usb_hinthandler_usbip1.c \
../r_usb_basic/src/driver/r_usb_hlibusbip.c \
../r_usb_basic/src/driver/r_usb_hmanager.c \
../r_usb_basic/src/driver/r_usb_hscheduler.c \
../r_usb_basic/src/driver/r_usb_hsignal.c \
../r_usb_basic/src/driver/r_usb_hstdfunction.c \
../r_usb_basic/src/driver/r_usb_pbc.c \
../r_usb_basic/src/driver/r_usb_pcontrolrw.c \
../r_usb_basic/src/driver/r_usb_pdriver.c \
../r_usb_basic/src/driver/r_usb_peptable.c \
../r_usb_basic/src/driver/r_usb_pintfifo.c \
../r_usb_basic/src/driver/r_usb_pinthandler_usbip0.c \
../r_usb_basic/src/driver/r_usb_plibusbip.c \
../r_usb_basic/src/driver/r_usb_psignal.c \
../r_usb_basic/src/driver/r_usb_pstdfunction.c \
../r_usb_basic/src/driver/r_usb_pstdrequest.c \
../r_usb_basic/src/driver/r_usb_usbif_api.c 

COMPILER_OBJS += \
r_usb_basic/src/driver/r_usb_cdataio.obj \
r_usb_basic/src/driver/r_usb_clibusbip.obj \
r_usb_basic/src/driver/r_usb_hbc.obj \
r_usb_basic/src/driver/r_usb_hcontrolrw.obj \
r_usb_basic/src/driver/r_usb_hdriver.obj \
r_usb_basic/src/driver/r_usb_hhubsys.obj \
r_usb_basic/src/driver/r_usb_hintfifo.obj \
r_usb_basic/src/driver/r_usb_hinthandler_usbip0.obj \
r_usb_basic/src/driver/r_usb_hinthandler_usbip1.obj \
r_usb_basic/src/driver/r_usb_hlibusbip.obj \
r_usb_basic/src/driver/r_usb_hmanager.obj \
r_usb_basic/src/driver/r_usb_hscheduler.obj \
r_usb_basic/src/driver/r_usb_hsignal.obj \
r_usb_basic/src/driver/r_usb_hstdfunction.obj \
r_usb_basic/src/driver/r_usb_pbc.obj \
r_usb_basic/src/driver/r_usb_pcontrolrw.obj \
r_usb_basic/src/driver/r_usb_pdriver.obj \
r_usb_basic/src/driver/r_usb_peptable.obj \
r_usb_basic/src/driver/r_usb_pintfifo.obj \
r_usb_basic/src/driver/r_usb_pinthandler_usbip0.obj \
r_usb_basic/src/driver/r_usb_plibusbip.obj \
r_usb_basic/src/driver/r_usb_psignal.obj \
r_usb_basic/src/driver/r_usb_pstdfunction.obj \
r_usb_basic/src/driver/r_usb_pstdrequest.obj \
r_usb_basic/src/driver/r_usb_usbif_api.obj 

C_DEPS += \
r_usb_basic/src/driver/r_usb_cdataio.d \
r_usb_basic/src/driver/r_usb_clibusbip.d \
r_usb_basic/src/driver/r_usb_hbc.d \
r_usb_basic/src/driver/r_usb_hcontrolrw.d \
r_usb_basic/src/driver/r_usb_hdriver.d \
r_usb_basic/src/driver/r_usb_hhubsys.d \
r_usb_basic/src/driver/r_usb_hintfifo.d \
r_usb_basic/src/driver/r_usb_hinthandler_usbip0.d \
r_usb_basic/src/driver/r_usb_hinthandler_usbip1.d \
r_usb_basic/src/driver/r_usb_hlibusbip.d \
r_usb_basic/src/driver/r_usb_hmanager.d \
r_usb_basic/src/driver/r_usb_hscheduler.d \
r_usb_basic/src/driver/r_usb_hsignal.d \
r_usb_basic/src/driver/r_usb_hstdfunction.d \
r_usb_basic/src/driver/r_usb_pbc.d \
r_usb_basic/src/driver/r_usb_pcontrolrw.d \
r_usb_basic/src/driver/r_usb_pdriver.d \
r_usb_basic/src/driver/r_usb_peptable.d \
r_usb_basic/src/driver/r_usb_pintfifo.d \
r_usb_basic/src/driver/r_usb_pinthandler_usbip0.d \
r_usb_basic/src/driver/r_usb_plibusbip.d \
r_usb_basic/src/driver/r_usb_psignal.d \
r_usb_basic/src/driver/r_usb_pstdfunction.d \
r_usb_basic/src/driver/r_usb_pstdrequest.d \
r_usb_basic/src/driver/r_usb_usbif_api.d 

# Each subdirectory must supply rules for building sources it contributes
r_usb_basic/src/driver/%.obj: ../r_usb_basic/src/driver/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	ccrx -MM -MP -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" -isa=rxv2 -fpu -include="C:\Program Files (x86)\Renesas\RX\2_7_0\include","F:\Git\Sonar\e2Projects\Sonar\r_bsp","F:\Git\Sonar\e2Projects\Sonar\src","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\driver\inc","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\hw\inc","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc\src\inc","F:\Git\Sonar\e2Projects\Sonar\r_pdc_rx","F:\Git\Sonar\e2Projects\Sonar\r_config","F:\Git\Sonar\e2Projects\Sonar\r_pincfg" -lang=c99 -nomessage -debug -optimize=0 -nologo  "$<"
	ccrx -isa=rxv2 -fpu -include="C:\Program Files (x86)\Renesas\RX\2_7_0\include","F:\Git\Sonar\e2Projects\Sonar\r_bsp","F:\Git\Sonar\e2Projects\Sonar\src","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\driver\inc","F:\Git\Sonar\e2Projects\Sonar\r_usb_basic\src\hw\inc","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc","F:\Git\Sonar\e2Projects\Sonar\r_usb_pcdc\src\inc","F:\Git\Sonar\e2Projects\Sonar\r_pdc_rx","F:\Git\Sonar\e2Projects\Sonar\r_config","F:\Git\Sonar\e2Projects\Sonar\r_pincfg" -lang=c99 -nomessage -output=obj -obj_path="r_usb_basic/src/driver" -debug -optimize=0 -nologo "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

