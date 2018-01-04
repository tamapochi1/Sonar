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
	../../../PhasedArrayController/PowerOnReset.v	\
	../../../PhasedArrayController/PLL.v	\
	../../../PhasedArrayController/SerialSlave.v	\
	../../../PhasedArrayController/simulation/modelsim/test.v

vsim -L altera_mf_ver -c work.test

add wave -hex sim:/test/clk

log -r *

run -all