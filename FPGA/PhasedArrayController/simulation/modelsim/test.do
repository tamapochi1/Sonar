transcript on

if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}

vlib  rtl_work

vmap work rtl_work

vlog +define+SIMULATION				\
	-vlog01compat -work work		\
	+incdir+../../../PhasedArrayController	\
	../../../PhasedArrayController/TOP.v	\
	../../../PhasedArrayController/PhaseShifter.v	\
	../../../PhasedArrayController/simulation/modelsim/test.v

vsim -L -c work.test

add wave -hex sim:/test/clk

log -r *

run -all