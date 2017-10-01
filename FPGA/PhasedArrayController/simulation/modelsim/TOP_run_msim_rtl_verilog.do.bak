transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+F:/Git/Sonar/FPGA/PhasedArrayController {F:/Git/Sonar/FPGA/PhasedArrayController/TOP.v}
vlog -vlog01compat -work work +incdir+F:/Git/Sonar/FPGA/PhasedArrayController {F:/Git/Sonar/FPGA/PhasedArrayController/PhaseShifter.v}
vlog -vlog01compat -work work +incdir+F:/Git/Sonar/FPGA/PhasedArrayController {F:/Git/Sonar/FPGA/PhasedArrayController/PLL.v}
vlog -vlog01compat -work work +incdir+F:/Git/Sonar/FPGA/PhasedArrayController/db {F:/Git/Sonar/FPGA/PhasedArrayController/db/pll_altpll.v}

