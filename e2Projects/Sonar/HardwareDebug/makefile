################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include makefile.init

RM := rm -rf *.sni *.dbg *.lst *.lis *.lpp *.map *.x *.lbp *.bls *.libelf *.rel *.lbk *.abs  *.obj *.p *.pp *.d *.asm 1st/*.obj 1st/*.d 1st/*.asm 1st/*.abs

# All of the sources participating in the build are defined here
-include sources.mk
-include r_bsp/board/MainBoard/subdir.mk
-include r_usb_pcdc/src/subdir.mk
-include src/cg_src/subdir.mk
-include r_bsp/mcu/all/subdir.mk
-include r_usb_basic/src/hw/subdir.mk
-include src/subdir.mk
-include r_bsp/mcu/rx71m/subdir.mk
-include r_usb_basic/src/driver/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif 
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif 
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif 
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif 
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif 
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif 
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif 
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif 
ifneq ($(strip $(JMP_DEPS)),)
-include $(JMP_DEPS)
endif 
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif 
ifneq ($(strip $(PP_DEPS)),)
-include $(PP_DEPS)
endif 
ifneq ($(strip $(P_DEPS)),)
-include $(P_DEPS)
endif 
ifneq ($(strip $(FSY_DEPS)),)
-include $(FSY_DEPS)
endif 
endif

ifneq ($(strip $(SRC_UPPER_SRCS)),)
ALL_ASMS += $(SRC_UPPER_SRCS) 
endif
ifneq ($(strip $(SRC_SRCS)),)
ALL_ASMS += $(SRC_SRCS) 
endif
ifneq ($(strip $(S_UPPER_SRCS)),)
ALL_ASMS += $(S_UPPER_SRCS) 
endif
ifneq ($(strip $(S_SRCS)),)
ALL_ASMS += $(S_SRCS) 
endif


-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables
LINKER_OUTPUT_OUTPUTS += \
Sonar.abs \
Sonar.x

LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS += \
Sonar.lib

OBJS := \
$(COMPILER_OBJS) \
$(INDIVIDUAL_COMPILER_OBJS) \
$(ASSEMBLER_OBJS) \
$(CUSTOM_OBJS)

# All Target
all: $(LINKER_OUTPUT_OUTPUTS) 
	@echo 'Build complete.'

Sonar.abs: $(OBJS)  $(ALL_ASMS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) 
	@echo 'Invoking: Linker'
	@echo 'Building target:'
	rlink -subcommand="LinkerSubCommand.tmp"  -output="Sonar.abs" -form=absolute -nomessage -vect=_undefined_interrupt_source_isr -list=Sonar.map -nooptimize -rom=D=R,D_1=R_1,D_2=R_2 -nologo
	@echo 'Finished building target:'
	@echo.


Sonar.lib: 
	@echo 'Invoking: Library Generator'
	lbgrx -isa=rxv2 -fpu -lang=c99 -head=runtime,stdio,stdlib,string,new -output="Sonar.lib" -nologo
	@echo 'Finished building:'
	@echo.

Sonar.x: Sonar.abs
		-C:\Renesas\e2_studio\eclipse\/../\Utilities\\ccrx\renesas_cc_converter.exe Sonar.abs Sonar.x

# Other Targets
clean:
	-$(RM) $(LINKER_OUTPUT_OUTPUTS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS)
	-rm -rf r_bsp/board/MainBoard/*.obj r_bsp/board/MainBoard/*.d r_bsp/board/MainBoard/*.asm r_bsp/board/MainBoard/*.p r_bsp/board/MainBoard/*.src r_bsp/board/MainBoard/*.jmp r_bsp/board/MainBoard/*.lst r_bsp/board/MainBoard/*.prn 
	-rm -rf r_usb_pcdc/src/*.obj r_usb_pcdc/src/*.d r_usb_pcdc/src/*.asm r_usb_pcdc/src/*.p r_usb_pcdc/src/*.src r_usb_pcdc/src/*.jmp r_usb_pcdc/src/*.lst r_usb_pcdc/src/*.prn 
	-rm -rf src/cg_src/*.obj src/cg_src/*.d src/cg_src/*.asm src/cg_src/*.p src/cg_src/*.src src/cg_src/*.jmp src/cg_src/*.lst src/cg_src/*.prn 
	-rm -rf r_bsp/mcu/all/*.obj r_bsp/mcu/all/*.d r_bsp/mcu/all/*.asm r_bsp/mcu/all/*.p r_bsp/mcu/all/*.src r_bsp/mcu/all/*.jmp r_bsp/mcu/all/*.lst r_bsp/mcu/all/*.prn 
	-rm -rf r_usb_basic/src/hw/*.obj r_usb_basic/src/hw/*.d r_usb_basic/src/hw/*.asm r_usb_basic/src/hw/*.p r_usb_basic/src/hw/*.src r_usb_basic/src/hw/*.jmp r_usb_basic/src/hw/*.lst r_usb_basic/src/hw/*.prn 
	-rm -rf src/*.obj src/*.d src/*.asm src/*.p src/*.src src/*.jmp src/*.lst src/*.prn 
	-rm -rf r_bsp/mcu/rx71m/*.obj r_bsp/mcu/rx71m/*.d r_bsp/mcu/rx71m/*.asm r_bsp/mcu/rx71m/*.p r_bsp/mcu/rx71m/*.src r_bsp/mcu/rx71m/*.jmp r_bsp/mcu/rx71m/*.lst r_bsp/mcu/rx71m/*.prn 
	-rm -rf r_usb_basic/src/driver/*.obj r_usb_basic/src/driver/*.d r_usb_basic/src/driver/*.asm r_usb_basic/src/driver/*.p r_usb_basic/src/driver/*.src r_usb_basic/src/driver/*.jmp r_usb_basic/src/driver/*.lst r_usb_basic/src/driver/*.prn 
	@echo
	@echo 'Clean complete.'

.PHONY: all clean 
-include ../makefile.targets