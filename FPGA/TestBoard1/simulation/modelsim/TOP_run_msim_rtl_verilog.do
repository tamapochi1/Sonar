transcript on
if ![file isdirectory TOP_iputf_libs] {
	file mkdir TOP_iputf_libs
}

if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

###### Libraries for IPUTF cores 
vlib TOP_iputf_libs/fir_compiler_ii_0
vmap fir_compiler_ii_0 ./TOP_iputf_libs/fir_compiler_ii_0
###### End libraries for IPUTF cores 
###### MIF file copy and HDL compilation commands for IPUTF cores 


vcom "F:/Git/Sonar/FPGA/TestBoard1/FIR/simulation/submodules/dspba_library_package.vhd"                       -work fir_compiler_ii_0
vcom "F:/Git/Sonar/FPGA/TestBoard1/FIR/simulation/submodules/dspba_library.vhd"                               -work fir_compiler_ii_0
vcom "F:/Git/Sonar/FPGA/TestBoard1/FIR/simulation/submodules/auk_dspip_math_pkg_hpfir.vhd"                    -work fir_compiler_ii_0
vcom "F:/Git/Sonar/FPGA/TestBoard1/FIR/simulation/submodules/auk_dspip_lib_pkg_hpfir.vhd"                     -work fir_compiler_ii_0
vcom "F:/Git/Sonar/FPGA/TestBoard1/FIR/simulation/submodules/auk_dspip_avalon_streaming_controller_hpfir.vhd" -work fir_compiler_ii_0
vcom "F:/Git/Sonar/FPGA/TestBoard1/FIR/simulation/submodules/auk_dspip_avalon_streaming_sink_hpfir.vhd"       -work fir_compiler_ii_0
vcom "F:/Git/Sonar/FPGA/TestBoard1/FIR/simulation/submodules/auk_dspip_avalon_streaming_source_hpfir.vhd"     -work fir_compiler_ii_0
vcom "F:/Git/Sonar/FPGA/TestBoard1/FIR/simulation/submodules/auk_dspip_roundsat_hpfir.vhd"                    -work fir_compiler_ii_0
vlog "F:/Git/Sonar/FPGA/TestBoard1/FIR/simulation/submodules/altera_avalon_sc_fifo.v"                         -work fir_compiler_ii_0
vcom "F:/Git/Sonar/FPGA/TestBoard1/FIR/simulation/submodules/FIR_fir_compiler_ii_0_rtl_core.vhd"              -work fir_compiler_ii_0
vcom "F:/Git/Sonar/FPGA/TestBoard1/FIR/simulation/submodules/FIR_fir_compiler_ii_0_ast.vhd"                   -work fir_compiler_ii_0
vcom "F:/Git/Sonar/FPGA/TestBoard1/FIR/simulation/submodules/FIR_fir_compiler_ii_0.vhd"                       -work fir_compiler_ii_0
vcom "F:/Git/Sonar/FPGA/TestBoard1/FIR/simulation/submodules/FIR_fir_compiler_ii_0_tb.vhd"                    -work fir_compiler_ii_0
vlog "F:/Git/Sonar/FPGA/TestBoard1/FIR/simulation/FIR.v"                                                                             

vlog -vlog01compat -work work +incdir+F:/Git/Sonar/FPGA/TestBoard1 {F:/Git/Sonar/FPGA/TestBoard1/TOP.v}
vlog -vlog01compat -work work +incdir+F:/Git/Sonar/FPGA/TestBoard1 {F:/Git/Sonar/FPGA/TestBoard1/PLL.v}
vlog -vlog01compat -work work +incdir+F:/Git/Sonar/FPGA/TestBoard1 {F:/Git/Sonar/FPGA/TestBoard1/PWM.v}
vlog -vlog01compat -work work +incdir+F:/Git/Sonar/FPGA/TestBoard1 {F:/Git/Sonar/FPGA/TestBoard1/CIC.v}
vlog -vlog01compat -work work +incdir+F:/Git/Sonar/FPGA/TestBoard1/db {F:/Git/Sonar/FPGA/TestBoard1/db/pll_altpll.v}

vlog -vlog01compat -work work +incdir+F:/Git/Sonar/FPGA/TestBoard1/simulation/modelsim {F:/Git/Sonar/FPGA/TestBoard1/simulation/modelsim/tb_TestBoard1.v}

vsim -t 1ps -L altera_ver -L lpm_ver -L sgate_ver -L altera_mf_ver -L altera_lnsim_ver -L fiftyfivenm -L fiftyfivenm_ver -L rtl_work -L work -L fir_compiler_ii_0 -voptargs="+acc"  tb_TestBoard1

add wave *
view structure
view signals
log -r *
run 1 ms
