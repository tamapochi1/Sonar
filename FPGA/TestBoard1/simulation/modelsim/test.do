transcript on

if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}

vlib  rtl_work

vmap work rtl_work

vlog +define+SIMULATION				\
	-vlog01compat -work work		\
	+incdir+../../../TestBoard1	\
	../../../TestBoard1/TOP.v	\
	../../../TestBoard1/PLL.v	\
	../../../TestBoard1/PWM.v	\
	../../../TestBoard1/simulation/modelsim/test.v

#source ../../../TestBoard1/FIR/simulation/mentor/msim_setup.tcl
source ../../../TestBoard1/CIC/simulation/mentor/msim_setup.tcl

vsim -L altera_mf_ver -c work.test

add wave -hex sim:/test/clk

log -r *

run -all