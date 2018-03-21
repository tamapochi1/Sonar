-- ------------------------------------------------------------------------- 
-- High Level Design Compiler for Intel(R) FPGAs Version 17.0 (Release Build #595)
-- Quartus Prime development tool and MATLAB/Simulink Interface
-- 
-- Legal Notice: Copyright 2017 Intel Corporation.  All rights reserved.
-- Your use of  Intel Corporation's design tools,  logic functions and other
-- software and  tools, and its AMPP partner logic functions, and any output
-- files any  of the foregoing (including  device programming  or simulation
-- files), and  any associated  documentation  or information  are expressly
-- subject  to the terms and  conditions of the  Intel FPGA Software License
-- Agreement, Intel MegaCore Function License Agreement, or other applicable
-- license agreement,  including,  without limitation,  that your use is for
-- the  sole  purpose of  programming  logic devices  manufactured by  Intel
-- and  sold by Intel  or its authorized  distributors. Please refer  to the
-- applicable agreement for further details.
-- ---------------------------------------------------------------------------

-- VHDL created from MULT_0002
-- VHDL created on Tue Jan 09 14:15:27 2018


library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_STD.all;
use IEEE.MATH_REAL.all;
use std.TextIO.all;
use work.dspba_library_package.all;

LIBRARY altera_mf;
USE altera_mf.altera_mf_components.all;
LIBRARY lpm;
USE lpm.lpm_components.all;

entity MULT_0002 is
    port (
        a : in std_logic_vector(63 downto 0);  -- float64_m52
        b : in std_logic_vector(63 downto 0);  -- float64_m52
        en : in std_logic_vector(0 downto 0);  -- ufix1
        q : out std_logic_vector(63 downto 0);  -- float64_m52
        clk : in std_logic;
        areset : in std_logic
    );
end MULT_0002;

architecture normal of MULT_0002 is

    attribute altera_attribute : string;
    attribute altera_attribute of normal : architecture is "-name AUTO_SHIFT_REGISTER_RECOGNITION OFF; -name PHYSICAL_SYNTHESIS_REGISTER_DUPLICATION ON; -name MESSAGE_DISABLE 10036; -name MESSAGE_DISABLE 10037; -name MESSAGE_DISABLE 14130; -name MESSAGE_DISABLE 14320; -name MESSAGE_DISABLE 15400; -name MESSAGE_DISABLE 14130; -name MESSAGE_DISABLE 10036; -name MESSAGE_DISABLE 12020; -name MESSAGE_DISABLE 12030; -name MESSAGE_DISABLE 12010; -name MESSAGE_DISABLE 12110; -name MESSAGE_DISABLE 14320; -name MESSAGE_DISABLE 13410; -name MESSAGE_DISABLE 113007";
    
    signal GND_q : STD_LOGIC_VECTOR (0 downto 0);
    signal VCC_q : STD_LOGIC_VECTOR (0 downto 0);
    signal expX_uid6_fpMulTest_b : STD_LOGIC_VECTOR (10 downto 0);
    signal expY_uid7_fpMulTest_b : STD_LOGIC_VECTOR (10 downto 0);
    signal signX_uid8_fpMulTest_b : STD_LOGIC_VECTOR (0 downto 0);
    signal signY_uid9_fpMulTest_b : STD_LOGIC_VECTOR (0 downto 0);
    signal cstAllOWE_uid10_fpMulTest_q : STD_LOGIC_VECTOR (10 downto 0);
    signal cstZeroWF_uid11_fpMulTest_q : STD_LOGIC_VECTOR (51 downto 0);
    signal cstAllZWE_uid12_fpMulTest_q : STD_LOGIC_VECTOR (10 downto 0);
    signal frac_x_uid14_fpMulTest_b : STD_LOGIC_VECTOR (51 downto 0);
    signal excZ_x_uid15_fpMulTest_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal excZ_x_uid15_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal expXIsMax_uid16_fpMulTest_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal expXIsMax_uid16_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsZero_uid17_fpMulTest_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsZero_uid17_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsNotZero_uid18_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excI_x_uid19_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excN_x_uid20_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal invExpXIsMax_uid21_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal InvExpXIsZero_uid22_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excR_x_uid23_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal frac_y_uid28_fpMulTest_b : STD_LOGIC_VECTOR (51 downto 0);
    signal excZ_y_uid29_fpMulTest_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal excZ_y_uid29_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal expXIsMax_uid30_fpMulTest_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal expXIsMax_uid30_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsZero_uid31_fpMulTest_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsZero_uid31_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracXIsNotZero_uid32_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excI_y_uid33_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excN_y_uid34_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal invExpXIsMax_uid35_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal InvExpXIsZero_uid36_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excR_y_uid37_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal ofracX_uid40_fpMulTest_q : STD_LOGIC_VECTOR (52 downto 0);
    signal ofracY_uid43_fpMulTest_q : STD_LOGIC_VECTOR (52 downto 0);
    signal expSum_uid44_fpMulTest_a : STD_LOGIC_VECTOR (11 downto 0);
    signal expSum_uid44_fpMulTest_b : STD_LOGIC_VECTOR (11 downto 0);
    signal expSum_uid44_fpMulTest_o : STD_LOGIC_VECTOR (11 downto 0);
    signal expSum_uid44_fpMulTest_q : STD_LOGIC_VECTOR (11 downto 0);
    signal biasInc_uid45_fpMulTest_q : STD_LOGIC_VECTOR (12 downto 0);
    signal expSumMBias_uid46_fpMulTest_a : STD_LOGIC_VECTOR (14 downto 0);
    signal expSumMBias_uid46_fpMulTest_b : STD_LOGIC_VECTOR (14 downto 0);
    signal expSumMBias_uid46_fpMulTest_o : STD_LOGIC_VECTOR (14 downto 0);
    signal expSumMBias_uid46_fpMulTest_q : STD_LOGIC_VECTOR (13 downto 0);
    signal signR_uid48_fpMulTest_qi : STD_LOGIC_VECTOR (0 downto 0);
    signal signR_uid48_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal normalizeBit_uid49_fpMulTest_b : STD_LOGIC_VECTOR (0 downto 0);
    signal fracRPostNormHigh_uid51_fpMulTest_in : STD_LOGIC_VECTOR (104 downto 0);
    signal fracRPostNormHigh_uid51_fpMulTest_b : STD_LOGIC_VECTOR (52 downto 0);
    signal fracRPostNormLow_uid52_fpMulTest_in : STD_LOGIC_VECTOR (103 downto 0);
    signal fracRPostNormLow_uid52_fpMulTest_b : STD_LOGIC_VECTOR (52 downto 0);
    signal fracRPostNorm_uid53_fpMulTest_s : STD_LOGIC_VECTOR (0 downto 0);
    signal fracRPostNorm_uid53_fpMulTest_q : STD_LOGIC_VECTOR (52 downto 0);
    signal stickyRange_uid54_fpMulTest_in : STD_LOGIC_VECTOR (50 downto 0);
    signal stickyRange_uid54_fpMulTest_b : STD_LOGIC_VECTOR (50 downto 0);
    signal extraStickyBitOfProd_uid55_fpMulTest_in : STD_LOGIC_VECTOR (51 downto 0);
    signal extraStickyBitOfProd_uid55_fpMulTest_b : STD_LOGIC_VECTOR (0 downto 0);
    signal extraStickyBit_uid56_fpMulTest_s : STD_LOGIC_VECTOR (0 downto 0);
    signal extraStickyBit_uid56_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal stickyExtendedRange_uid57_fpMulTest_q : STD_LOGIC_VECTOR (51 downto 0);
    signal stickyRangeComparator_uid59_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal sticky_uid60_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal fracRPostNorm1dto0_uid61_fpMulTest_in : STD_LOGIC_VECTOR (1 downto 0);
    signal fracRPostNorm1dto0_uid61_fpMulTest_b : STD_LOGIC_VECTOR (1 downto 0);
    signal lrs_uid62_fpMulTest_q : STD_LOGIC_VECTOR (2 downto 0);
    signal roundBitDetectionConstant_uid63_fpMulTest_q : STD_LOGIC_VECTOR (2 downto 0);
    signal roundBitDetectionPattern_uid64_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal roundBit_uid65_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal expFracPreRound_uid66_fpMulTest_q : STD_LOGIC_VECTOR (66 downto 0);
    signal roundBitAndNormalizationOp_uid68_fpMulTest_q : STD_LOGIC_VECTOR (54 downto 0);
    signal expFracRPostRounding_uid69_fpMulTest_a : STD_LOGIC_VECTOR (68 downto 0);
    signal expFracRPostRounding_uid69_fpMulTest_b : STD_LOGIC_VECTOR (68 downto 0);
    signal expFracRPostRounding_uid69_fpMulTest_o : STD_LOGIC_VECTOR (68 downto 0);
    signal expFracRPostRounding_uid69_fpMulTest_q : STD_LOGIC_VECTOR (67 downto 0);
    signal fracRPreExc_uid70_fpMulTest_in : STD_LOGIC_VECTOR (52 downto 0);
    signal fracRPreExc_uid70_fpMulTest_b : STD_LOGIC_VECTOR (51 downto 0);
    signal expRPreExcExt_uid71_fpMulTest_b : STD_LOGIC_VECTOR (14 downto 0);
    signal expRPreExc_uid72_fpMulTest_in : STD_LOGIC_VECTOR (10 downto 0);
    signal expRPreExc_uid72_fpMulTest_b : STD_LOGIC_VECTOR (10 downto 0);
    signal expUdf_uid73_fpMulTest_a : STD_LOGIC_VECTOR (16 downto 0);
    signal expUdf_uid73_fpMulTest_b : STD_LOGIC_VECTOR (16 downto 0);
    signal expUdf_uid73_fpMulTest_o : STD_LOGIC_VECTOR (16 downto 0);
    signal expUdf_uid73_fpMulTest_n : STD_LOGIC_VECTOR (0 downto 0);
    signal expOvf_uid75_fpMulTest_a : STD_LOGIC_VECTOR (16 downto 0);
    signal expOvf_uid75_fpMulTest_b : STD_LOGIC_VECTOR (16 downto 0);
    signal expOvf_uid75_fpMulTest_o : STD_LOGIC_VECTOR (16 downto 0);
    signal expOvf_uid75_fpMulTest_n : STD_LOGIC_VECTOR (0 downto 0);
    signal excXZAndExcYZ_uid76_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excXZAndExcYR_uid77_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excYZAndExcXR_uid78_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excZC3_uid79_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excRZero_uid80_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excXIAndExcYI_uid81_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excXRAndExcYI_uid82_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excYRAndExcXI_uid83_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal ExcROvfAndInReg_uid84_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excRInf_uid85_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excYZAndExcXI_uid86_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excXZAndExcYI_uid87_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal ZeroTimesInf_uid88_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal excRNaN_uid89_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal concExc_uid90_fpMulTest_q : STD_LOGIC_VECTOR (2 downto 0);
    signal excREnc_uid91_fpMulTest_q : STD_LOGIC_VECTOR (1 downto 0);
    signal oneFracRPostExc2_uid92_fpMulTest_q : STD_LOGIC_VECTOR (51 downto 0);
    signal fracRPostExc_uid95_fpMulTest_s : STD_LOGIC_VECTOR (1 downto 0);
    signal fracRPostExc_uid95_fpMulTest_q : STD_LOGIC_VECTOR (51 downto 0);
    signal expRPostExc_uid100_fpMulTest_s : STD_LOGIC_VECTOR (1 downto 0);
    signal expRPostExc_uid100_fpMulTest_q : STD_LOGIC_VECTOR (10 downto 0);
    signal invExcRNaN_uid101_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal signRPostExc_uid102_fpMulTest_q : STD_LOGIC_VECTOR (0 downto 0);
    signal R_uid103_fpMulTest_q : STD_LOGIC_VECTOR (63 downto 0);
    signal osig_uid106_prod_uid47_fpMulTest_in : STD_LOGIC_VECTOR (105 downto 0);
    signal osig_uid106_prod_uid47_fpMulTest_b : STD_LOGIC_VECTOR (105 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im0_a0 : STD_LOGIC_VECTOR (17 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im0_b0 : STD_LOGIC_VECTOR (17 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im0_s1 : STD_LOGIC_VECTOR (35 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im0_reset : std_logic;
    signal prodXY_uid105_prod_uid47_fpMulTest_im0_q : STD_LOGIC_VECTOR (35 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im3_a0 : STD_LOGIC_VECTOR (17 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im3_b0 : STD_LOGIC_VECTOR (16 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im3_s1 : STD_LOGIC_VECTOR (34 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im3_reset : std_logic;
    signal prodXY_uid105_prod_uid47_fpMulTest_im3_q : STD_LOGIC_VECTOR (34 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im6_a0 : STD_LOGIC_VECTOR (17 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im6_b0 : STD_LOGIC_VECTOR (16 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im6_s1 : STD_LOGIC_VECTOR (34 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im6_reset : std_logic;
    signal prodXY_uid105_prod_uid47_fpMulTest_im6_q : STD_LOGIC_VECTOR (34 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im9_a0 : STD_LOGIC_VECTOR (17 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im9_b0 : STD_LOGIC_VECTOR (17 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im9_s1 : STD_LOGIC_VECTOR (35 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im9_reset : std_logic;
    signal prodXY_uid105_prod_uid47_fpMulTest_im9_q : STD_LOGIC_VECTOR (35 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im12_a0 : STD_LOGIC_VECTOR (17 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im12_b0 : STD_LOGIC_VECTOR (17 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im12_s1 : STD_LOGIC_VECTOR (35 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im12_reset : std_logic;
    signal prodXY_uid105_prod_uid47_fpMulTest_im12_q : STD_LOGIC_VECTOR (35 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im15_a0 : STD_LOGIC_VECTOR (16 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im15_b0 : STD_LOGIC_VECTOR (16 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im15_s1 : STD_LOGIC_VECTOR (33 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im15_reset : std_logic;
    signal prodXY_uid105_prod_uid47_fpMulTest_im15_q : STD_LOGIC_VECTOR (33 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im18_a0 : STD_LOGIC_VECTOR (17 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im18_b0 : STD_LOGIC_VECTOR (17 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im18_s1 : STD_LOGIC_VECTOR (35 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im18_reset : std_logic;
    signal prodXY_uid105_prod_uid47_fpMulTest_im18_q : STD_LOGIC_VECTOR (35 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im21_a0 : STD_LOGIC_VECTOR (17 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im21_b0 : STD_LOGIC_VECTOR (16 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im21_s1 : STD_LOGIC_VECTOR (34 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im21_reset : std_logic;
    signal prodXY_uid105_prod_uid47_fpMulTest_im21_q : STD_LOGIC_VECTOR (34 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im24_a0 : STD_LOGIC_VECTOR (17 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im24_b0 : STD_LOGIC_VECTOR (16 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im24_s1 : STD_LOGIC_VECTOR (34 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_im24_reset : std_logic;
    signal prodXY_uid105_prod_uid47_fpMulTest_im24_q : STD_LOGIC_VECTOR (34 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_join_27_q : STD_LOGIC_VECTOR (105 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_align_28_q : STD_LOGIC_VECTOR (53 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_align_28_qint : STD_LOGIC_VECTOR (53 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_join_29_q : STD_LOGIC_VECTOR (88 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_align_30_q : STD_LOGIC_VECTOR (53 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_align_30_qint : STD_LOGIC_VECTOR (53 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_join_31_q : STD_LOGIC_VECTOR (88 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_align_32_q : STD_LOGIC_VECTOR (70 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_align_32_qint : STD_LOGIC_VECTOR (70 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_align_34_q : STD_LOGIC_VECTOR (70 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_align_34_qint : STD_LOGIC_VECTOR (70 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_result_add_0_0_a : STD_LOGIC_VECTOR (106 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_result_add_0_0_b : STD_LOGIC_VECTOR (106 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_result_add_0_0_o : STD_LOGIC_VECTOR (106 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_result_add_0_0_q : STD_LOGIC_VECTOR (106 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_result_add_0_1_a : STD_LOGIC_VECTOR (89 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_result_add_0_1_b : STD_LOGIC_VECTOR (89 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_result_add_0_1_o : STD_LOGIC_VECTOR (89 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_result_add_0_1_q : STD_LOGIC_VECTOR (89 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_result_add_1_0_a : STD_LOGIC_VECTOR (107 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_result_add_1_0_b : STD_LOGIC_VECTOR (107 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_result_add_1_0_o : STD_LOGIC_VECTOR (107 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_result_add_1_0_q : STD_LOGIC_VECTOR (107 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_result_add_2_0_a : STD_LOGIC_VECTOR (108 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_result_add_2_0_b : STD_LOGIC_VECTOR (108 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_result_add_2_0_o : STD_LOGIC_VECTOR (108 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_result_add_2_0_q : STD_LOGIC_VECTOR (108 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_bs1_merged_bit_select_b : STD_LOGIC_VECTOR (17 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_bs1_merged_bit_select_c : STD_LOGIC_VECTOR (17 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_bs1_merged_bit_select_d : STD_LOGIC_VECTOR (16 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_bs2_merged_bit_select_b : STD_LOGIC_VECTOR (17 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_bs2_merged_bit_select_c : STD_LOGIC_VECTOR (16 downto 0);
    signal prodXY_uid105_prod_uid47_fpMulTest_bs2_merged_bit_select_d : STD_LOGIC_VECTOR (17 downto 0);
    signal redist0_signR_uid48_fpMulTest_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist1_expSum_uid44_fpMulTest_q_2_q : STD_LOGIC_VECTOR (11 downto 0);
    signal redist2_fracXIsZero_uid31_fpMulTest_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist3_expXIsMax_uid30_fpMulTest_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist4_excZ_y_uid29_fpMulTest_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist5_fracXIsZero_uid17_fpMulTest_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist6_expXIsMax_uid16_fpMulTest_q_2_q : STD_LOGIC_VECTOR (0 downto 0);
    signal redist7_excZ_x_uid15_fpMulTest_q_2_q : STD_LOGIC_VECTOR (0 downto 0);

begin


    -- frac_x_uid14_fpMulTest(BITSELECT,13)@0
    frac_x_uid14_fpMulTest_b <= a(51 downto 0);

    -- cstZeroWF_uid11_fpMulTest(CONSTANT,10)
    cstZeroWF_uid11_fpMulTest_q <= "0000000000000000000000000000000000000000000000000000";

    -- fracXIsZero_uid17_fpMulTest(LOGICAL,16)@0 + 1
    fracXIsZero_uid17_fpMulTest_qi <= "1" WHEN cstZeroWF_uid11_fpMulTest_q = frac_x_uid14_fpMulTest_b ELSE "0";
    fracXIsZero_uid17_fpMulTest_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "ASYNC" )
    PORT MAP ( xin => fracXIsZero_uid17_fpMulTest_qi, xout => fracXIsZero_uid17_fpMulTest_q, ena => en(0), clk => clk, aclr => areset );

    -- redist5_fracXIsZero_uid17_fpMulTest_q_2(DELAY,154)
    redist5_fracXIsZero_uid17_fpMulTest_q_2 : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "ASYNC" )
    PORT MAP ( xin => fracXIsZero_uid17_fpMulTest_q, xout => redist5_fracXIsZero_uid17_fpMulTest_q_2_q, ena => en(0), clk => clk, aclr => areset );

    -- cstAllOWE_uid10_fpMulTest(CONSTANT,9)
    cstAllOWE_uid10_fpMulTest_q <= "11111111111";

    -- expX_uid6_fpMulTest(BITSELECT,5)@0
    expX_uid6_fpMulTest_b <= a(62 downto 52);

    -- expXIsMax_uid16_fpMulTest(LOGICAL,15)@0 + 1
    expXIsMax_uid16_fpMulTest_qi <= "1" WHEN expX_uid6_fpMulTest_b = cstAllOWE_uid10_fpMulTest_q ELSE "0";
    expXIsMax_uid16_fpMulTest_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "ASYNC" )
    PORT MAP ( xin => expXIsMax_uid16_fpMulTest_qi, xout => expXIsMax_uid16_fpMulTest_q, ena => en(0), clk => clk, aclr => areset );

    -- redist6_expXIsMax_uid16_fpMulTest_q_2(DELAY,155)
    redist6_expXIsMax_uid16_fpMulTest_q_2 : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "ASYNC" )
    PORT MAP ( xin => expXIsMax_uid16_fpMulTest_q, xout => redist6_expXIsMax_uid16_fpMulTest_q_2_q, ena => en(0), clk => clk, aclr => areset );

    -- excI_x_uid19_fpMulTest(LOGICAL,18)@2
    excI_x_uid19_fpMulTest_q <= redist6_expXIsMax_uid16_fpMulTest_q_2_q and redist5_fracXIsZero_uid17_fpMulTest_q_2_q;

    -- cstAllZWE_uid12_fpMulTest(CONSTANT,11)
    cstAllZWE_uid12_fpMulTest_q <= "00000000000";

    -- expY_uid7_fpMulTest(BITSELECT,6)@0
    expY_uid7_fpMulTest_b <= b(62 downto 52);

    -- excZ_y_uid29_fpMulTest(LOGICAL,28)@0 + 1
    excZ_y_uid29_fpMulTest_qi <= "1" WHEN expY_uid7_fpMulTest_b = cstAllZWE_uid12_fpMulTest_q ELSE "0";
    excZ_y_uid29_fpMulTest_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "ASYNC" )
    PORT MAP ( xin => excZ_y_uid29_fpMulTest_qi, xout => excZ_y_uid29_fpMulTest_q, ena => en(0), clk => clk, aclr => areset );

    -- redist4_excZ_y_uid29_fpMulTest_q_2(DELAY,153)
    redist4_excZ_y_uid29_fpMulTest_q_2 : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "ASYNC" )
    PORT MAP ( xin => excZ_y_uid29_fpMulTest_q, xout => redist4_excZ_y_uid29_fpMulTest_q_2_q, ena => en(0), clk => clk, aclr => areset );

    -- excYZAndExcXI_uid86_fpMulTest(LOGICAL,85)@2
    excYZAndExcXI_uid86_fpMulTest_q <= redist4_excZ_y_uid29_fpMulTest_q_2_q and excI_x_uid19_fpMulTest_q;

    -- frac_y_uid28_fpMulTest(BITSELECT,27)@0
    frac_y_uid28_fpMulTest_b <= b(51 downto 0);

    -- fracXIsZero_uid31_fpMulTest(LOGICAL,30)@0 + 1
    fracXIsZero_uid31_fpMulTest_qi <= "1" WHEN cstZeroWF_uid11_fpMulTest_q = frac_y_uid28_fpMulTest_b ELSE "0";
    fracXIsZero_uid31_fpMulTest_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "ASYNC" )
    PORT MAP ( xin => fracXIsZero_uid31_fpMulTest_qi, xout => fracXIsZero_uid31_fpMulTest_q, ena => en(0), clk => clk, aclr => areset );

    -- redist2_fracXIsZero_uid31_fpMulTest_q_2(DELAY,151)
    redist2_fracXIsZero_uid31_fpMulTest_q_2 : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "ASYNC" )
    PORT MAP ( xin => fracXIsZero_uid31_fpMulTest_q, xout => redist2_fracXIsZero_uid31_fpMulTest_q_2_q, ena => en(0), clk => clk, aclr => areset );

    -- expXIsMax_uid30_fpMulTest(LOGICAL,29)@0 + 1
    expXIsMax_uid30_fpMulTest_qi <= "1" WHEN expY_uid7_fpMulTest_b = cstAllOWE_uid10_fpMulTest_q ELSE "0";
    expXIsMax_uid30_fpMulTest_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "ASYNC" )
    PORT MAP ( xin => expXIsMax_uid30_fpMulTest_qi, xout => expXIsMax_uid30_fpMulTest_q, ena => en(0), clk => clk, aclr => areset );

    -- redist3_expXIsMax_uid30_fpMulTest_q_2(DELAY,152)
    redist3_expXIsMax_uid30_fpMulTest_q_2 : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "ASYNC" )
    PORT MAP ( xin => expXIsMax_uid30_fpMulTest_q, xout => redist3_expXIsMax_uid30_fpMulTest_q_2_q, ena => en(0), clk => clk, aclr => areset );

    -- excI_y_uid33_fpMulTest(LOGICAL,32)@2
    excI_y_uid33_fpMulTest_q <= redist3_expXIsMax_uid30_fpMulTest_q_2_q and redist2_fracXIsZero_uid31_fpMulTest_q_2_q;

    -- excZ_x_uid15_fpMulTest(LOGICAL,14)@0 + 1
    excZ_x_uid15_fpMulTest_qi <= "1" WHEN expX_uid6_fpMulTest_b = cstAllZWE_uid12_fpMulTest_q ELSE "0";
    excZ_x_uid15_fpMulTest_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "ASYNC" )
    PORT MAP ( xin => excZ_x_uid15_fpMulTest_qi, xout => excZ_x_uid15_fpMulTest_q, ena => en(0), clk => clk, aclr => areset );

    -- redist7_excZ_x_uid15_fpMulTest_q_2(DELAY,156)
    redist7_excZ_x_uid15_fpMulTest_q_2 : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "ASYNC" )
    PORT MAP ( xin => excZ_x_uid15_fpMulTest_q, xout => redist7_excZ_x_uid15_fpMulTest_q_2_q, ena => en(0), clk => clk, aclr => areset );

    -- excXZAndExcYI_uid87_fpMulTest(LOGICAL,86)@2
    excXZAndExcYI_uid87_fpMulTest_q <= redist7_excZ_x_uid15_fpMulTest_q_2_q and excI_y_uid33_fpMulTest_q;

    -- ZeroTimesInf_uid88_fpMulTest(LOGICAL,87)@2
    ZeroTimesInf_uid88_fpMulTest_q <= excXZAndExcYI_uid87_fpMulTest_q or excYZAndExcXI_uid86_fpMulTest_q;

    -- fracXIsNotZero_uid32_fpMulTest(LOGICAL,31)@2
    fracXIsNotZero_uid32_fpMulTest_q <= not (redist2_fracXIsZero_uid31_fpMulTest_q_2_q);

    -- excN_y_uid34_fpMulTest(LOGICAL,33)@2
    excN_y_uid34_fpMulTest_q <= redist3_expXIsMax_uid30_fpMulTest_q_2_q and fracXIsNotZero_uid32_fpMulTest_q;

    -- fracXIsNotZero_uid18_fpMulTest(LOGICAL,17)@2
    fracXIsNotZero_uid18_fpMulTest_q <= not (redist5_fracXIsZero_uid17_fpMulTest_q_2_q);

    -- excN_x_uid20_fpMulTest(LOGICAL,19)@2
    excN_x_uid20_fpMulTest_q <= redist6_expXIsMax_uid16_fpMulTest_q_2_q and fracXIsNotZero_uid18_fpMulTest_q;

    -- excRNaN_uid89_fpMulTest(LOGICAL,88)@2
    excRNaN_uid89_fpMulTest_q <= excN_x_uid20_fpMulTest_q or excN_y_uid34_fpMulTest_q or ZeroTimesInf_uid88_fpMulTest_q;

    -- invExcRNaN_uid101_fpMulTest(LOGICAL,100)@2
    invExcRNaN_uid101_fpMulTest_q <= not (excRNaN_uid89_fpMulTest_q);

    -- signY_uid9_fpMulTest(BITSELECT,8)@0
    signY_uid9_fpMulTest_b <= STD_LOGIC_VECTOR(b(63 downto 63));

    -- signX_uid8_fpMulTest(BITSELECT,7)@0
    signX_uid8_fpMulTest_b <= STD_LOGIC_VECTOR(a(63 downto 63));

    -- signR_uid48_fpMulTest(LOGICAL,47)@0 + 1
    signR_uid48_fpMulTest_qi <= signX_uid8_fpMulTest_b xor signY_uid9_fpMulTest_b;
    signR_uid48_fpMulTest_delay : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "ASYNC" )
    PORT MAP ( xin => signR_uid48_fpMulTest_qi, xout => signR_uid48_fpMulTest_q, ena => en(0), clk => clk, aclr => areset );

    -- redist0_signR_uid48_fpMulTest_q_2(DELAY,149)
    redist0_signR_uid48_fpMulTest_q_2 : dspba_delay
    GENERIC MAP ( width => 1, depth => 1, reset_kind => "ASYNC" )
    PORT MAP ( xin => signR_uid48_fpMulTest_q, xout => redist0_signR_uid48_fpMulTest_q_2_q, ena => en(0), clk => clk, aclr => areset );

    -- signRPostExc_uid102_fpMulTest(LOGICAL,101)@2
    signRPostExc_uid102_fpMulTest_q <= redist0_signR_uid48_fpMulTest_q_2_q and invExcRNaN_uid101_fpMulTest_q;

    -- GND(CONSTANT,0)
    GND_q <= "0";

    -- VCC(CONSTANT,1)
    VCC_q <= "1";

    -- ofracX_uid40_fpMulTest(BITJOIN,39)@0
    ofracX_uid40_fpMulTest_q <= VCC_q & frac_x_uid14_fpMulTest_b;

    -- prodXY_uid105_prod_uid47_fpMulTest_bs1_merged_bit_select(BITSELECT,147)@0
    prodXY_uid105_prod_uid47_fpMulTest_bs1_merged_bit_select_b <= ofracX_uid40_fpMulTest_q(17 downto 0);
    prodXY_uid105_prod_uid47_fpMulTest_bs1_merged_bit_select_c <= ofracX_uid40_fpMulTest_q(35 downto 18);
    prodXY_uid105_prod_uid47_fpMulTest_bs1_merged_bit_select_d <= ofracX_uid40_fpMulTest_q(52 downto 36);

    -- ofracY_uid43_fpMulTest(BITJOIN,42)@0
    ofracY_uid43_fpMulTest_q <= VCC_q & frac_y_uid28_fpMulTest_b;

    -- prodXY_uid105_prod_uid47_fpMulTest_bs2_merged_bit_select(BITSELECT,148)@0
    prodXY_uid105_prod_uid47_fpMulTest_bs2_merged_bit_select_b <= ofracY_uid43_fpMulTest_q(17 downto 0);
    prodXY_uid105_prod_uid47_fpMulTest_bs2_merged_bit_select_c <= ofracY_uid43_fpMulTest_q(52 downto 36);
    prodXY_uid105_prod_uid47_fpMulTest_bs2_merged_bit_select_d <= ofracY_uid43_fpMulTest_q(35 downto 18);

    -- prodXY_uid105_prod_uid47_fpMulTest_im24(MULT,131)@0 + 2
    prodXY_uid105_prod_uid47_fpMulTest_im24_a0 <= prodXY_uid105_prod_uid47_fpMulTest_bs2_merged_bit_select_b;
    prodXY_uid105_prod_uid47_fpMulTest_im24_b0 <= prodXY_uid105_prod_uid47_fpMulTest_bs1_merged_bit_select_d;
    prodXY_uid105_prod_uid47_fpMulTest_im24_reset <= areset;
    prodXY_uid105_prod_uid47_fpMulTest_im24_component : lpm_mult
    GENERIC MAP (
        lpm_widtha => 18,
        lpm_widthb => 17,
        lpm_widthp => 35,
        lpm_widths => 1,
        lpm_type => "LPM_MULT",
        lpm_representation => "UNSIGNED",
        lpm_hint => "DEDICATED_MULTIPLIER_CIRCUITRY=YES, MAXIMIZE_SPEED=5",
        lpm_pipeline => 2
    )
    PORT MAP (
        dataa => prodXY_uid105_prod_uid47_fpMulTest_im24_a0,
        datab => prodXY_uid105_prod_uid47_fpMulTest_im24_b0,
        clken => en(0),
        aclr => prodXY_uid105_prod_uid47_fpMulTest_im24_reset,
        clock => clk,
        result => prodXY_uid105_prod_uid47_fpMulTest_im24_s1
    );
    prodXY_uid105_prod_uid47_fpMulTest_im24_q <= prodXY_uid105_prod_uid47_fpMulTest_im24_s1;

    -- prodXY_uid105_prod_uid47_fpMulTest_align_34(BITSHIFT,141)@2
    prodXY_uid105_prod_uid47_fpMulTest_align_34_qint <= prodXY_uid105_prod_uid47_fpMulTest_im24_q & "000000000000000000000000000000000000";
    prodXY_uid105_prod_uid47_fpMulTest_align_34_q <= prodXY_uid105_prod_uid47_fpMulTest_align_34_qint(70 downto 0);

    -- prodXY_uid105_prod_uid47_fpMulTest_im21(MULT,128)@0 + 2
    prodXY_uid105_prod_uid47_fpMulTest_im21_a0 <= prodXY_uid105_prod_uid47_fpMulTest_bs1_merged_bit_select_b;
    prodXY_uid105_prod_uid47_fpMulTest_im21_b0 <= prodXY_uid105_prod_uid47_fpMulTest_bs2_merged_bit_select_c;
    prodXY_uid105_prod_uid47_fpMulTest_im21_reset <= areset;
    prodXY_uid105_prod_uid47_fpMulTest_im21_component : lpm_mult
    GENERIC MAP (
        lpm_widtha => 18,
        lpm_widthb => 17,
        lpm_widthp => 35,
        lpm_widths => 1,
        lpm_type => "LPM_MULT",
        lpm_representation => "UNSIGNED",
        lpm_hint => "DEDICATED_MULTIPLIER_CIRCUITRY=YES, MAXIMIZE_SPEED=5",
        lpm_pipeline => 2
    )
    PORT MAP (
        dataa => prodXY_uid105_prod_uid47_fpMulTest_im21_a0,
        datab => prodXY_uid105_prod_uid47_fpMulTest_im21_b0,
        clken => en(0),
        aclr => prodXY_uid105_prod_uid47_fpMulTest_im21_reset,
        clock => clk,
        result => prodXY_uid105_prod_uid47_fpMulTest_im21_s1
    );
    prodXY_uid105_prod_uid47_fpMulTest_im21_q <= prodXY_uid105_prod_uid47_fpMulTest_im21_s1;

    -- prodXY_uid105_prod_uid47_fpMulTest_align_32(BITSHIFT,139)@2
    prodXY_uid105_prod_uid47_fpMulTest_align_32_qint <= prodXY_uid105_prod_uid47_fpMulTest_im21_q & "000000000000000000000000000000000000";
    prodXY_uid105_prod_uid47_fpMulTest_align_32_q <= prodXY_uid105_prod_uid47_fpMulTest_align_32_qint(70 downto 0);

    -- prodXY_uid105_prod_uid47_fpMulTest_im6(MULT,113)@0 + 2
    prodXY_uid105_prod_uid47_fpMulTest_im6_a0 <= prodXY_uid105_prod_uid47_fpMulTest_bs2_merged_bit_select_d;
    prodXY_uid105_prod_uid47_fpMulTest_im6_b0 <= prodXY_uid105_prod_uid47_fpMulTest_bs1_merged_bit_select_d;
    prodXY_uid105_prod_uid47_fpMulTest_im6_reset <= areset;
    prodXY_uid105_prod_uid47_fpMulTest_im6_component : lpm_mult
    GENERIC MAP (
        lpm_widtha => 18,
        lpm_widthb => 17,
        lpm_widthp => 35,
        lpm_widths => 1,
        lpm_type => "LPM_MULT",
        lpm_representation => "UNSIGNED",
        lpm_hint => "DEDICATED_MULTIPLIER_CIRCUITRY=YES, MAXIMIZE_SPEED=5",
        lpm_pipeline => 2
    )
    PORT MAP (
        dataa => prodXY_uid105_prod_uid47_fpMulTest_im6_a0,
        datab => prodXY_uid105_prod_uid47_fpMulTest_im6_b0,
        clken => en(0),
        aclr => prodXY_uid105_prod_uid47_fpMulTest_im6_reset,
        clock => clk,
        result => prodXY_uid105_prod_uid47_fpMulTest_im6_s1
    );
    prodXY_uid105_prod_uid47_fpMulTest_im6_q <= prodXY_uid105_prod_uid47_fpMulTest_im6_s1;

    -- prodXY_uid105_prod_uid47_fpMulTest_im12(MULT,119)@0 + 2
    prodXY_uid105_prod_uid47_fpMulTest_im12_a0 <= prodXY_uid105_prod_uid47_fpMulTest_bs1_merged_bit_select_c;
    prodXY_uid105_prod_uid47_fpMulTest_im12_b0 <= prodXY_uid105_prod_uid47_fpMulTest_bs2_merged_bit_select_b;
    prodXY_uid105_prod_uid47_fpMulTest_im12_reset <= areset;
    prodXY_uid105_prod_uid47_fpMulTest_im12_component : lpm_mult
    GENERIC MAP (
        lpm_widtha => 18,
        lpm_widthb => 18,
        lpm_widthp => 36,
        lpm_widths => 1,
        lpm_type => "LPM_MULT",
        lpm_representation => "UNSIGNED",
        lpm_hint => "DEDICATED_MULTIPLIER_CIRCUITRY=YES, MAXIMIZE_SPEED=5",
        lpm_pipeline => 2
    )
    PORT MAP (
        dataa => prodXY_uid105_prod_uid47_fpMulTest_im12_a0,
        datab => prodXY_uid105_prod_uid47_fpMulTest_im12_b0,
        clken => en(0),
        aclr => prodXY_uid105_prod_uid47_fpMulTest_im12_reset,
        clock => clk,
        result => prodXY_uid105_prod_uid47_fpMulTest_im12_s1
    );
    prodXY_uid105_prod_uid47_fpMulTest_im12_q <= prodXY_uid105_prod_uid47_fpMulTest_im12_s1;

    -- prodXY_uid105_prod_uid47_fpMulTest_align_30(BITSHIFT,137)@2
    prodXY_uid105_prod_uid47_fpMulTest_align_30_qint <= prodXY_uid105_prod_uid47_fpMulTest_im12_q & "000000000000000000";
    prodXY_uid105_prod_uid47_fpMulTest_align_30_q <= prodXY_uid105_prod_uid47_fpMulTest_align_30_qint(53 downto 0);

    -- prodXY_uid105_prod_uid47_fpMulTest_join_31(BITJOIN,138)@2
    prodXY_uid105_prod_uid47_fpMulTest_join_31_q <= prodXY_uid105_prod_uid47_fpMulTest_im6_q & prodXY_uid105_prod_uid47_fpMulTest_align_30_q;

    -- prodXY_uid105_prod_uid47_fpMulTest_result_add_0_1(ADD,144)@2
    prodXY_uid105_prod_uid47_fpMulTest_result_add_0_1_a <= STD_LOGIC_VECTOR("0" & prodXY_uid105_prod_uid47_fpMulTest_join_31_q);
    prodXY_uid105_prod_uid47_fpMulTest_result_add_0_1_b <= STD_LOGIC_VECTOR("0000000000000000000" & prodXY_uid105_prod_uid47_fpMulTest_align_32_q);
    prodXY_uid105_prod_uid47_fpMulTest_result_add_0_1_o <= STD_LOGIC_VECTOR(UNSIGNED(prodXY_uid105_prod_uid47_fpMulTest_result_add_0_1_a) + UNSIGNED(prodXY_uid105_prod_uid47_fpMulTest_result_add_0_1_b));
    prodXY_uid105_prod_uid47_fpMulTest_result_add_0_1_q <= prodXY_uid105_prod_uid47_fpMulTest_result_add_0_1_o(89 downto 0);

    -- prodXY_uid105_prod_uid47_fpMulTest_im3(MULT,110)@0 + 2
    prodXY_uid105_prod_uid47_fpMulTest_im3_a0 <= prodXY_uid105_prod_uid47_fpMulTest_bs1_merged_bit_select_c;
    prodXY_uid105_prod_uid47_fpMulTest_im3_b0 <= prodXY_uid105_prod_uid47_fpMulTest_bs2_merged_bit_select_c;
    prodXY_uid105_prod_uid47_fpMulTest_im3_reset <= areset;
    prodXY_uid105_prod_uid47_fpMulTest_im3_component : lpm_mult
    GENERIC MAP (
        lpm_widtha => 18,
        lpm_widthb => 17,
        lpm_widthp => 35,
        lpm_widths => 1,
        lpm_type => "LPM_MULT",
        lpm_representation => "UNSIGNED",
        lpm_hint => "DEDICATED_MULTIPLIER_CIRCUITRY=YES, MAXIMIZE_SPEED=5",
        lpm_pipeline => 2
    )
    PORT MAP (
        dataa => prodXY_uid105_prod_uid47_fpMulTest_im3_a0,
        datab => prodXY_uid105_prod_uid47_fpMulTest_im3_b0,
        clken => en(0),
        aclr => prodXY_uid105_prod_uid47_fpMulTest_im3_reset,
        clock => clk,
        result => prodXY_uid105_prod_uid47_fpMulTest_im3_s1
    );
    prodXY_uid105_prod_uid47_fpMulTest_im3_q <= prodXY_uid105_prod_uid47_fpMulTest_im3_s1;

    -- prodXY_uid105_prod_uid47_fpMulTest_im9(MULT,116)@0 + 2
    prodXY_uid105_prod_uid47_fpMulTest_im9_a0 <= prodXY_uid105_prod_uid47_fpMulTest_bs1_merged_bit_select_b;
    prodXY_uid105_prod_uid47_fpMulTest_im9_b0 <= prodXY_uid105_prod_uid47_fpMulTest_bs2_merged_bit_select_d;
    prodXY_uid105_prod_uid47_fpMulTest_im9_reset <= areset;
    prodXY_uid105_prod_uid47_fpMulTest_im9_component : lpm_mult
    GENERIC MAP (
        lpm_widtha => 18,
        lpm_widthb => 18,
        lpm_widthp => 36,
        lpm_widths => 1,
        lpm_type => "LPM_MULT",
        lpm_representation => "UNSIGNED",
        lpm_hint => "DEDICATED_MULTIPLIER_CIRCUITRY=YES, MAXIMIZE_SPEED=5",
        lpm_pipeline => 2
    )
    PORT MAP (
        dataa => prodXY_uid105_prod_uid47_fpMulTest_im9_a0,
        datab => prodXY_uid105_prod_uid47_fpMulTest_im9_b0,
        clken => en(0),
        aclr => prodXY_uid105_prod_uid47_fpMulTest_im9_reset,
        clock => clk,
        result => prodXY_uid105_prod_uid47_fpMulTest_im9_s1
    );
    prodXY_uid105_prod_uid47_fpMulTest_im9_q <= prodXY_uid105_prod_uid47_fpMulTest_im9_s1;

    -- prodXY_uid105_prod_uid47_fpMulTest_align_28(BITSHIFT,135)@2
    prodXY_uid105_prod_uid47_fpMulTest_align_28_qint <= prodXY_uid105_prod_uid47_fpMulTest_im9_q & "000000000000000000";
    prodXY_uid105_prod_uid47_fpMulTest_align_28_q <= prodXY_uid105_prod_uid47_fpMulTest_align_28_qint(53 downto 0);

    -- prodXY_uid105_prod_uid47_fpMulTest_join_29(BITJOIN,136)@2
    prodXY_uid105_prod_uid47_fpMulTest_join_29_q <= prodXY_uid105_prod_uid47_fpMulTest_im3_q & prodXY_uid105_prod_uid47_fpMulTest_align_28_q;

    -- prodXY_uid105_prod_uid47_fpMulTest_im15(MULT,122)@0 + 2
    prodXY_uid105_prod_uid47_fpMulTest_im15_a0 <= prodXY_uid105_prod_uid47_fpMulTest_bs1_merged_bit_select_d;
    prodXY_uid105_prod_uid47_fpMulTest_im15_b0 <= prodXY_uid105_prod_uid47_fpMulTest_bs2_merged_bit_select_c;
    prodXY_uid105_prod_uid47_fpMulTest_im15_reset <= areset;
    prodXY_uid105_prod_uid47_fpMulTest_im15_component : lpm_mult
    GENERIC MAP (
        lpm_widtha => 17,
        lpm_widthb => 17,
        lpm_widthp => 34,
        lpm_widths => 1,
        lpm_type => "LPM_MULT",
        lpm_representation => "UNSIGNED",
        lpm_hint => "DEDICATED_MULTIPLIER_CIRCUITRY=YES, MAXIMIZE_SPEED=5",
        lpm_pipeline => 2
    )
    PORT MAP (
        dataa => prodXY_uid105_prod_uid47_fpMulTest_im15_a0,
        datab => prodXY_uid105_prod_uid47_fpMulTest_im15_b0,
        clken => en(0),
        aclr => prodXY_uid105_prod_uid47_fpMulTest_im15_reset,
        clock => clk,
        result => prodXY_uid105_prod_uid47_fpMulTest_im15_s1
    );
    prodXY_uid105_prod_uid47_fpMulTest_im15_q <= prodXY_uid105_prod_uid47_fpMulTest_im15_s1;

    -- prodXY_uid105_prod_uid47_fpMulTest_im18(MULT,125)@0 + 2
    prodXY_uid105_prod_uid47_fpMulTest_im18_a0 <= prodXY_uid105_prod_uid47_fpMulTest_bs1_merged_bit_select_c;
    prodXY_uid105_prod_uid47_fpMulTest_im18_b0 <= prodXY_uid105_prod_uid47_fpMulTest_bs2_merged_bit_select_d;
    prodXY_uid105_prod_uid47_fpMulTest_im18_reset <= areset;
    prodXY_uid105_prod_uid47_fpMulTest_im18_component : lpm_mult
    GENERIC MAP (
        lpm_widtha => 18,
        lpm_widthb => 18,
        lpm_widthp => 36,
        lpm_widths => 1,
        lpm_type => "LPM_MULT",
        lpm_representation => "UNSIGNED",
        lpm_hint => "DEDICATED_MULTIPLIER_CIRCUITRY=YES, MAXIMIZE_SPEED=5",
        lpm_pipeline => 2
    )
    PORT MAP (
        dataa => prodXY_uid105_prod_uid47_fpMulTest_im18_a0,
        datab => prodXY_uid105_prod_uid47_fpMulTest_im18_b0,
        clken => en(0),
        aclr => prodXY_uid105_prod_uid47_fpMulTest_im18_reset,
        clock => clk,
        result => prodXY_uid105_prod_uid47_fpMulTest_im18_s1
    );
    prodXY_uid105_prod_uid47_fpMulTest_im18_q <= prodXY_uid105_prod_uid47_fpMulTest_im18_s1;

    -- prodXY_uid105_prod_uid47_fpMulTest_im0(MULT,107)@0 + 2
    prodXY_uid105_prod_uid47_fpMulTest_im0_a0 <= prodXY_uid105_prod_uid47_fpMulTest_bs1_merged_bit_select_b;
    prodXY_uid105_prod_uid47_fpMulTest_im0_b0 <= prodXY_uid105_prod_uid47_fpMulTest_bs2_merged_bit_select_b;
    prodXY_uid105_prod_uid47_fpMulTest_im0_reset <= areset;
    prodXY_uid105_prod_uid47_fpMulTest_im0_component : lpm_mult
    GENERIC MAP (
        lpm_widtha => 18,
        lpm_widthb => 18,
        lpm_widthp => 36,
        lpm_widths => 1,
        lpm_type => "LPM_MULT",
        lpm_representation => "UNSIGNED",
        lpm_hint => "DEDICATED_MULTIPLIER_CIRCUITRY=YES, MAXIMIZE_SPEED=5",
        lpm_pipeline => 2
    )
    PORT MAP (
        dataa => prodXY_uid105_prod_uid47_fpMulTest_im0_a0,
        datab => prodXY_uid105_prod_uid47_fpMulTest_im0_b0,
        clken => en(0),
        aclr => prodXY_uid105_prod_uid47_fpMulTest_im0_reset,
        clock => clk,
        result => prodXY_uid105_prod_uid47_fpMulTest_im0_s1
    );
    prodXY_uid105_prod_uid47_fpMulTest_im0_q <= prodXY_uid105_prod_uid47_fpMulTest_im0_s1;

    -- prodXY_uid105_prod_uid47_fpMulTest_join_27(BITJOIN,134)@2
    prodXY_uid105_prod_uid47_fpMulTest_join_27_q <= prodXY_uid105_prod_uid47_fpMulTest_im15_q & prodXY_uid105_prod_uid47_fpMulTest_im18_q & prodXY_uid105_prod_uid47_fpMulTest_im0_q;

    -- prodXY_uid105_prod_uid47_fpMulTest_result_add_0_0(ADD,143)@2
    prodXY_uid105_prod_uid47_fpMulTest_result_add_0_0_a <= STD_LOGIC_VECTOR("0" & prodXY_uid105_prod_uid47_fpMulTest_join_27_q);
    prodXY_uid105_prod_uid47_fpMulTest_result_add_0_0_b <= STD_LOGIC_VECTOR("000000000000000000" & prodXY_uid105_prod_uid47_fpMulTest_join_29_q);
    prodXY_uid105_prod_uid47_fpMulTest_result_add_0_0_o <= STD_LOGIC_VECTOR(UNSIGNED(prodXY_uid105_prod_uid47_fpMulTest_result_add_0_0_a) + UNSIGNED(prodXY_uid105_prod_uid47_fpMulTest_result_add_0_0_b));
    prodXY_uid105_prod_uid47_fpMulTest_result_add_0_0_q <= prodXY_uid105_prod_uid47_fpMulTest_result_add_0_0_o(106 downto 0);

    -- prodXY_uid105_prod_uid47_fpMulTest_result_add_1_0(ADD,145)@2
    prodXY_uid105_prod_uid47_fpMulTest_result_add_1_0_a <= STD_LOGIC_VECTOR("0" & prodXY_uid105_prod_uid47_fpMulTest_result_add_0_0_q);
    prodXY_uid105_prod_uid47_fpMulTest_result_add_1_0_b <= STD_LOGIC_VECTOR("000000000000000000" & prodXY_uid105_prod_uid47_fpMulTest_result_add_0_1_q);
    prodXY_uid105_prod_uid47_fpMulTest_result_add_1_0_o <= STD_LOGIC_VECTOR(UNSIGNED(prodXY_uid105_prod_uid47_fpMulTest_result_add_1_0_a) + UNSIGNED(prodXY_uid105_prod_uid47_fpMulTest_result_add_1_0_b));
    prodXY_uid105_prod_uid47_fpMulTest_result_add_1_0_q <= prodXY_uid105_prod_uid47_fpMulTest_result_add_1_0_o(107 downto 0);

    -- prodXY_uid105_prod_uid47_fpMulTest_result_add_2_0(ADD,146)@2
    prodXY_uid105_prod_uid47_fpMulTest_result_add_2_0_a <= STD_LOGIC_VECTOR("0" & prodXY_uid105_prod_uid47_fpMulTest_result_add_1_0_q);
    prodXY_uid105_prod_uid47_fpMulTest_result_add_2_0_b <= STD_LOGIC_VECTOR("00000000000000000000000000000000000000" & prodXY_uid105_prod_uid47_fpMulTest_align_34_q);
    prodXY_uid105_prod_uid47_fpMulTest_result_add_2_0_o <= STD_LOGIC_VECTOR(UNSIGNED(prodXY_uid105_prod_uid47_fpMulTest_result_add_2_0_a) + UNSIGNED(prodXY_uid105_prod_uid47_fpMulTest_result_add_2_0_b));
    prodXY_uid105_prod_uid47_fpMulTest_result_add_2_0_q <= prodXY_uid105_prod_uid47_fpMulTest_result_add_2_0_o(108 downto 0);

    -- osig_uid106_prod_uid47_fpMulTest(BITSELECT,105)@2
    osig_uid106_prod_uid47_fpMulTest_in <= prodXY_uid105_prod_uid47_fpMulTest_result_add_2_0_q(105 downto 0);
    osig_uid106_prod_uid47_fpMulTest_b <= osig_uid106_prod_uid47_fpMulTest_in(105 downto 0);

    -- normalizeBit_uid49_fpMulTest(BITSELECT,48)@2
    normalizeBit_uid49_fpMulTest_b <= STD_LOGIC_VECTOR(osig_uid106_prod_uid47_fpMulTest_b(105 downto 105));

    -- roundBitDetectionConstant_uid63_fpMulTest(CONSTANT,62)
    roundBitDetectionConstant_uid63_fpMulTest_q <= "010";

    -- fracRPostNormHigh_uid51_fpMulTest(BITSELECT,50)@2
    fracRPostNormHigh_uid51_fpMulTest_in <= osig_uid106_prod_uid47_fpMulTest_b(104 downto 0);
    fracRPostNormHigh_uid51_fpMulTest_b <= fracRPostNormHigh_uid51_fpMulTest_in(104 downto 52);

    -- fracRPostNormLow_uid52_fpMulTest(BITSELECT,51)@2
    fracRPostNormLow_uid52_fpMulTest_in <= osig_uid106_prod_uid47_fpMulTest_b(103 downto 0);
    fracRPostNormLow_uid52_fpMulTest_b <= fracRPostNormLow_uid52_fpMulTest_in(103 downto 51);

    -- fracRPostNorm_uid53_fpMulTest(MUX,52)@2
    fracRPostNorm_uid53_fpMulTest_s <= normalizeBit_uid49_fpMulTest_b;
    fracRPostNorm_uid53_fpMulTest_combproc: PROCESS (fracRPostNorm_uid53_fpMulTest_s, en, fracRPostNormLow_uid52_fpMulTest_b, fracRPostNormHigh_uid51_fpMulTest_b)
    BEGIN
        CASE (fracRPostNorm_uid53_fpMulTest_s) IS
            WHEN "0" => fracRPostNorm_uid53_fpMulTest_q <= fracRPostNormLow_uid52_fpMulTest_b;
            WHEN "1" => fracRPostNorm_uid53_fpMulTest_q <= fracRPostNormHigh_uid51_fpMulTest_b;
            WHEN OTHERS => fracRPostNorm_uid53_fpMulTest_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- fracRPostNorm1dto0_uid61_fpMulTest(BITSELECT,60)@2
    fracRPostNorm1dto0_uid61_fpMulTest_in <= fracRPostNorm_uid53_fpMulTest_q(1 downto 0);
    fracRPostNorm1dto0_uid61_fpMulTest_b <= fracRPostNorm1dto0_uid61_fpMulTest_in(1 downto 0);

    -- extraStickyBitOfProd_uid55_fpMulTest(BITSELECT,54)@2
    extraStickyBitOfProd_uid55_fpMulTest_in <= STD_LOGIC_VECTOR(osig_uid106_prod_uid47_fpMulTest_b(51 downto 0));
    extraStickyBitOfProd_uid55_fpMulTest_b <= STD_LOGIC_VECTOR(extraStickyBitOfProd_uid55_fpMulTest_in(51 downto 51));

    -- extraStickyBit_uid56_fpMulTest(MUX,55)@2
    extraStickyBit_uid56_fpMulTest_s <= normalizeBit_uid49_fpMulTest_b;
    extraStickyBit_uid56_fpMulTest_combproc: PROCESS (extraStickyBit_uid56_fpMulTest_s, en, GND_q, extraStickyBitOfProd_uid55_fpMulTest_b)
    BEGIN
        CASE (extraStickyBit_uid56_fpMulTest_s) IS
            WHEN "0" => extraStickyBit_uid56_fpMulTest_q <= GND_q;
            WHEN "1" => extraStickyBit_uid56_fpMulTest_q <= extraStickyBitOfProd_uid55_fpMulTest_b;
            WHEN OTHERS => extraStickyBit_uid56_fpMulTest_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- stickyRange_uid54_fpMulTest(BITSELECT,53)@2
    stickyRange_uid54_fpMulTest_in <= osig_uid106_prod_uid47_fpMulTest_b(50 downto 0);
    stickyRange_uid54_fpMulTest_b <= stickyRange_uid54_fpMulTest_in(50 downto 0);

    -- stickyExtendedRange_uid57_fpMulTest(BITJOIN,56)@2
    stickyExtendedRange_uid57_fpMulTest_q <= extraStickyBit_uid56_fpMulTest_q & stickyRange_uid54_fpMulTest_b;

    -- stickyRangeComparator_uid59_fpMulTest(LOGICAL,58)@2
    stickyRangeComparator_uid59_fpMulTest_q <= "1" WHEN stickyExtendedRange_uid57_fpMulTest_q = cstZeroWF_uid11_fpMulTest_q ELSE "0";

    -- sticky_uid60_fpMulTest(LOGICAL,59)@2
    sticky_uid60_fpMulTest_q <= not (stickyRangeComparator_uid59_fpMulTest_q);

    -- lrs_uid62_fpMulTest(BITJOIN,61)@2
    lrs_uid62_fpMulTest_q <= fracRPostNorm1dto0_uid61_fpMulTest_b & sticky_uid60_fpMulTest_q;

    -- roundBitDetectionPattern_uid64_fpMulTest(LOGICAL,63)@2
    roundBitDetectionPattern_uid64_fpMulTest_q <= "1" WHEN lrs_uid62_fpMulTest_q = roundBitDetectionConstant_uid63_fpMulTest_q ELSE "0";

    -- roundBit_uid65_fpMulTest(LOGICAL,64)@2
    roundBit_uid65_fpMulTest_q <= not (roundBitDetectionPattern_uid64_fpMulTest_q);

    -- roundBitAndNormalizationOp_uid68_fpMulTest(BITJOIN,67)@2
    roundBitAndNormalizationOp_uid68_fpMulTest_q <= GND_q & normalizeBit_uid49_fpMulTest_b & cstZeroWF_uid11_fpMulTest_q & roundBit_uid65_fpMulTest_q;

    -- biasInc_uid45_fpMulTest(CONSTANT,44)
    biasInc_uid45_fpMulTest_q <= "0001111111111";

    -- expSum_uid44_fpMulTest(ADD,43)@0 + 1
    expSum_uid44_fpMulTest_a <= STD_LOGIC_VECTOR("0" & expX_uid6_fpMulTest_b);
    expSum_uid44_fpMulTest_b <= STD_LOGIC_VECTOR("0" & expY_uid7_fpMulTest_b);
    expSum_uid44_fpMulTest_clkproc: PROCESS (clk, areset)
    BEGIN
        IF (areset = '1') THEN
            expSum_uid44_fpMulTest_o <= (others => '0');
        ELSIF (clk'EVENT AND clk = '1') THEN
            IF (en = "1") THEN
                expSum_uid44_fpMulTest_o <= STD_LOGIC_VECTOR(UNSIGNED(expSum_uid44_fpMulTest_a) + UNSIGNED(expSum_uid44_fpMulTest_b));
            END IF;
        END IF;
    END PROCESS;
    expSum_uid44_fpMulTest_q <= expSum_uid44_fpMulTest_o(11 downto 0);

    -- redist1_expSum_uid44_fpMulTest_q_2(DELAY,150)
    redist1_expSum_uid44_fpMulTest_q_2 : dspba_delay
    GENERIC MAP ( width => 12, depth => 1, reset_kind => "ASYNC" )
    PORT MAP ( xin => expSum_uid44_fpMulTest_q, xout => redist1_expSum_uid44_fpMulTest_q_2_q, ena => en(0), clk => clk, aclr => areset );

    -- expSumMBias_uid46_fpMulTest(SUB,45)@2
    expSumMBias_uid46_fpMulTest_a <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR("0" & "00" & redist1_expSum_uid44_fpMulTest_q_2_q));
    expSumMBias_uid46_fpMulTest_b <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR((14 downto 13 => biasInc_uid45_fpMulTest_q(12)) & biasInc_uid45_fpMulTest_q));
    expSumMBias_uid46_fpMulTest_o <= STD_LOGIC_VECTOR(SIGNED(expSumMBias_uid46_fpMulTest_a) - SIGNED(expSumMBias_uid46_fpMulTest_b));
    expSumMBias_uid46_fpMulTest_q <= expSumMBias_uid46_fpMulTest_o(13 downto 0);

    -- expFracPreRound_uid66_fpMulTest(BITJOIN,65)@2
    expFracPreRound_uid66_fpMulTest_q <= expSumMBias_uid46_fpMulTest_q & fracRPostNorm_uid53_fpMulTest_q;

    -- expFracRPostRounding_uid69_fpMulTest(ADD,68)@2
    expFracRPostRounding_uid69_fpMulTest_a <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR((68 downto 67 => expFracPreRound_uid66_fpMulTest_q(66)) & expFracPreRound_uid66_fpMulTest_q));
    expFracRPostRounding_uid69_fpMulTest_b <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR("0" & "0000000000000" & roundBitAndNormalizationOp_uid68_fpMulTest_q));
    expFracRPostRounding_uid69_fpMulTest_o <= STD_LOGIC_VECTOR(SIGNED(expFracRPostRounding_uid69_fpMulTest_a) + SIGNED(expFracRPostRounding_uid69_fpMulTest_b));
    expFracRPostRounding_uid69_fpMulTest_q <= expFracRPostRounding_uid69_fpMulTest_o(67 downto 0);

    -- expRPreExcExt_uid71_fpMulTest(BITSELECT,70)@2
    expRPreExcExt_uid71_fpMulTest_b <= STD_LOGIC_VECTOR(expFracRPostRounding_uid69_fpMulTest_q(67 downto 53));

    -- expRPreExc_uid72_fpMulTest(BITSELECT,71)@2
    expRPreExc_uid72_fpMulTest_in <= expRPreExcExt_uid71_fpMulTest_b(10 downto 0);
    expRPreExc_uid72_fpMulTest_b <= expRPreExc_uid72_fpMulTest_in(10 downto 0);

    -- expOvf_uid75_fpMulTest(COMPARE,74)@2
    expOvf_uid75_fpMulTest_a <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR((16 downto 15 => expRPreExcExt_uid71_fpMulTest_b(14)) & expRPreExcExt_uid71_fpMulTest_b));
    expOvf_uid75_fpMulTest_b <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR("0" & "00000" & cstAllOWE_uid10_fpMulTest_q));
    expOvf_uid75_fpMulTest_o <= STD_LOGIC_VECTOR(SIGNED(expOvf_uid75_fpMulTest_a) - SIGNED(expOvf_uid75_fpMulTest_b));
    expOvf_uid75_fpMulTest_n(0) <= not (expOvf_uid75_fpMulTest_o(16));

    -- invExpXIsMax_uid35_fpMulTest(LOGICAL,34)@2
    invExpXIsMax_uid35_fpMulTest_q <= not (redist3_expXIsMax_uid30_fpMulTest_q_2_q);

    -- InvExpXIsZero_uid36_fpMulTest(LOGICAL,35)@2
    InvExpXIsZero_uid36_fpMulTest_q <= not (redist4_excZ_y_uid29_fpMulTest_q_2_q);

    -- excR_y_uid37_fpMulTest(LOGICAL,36)@2
    excR_y_uid37_fpMulTest_q <= InvExpXIsZero_uid36_fpMulTest_q and invExpXIsMax_uid35_fpMulTest_q;

    -- invExpXIsMax_uid21_fpMulTest(LOGICAL,20)@2
    invExpXIsMax_uid21_fpMulTest_q <= not (redist6_expXIsMax_uid16_fpMulTest_q_2_q);

    -- InvExpXIsZero_uid22_fpMulTest(LOGICAL,21)@2
    InvExpXIsZero_uid22_fpMulTest_q <= not (redist7_excZ_x_uid15_fpMulTest_q_2_q);

    -- excR_x_uid23_fpMulTest(LOGICAL,22)@2
    excR_x_uid23_fpMulTest_q <= InvExpXIsZero_uid22_fpMulTest_q and invExpXIsMax_uid21_fpMulTest_q;

    -- ExcROvfAndInReg_uid84_fpMulTest(LOGICAL,83)@2
    ExcROvfAndInReg_uid84_fpMulTest_q <= excR_x_uid23_fpMulTest_q and excR_y_uid37_fpMulTest_q and expOvf_uid75_fpMulTest_n;

    -- excYRAndExcXI_uid83_fpMulTest(LOGICAL,82)@2
    excYRAndExcXI_uid83_fpMulTest_q <= excR_y_uid37_fpMulTest_q and excI_x_uid19_fpMulTest_q;

    -- excXRAndExcYI_uid82_fpMulTest(LOGICAL,81)@2
    excXRAndExcYI_uid82_fpMulTest_q <= excR_x_uid23_fpMulTest_q and excI_y_uid33_fpMulTest_q;

    -- excXIAndExcYI_uid81_fpMulTest(LOGICAL,80)@2
    excXIAndExcYI_uid81_fpMulTest_q <= excI_x_uid19_fpMulTest_q and excI_y_uid33_fpMulTest_q;

    -- excRInf_uid85_fpMulTest(LOGICAL,84)@2
    excRInf_uid85_fpMulTest_q <= excXIAndExcYI_uid81_fpMulTest_q or excXRAndExcYI_uid82_fpMulTest_q or excYRAndExcXI_uid83_fpMulTest_q or ExcROvfAndInReg_uid84_fpMulTest_q;

    -- expUdf_uid73_fpMulTest(COMPARE,72)@2
    expUdf_uid73_fpMulTest_a <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR("0" & "000000000000000" & GND_q));
    expUdf_uid73_fpMulTest_b <= STD_LOGIC_VECTOR(STD_LOGIC_VECTOR((16 downto 15 => expRPreExcExt_uid71_fpMulTest_b(14)) & expRPreExcExt_uid71_fpMulTest_b));
    expUdf_uid73_fpMulTest_o <= STD_LOGIC_VECTOR(SIGNED(expUdf_uid73_fpMulTest_a) - SIGNED(expUdf_uid73_fpMulTest_b));
    expUdf_uid73_fpMulTest_n(0) <= not (expUdf_uid73_fpMulTest_o(16));

    -- excZC3_uid79_fpMulTest(LOGICAL,78)@2
    excZC3_uid79_fpMulTest_q <= excR_x_uid23_fpMulTest_q and excR_y_uid37_fpMulTest_q and expUdf_uid73_fpMulTest_n;

    -- excYZAndExcXR_uid78_fpMulTest(LOGICAL,77)@2
    excYZAndExcXR_uid78_fpMulTest_q <= redist4_excZ_y_uid29_fpMulTest_q_2_q and excR_x_uid23_fpMulTest_q;

    -- excXZAndExcYR_uid77_fpMulTest(LOGICAL,76)@2
    excXZAndExcYR_uid77_fpMulTest_q <= redist7_excZ_x_uid15_fpMulTest_q_2_q and excR_y_uid37_fpMulTest_q;

    -- excXZAndExcYZ_uid76_fpMulTest(LOGICAL,75)@2
    excXZAndExcYZ_uid76_fpMulTest_q <= redist7_excZ_x_uid15_fpMulTest_q_2_q and redist4_excZ_y_uid29_fpMulTest_q_2_q;

    -- excRZero_uid80_fpMulTest(LOGICAL,79)@2
    excRZero_uid80_fpMulTest_q <= excXZAndExcYZ_uid76_fpMulTest_q or excXZAndExcYR_uid77_fpMulTest_q or excYZAndExcXR_uid78_fpMulTest_q or excZC3_uid79_fpMulTest_q;

    -- concExc_uid90_fpMulTest(BITJOIN,89)@2
    concExc_uid90_fpMulTest_q <= excRNaN_uid89_fpMulTest_q & excRInf_uid85_fpMulTest_q & excRZero_uid80_fpMulTest_q;

    -- excREnc_uid91_fpMulTest(LOOKUP,90)@2
    excREnc_uid91_fpMulTest_combproc: PROCESS (concExc_uid90_fpMulTest_q)
    BEGIN
        -- Begin reserved scope level
        CASE (concExc_uid90_fpMulTest_q) IS
            WHEN "000" => excREnc_uid91_fpMulTest_q <= "01";
            WHEN "001" => excREnc_uid91_fpMulTest_q <= "00";
            WHEN "010" => excREnc_uid91_fpMulTest_q <= "10";
            WHEN "011" => excREnc_uid91_fpMulTest_q <= "00";
            WHEN "100" => excREnc_uid91_fpMulTest_q <= "11";
            WHEN "101" => excREnc_uid91_fpMulTest_q <= "00";
            WHEN "110" => excREnc_uid91_fpMulTest_q <= "00";
            WHEN "111" => excREnc_uid91_fpMulTest_q <= "00";
            WHEN OTHERS => -- unreachable
                           excREnc_uid91_fpMulTest_q <= (others => '-');
        END CASE;
        -- End reserved scope level
    END PROCESS;

    -- expRPostExc_uid100_fpMulTest(MUX,99)@2
    expRPostExc_uid100_fpMulTest_s <= excREnc_uid91_fpMulTest_q;
    expRPostExc_uid100_fpMulTest_combproc: PROCESS (expRPostExc_uid100_fpMulTest_s, en, cstAllZWE_uid12_fpMulTest_q, expRPreExc_uid72_fpMulTest_b, cstAllOWE_uid10_fpMulTest_q)
    BEGIN
        CASE (expRPostExc_uid100_fpMulTest_s) IS
            WHEN "00" => expRPostExc_uid100_fpMulTest_q <= cstAllZWE_uid12_fpMulTest_q;
            WHEN "01" => expRPostExc_uid100_fpMulTest_q <= expRPreExc_uid72_fpMulTest_b;
            WHEN "10" => expRPostExc_uid100_fpMulTest_q <= cstAllOWE_uid10_fpMulTest_q;
            WHEN "11" => expRPostExc_uid100_fpMulTest_q <= cstAllOWE_uid10_fpMulTest_q;
            WHEN OTHERS => expRPostExc_uid100_fpMulTest_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- oneFracRPostExc2_uid92_fpMulTest(CONSTANT,91)
    oneFracRPostExc2_uid92_fpMulTest_q <= "0000000000000000000000000000000000000000000000000001";

    -- fracRPreExc_uid70_fpMulTest(BITSELECT,69)@2
    fracRPreExc_uid70_fpMulTest_in <= expFracRPostRounding_uid69_fpMulTest_q(52 downto 0);
    fracRPreExc_uid70_fpMulTest_b <= fracRPreExc_uid70_fpMulTest_in(52 downto 1);

    -- fracRPostExc_uid95_fpMulTest(MUX,94)@2
    fracRPostExc_uid95_fpMulTest_s <= excREnc_uid91_fpMulTest_q;
    fracRPostExc_uid95_fpMulTest_combproc: PROCESS (fracRPostExc_uid95_fpMulTest_s, en, cstZeroWF_uid11_fpMulTest_q, fracRPreExc_uid70_fpMulTest_b, oneFracRPostExc2_uid92_fpMulTest_q)
    BEGIN
        CASE (fracRPostExc_uid95_fpMulTest_s) IS
            WHEN "00" => fracRPostExc_uid95_fpMulTest_q <= cstZeroWF_uid11_fpMulTest_q;
            WHEN "01" => fracRPostExc_uid95_fpMulTest_q <= fracRPreExc_uid70_fpMulTest_b;
            WHEN "10" => fracRPostExc_uid95_fpMulTest_q <= cstZeroWF_uid11_fpMulTest_q;
            WHEN "11" => fracRPostExc_uid95_fpMulTest_q <= oneFracRPostExc2_uid92_fpMulTest_q;
            WHEN OTHERS => fracRPostExc_uid95_fpMulTest_q <= (others => '0');
        END CASE;
    END PROCESS;

    -- R_uid103_fpMulTest(BITJOIN,102)@2
    R_uid103_fpMulTest_q <= signRPostExc_uid102_fpMulTest_q & expRPostExc_uid100_fpMulTest_q & fracRPostExc_uid95_fpMulTest_q;

    -- xOut(GPOUT,4)@2
    q <= R_uid103_fpMulTest_q;

END normal;
