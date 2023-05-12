-- Copyright (C) 2022  Intel Corporation. All rights reserved.
-- Your use of Intel Corporation's design tools, logic functions 
-- and other software and tools, and any partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Intel Program License 
-- Subscription Agreement, the Intel Quartus Prime License Agreement,
-- the Intel FPGA IP License Agreement, or other applicable license
-- agreement, including, without limitation, that your use is for
-- the sole purpose of programming logic devices manufactured by
-- Intel and sold by Intel or its authorized distributors.  Please
-- refer to the applicable agreement for further details, at
-- https://fpgasoftware.intel.com/eula.

-- VENDOR "Altera"
-- PROGRAM "Quartus Prime"
-- VERSION "Version 22.1std.0 Build 915 10/25/2022 SC Lite Edition"

-- DATE "05/05/2023 15:42:00"

-- 
-- Device: Altera 5CEBA4F23C7 Package FBGA484
-- 

-- 
-- This VHDL file should be used for ModelSim (VHDL) only
-- 

LIBRARY ALTERA;
LIBRARY ALTERA_LNSIM;
LIBRARY CYCLONEV;
LIBRARY IEEE;
USE ALTERA.ALTERA_PRIMITIVES_COMPONENTS.ALL;
USE ALTERA_LNSIM.ALTERA_LNSIM_COMPONENTS.ALL;
USE CYCLONEV.CYCLONEV_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	voting IS
    PORT (
	prob_1 : IN std_logic_vector(23 DOWNTO 0);
	prob_2 : IN std_logic_vector(23 DOWNTO 0);
	prob_valid_1 : IN std_logic;
	prob_valid_2 : IN std_logic;
	clk_voting : IN std_logic;
	prob_mean : OUT std_logic_vector(23 DOWNTO 0);
	prediction : OUT std_logic
	);
END voting;

-- Design Ports Information
-- prob_mean[0]	=>  Location: PIN_U11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[1]	=>  Location: PIN_T8,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[2]	=>  Location: PIN_R12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[3]	=>  Location: PIN_AA13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[4]	=>  Location: PIN_Y11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[5]	=>  Location: PIN_T10,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[6]	=>  Location: PIN_T7,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[7]	=>  Location: PIN_C2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[8]	=>  Location: PIN_U12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[9]	=>  Location: PIN_AA9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[10]	=>  Location: PIN_W9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[11]	=>  Location: PIN_M6,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[12]	=>  Location: PIN_M8,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[13]	=>  Location: PIN_AA12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[14]	=>  Location: PIN_Y10,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[15]	=>  Location: PIN_U13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[16]	=>  Location: PIN_Y9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[17]	=>  Location: PIN_P8,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[18]	=>  Location: PIN_M9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[19]	=>  Location: PIN_AA10,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[20]	=>  Location: PIN_P12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[21]	=>  Location: PIN_R9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[22]	=>  Location: PIN_P9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_mean[23]	=>  Location: PIN_N9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prediction	=>  Location: PIN_U6,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_valid_2	=>  Location: PIN_V6,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- clk_voting	=>  Location: PIN_M16,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_valid_1	=>  Location: PIN_V9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[1]	=>  Location: PIN_AB5,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[1]	=>  Location: PIN_AB11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[2]	=>  Location: PIN_R10,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[2]	=>  Location: PIN_L2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[3]	=>  Location: PIN_U1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[3]	=>  Location: PIN_L1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[4]	=>  Location: PIN_AA2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[4]	=>  Location: PIN_AA14,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[5]	=>  Location: PIN_N2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[5]	=>  Location: PIN_AA1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[6]	=>  Location: PIN_T18,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[6]	=>  Location: PIN_T9,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[7]	=>  Location: PIN_P6,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[7]	=>  Location: PIN_V13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[8]	=>  Location: PIN_W2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[8]	=>  Location: PIN_AA8,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[9]	=>  Location: PIN_T13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[9]	=>  Location: PIN_AB10,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[10]	=>  Location: PIN_AB6,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[10]	=>  Location: PIN_M7,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[11]	=>  Location: PIN_R15,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[11]	=>  Location: PIN_R11,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[12]	=>  Location: PIN_U7,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[12]	=>  Location: PIN_AB13,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[13]	=>  Location: PIN_R6,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[13]	=>  Location: PIN_U10,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[14]	=>  Location: PIN_AA7,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[14]	=>  Location: PIN_Y15,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[15]	=>  Location: PIN_C1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[15]	=>  Location: PIN_P7,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[16]	=>  Location: PIN_N1,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[16]	=>  Location: PIN_T12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[17]	=>  Location: PIN_U8,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[17]	=>  Location: PIN_AB7,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[18]	=>  Location: PIN_N6,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[18]	=>  Location: PIN_AB12,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[19]	=>  Location: PIN_U2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[19]	=>  Location: PIN_W8,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[20]	=>  Location: PIN_AA15,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[20]	=>  Location: PIN_R5,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[21]	=>  Location: PIN_E2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[21]	=>  Location: PIN_R7,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[22]	=>  Location: PIN_AB8,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[22]	=>  Location: PIN_T22,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[23]	=>  Location: PIN_V10,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[23]	=>  Location: PIN_N8,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_2[0]	=>  Location: PIN_Y3,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- prob_1[0]	=>  Location: PIN_D3,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF voting IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_prob_1 : std_logic_vector(23 DOWNTO 0);
SIGNAL ww_prob_2 : std_logic_vector(23 DOWNTO 0);
SIGNAL ww_prob_valid_1 : std_logic;
SIGNAL ww_prob_valid_2 : std_logic;
SIGNAL ww_clk_voting : std_logic;
SIGNAL ww_prob_mean : std_logic_vector(23 DOWNTO 0);
SIGNAL ww_prediction : std_logic;
SIGNAL \~QUARTUS_CREATED_GND~I_combout\ : std_logic;
SIGNAL \clk_voting~input_o\ : std_logic;
SIGNAL \clk_voting~inputCLKENA0_outclk\ : std_logic;
SIGNAL \mean0|Add1~69_sumout\ : std_logic;
SIGNAL \prob_valid_2~input_o\ : std_logic;
SIGNAL \mean0|Add0~37_sumout\ : std_logic;
SIGNAL \prob_valid_1~input_o\ : std_logic;
SIGNAL \mean0|Add0~38\ : std_logic;
SIGNAL \mean0|Add0~49_sumout\ : std_logic;
SIGNAL \mean0|Add0~50\ : std_logic;
SIGNAL \mean0|Add0~45_sumout\ : std_logic;
SIGNAL \mean0|Add0~46\ : std_logic;
SIGNAL \mean0|Add0~41_sumout\ : std_logic;
SIGNAL \mean0|Add0~42\ : std_logic;
SIGNAL \mean0|Add0~117_sumout\ : std_logic;
SIGNAL \mean0|Add0~118\ : std_logic;
SIGNAL \mean0|Add0~33_sumout\ : std_logic;
SIGNAL \mean0|Add0~34\ : std_logic;
SIGNAL \mean0|Add0~29_sumout\ : std_logic;
SIGNAL \mean0|Add0~30\ : std_logic;
SIGNAL \mean0|Add0~73_sumout\ : std_logic;
SIGNAL \mean0|Add0~74\ : std_logic;
SIGNAL \mean0|Add0~65_sumout\ : std_logic;
SIGNAL \mean0|Add0~66\ : std_logic;
SIGNAL \mean0|Add0~61_sumout\ : std_logic;
SIGNAL \mean0|Add0~62\ : std_logic;
SIGNAL \mean0|Add0~57_sumout\ : std_logic;
SIGNAL \mean0|Add0~58\ : std_logic;
SIGNAL \mean0|Add0~13_sumout\ : std_logic;
SIGNAL \mean0|Add0~14\ : std_logic;
SIGNAL \mean0|Add0~53_sumout\ : std_logic;
SIGNAL \mean0|Add0~54\ : std_logic;
SIGNAL \mean0|Add0~121_sumout\ : std_logic;
SIGNAL \mean0|Add0~122\ : std_logic;
SIGNAL \mean0|Add0~77_sumout\ : std_logic;
SIGNAL \mean0|Add0~78\ : std_logic;
SIGNAL \mean0|Add0~113_sumout\ : std_logic;
SIGNAL \mean0|Add0~114\ : std_logic;
SIGNAL \mean0|Add0~109_sumout\ : std_logic;
SIGNAL \mean0|Add0~110\ : std_logic;
SIGNAL \mean0|Add0~105_sumout\ : std_logic;
SIGNAL \mean0|Add0~106\ : std_logic;
SIGNAL \mean0|Add0~101_sumout\ : std_logic;
SIGNAL \mean0|Add0~102\ : std_logic;
SIGNAL \mean0|Add0~97_sumout\ : std_logic;
SIGNAL \mean0|Add0~98\ : std_logic;
SIGNAL \mean0|Add0~93_sumout\ : std_logic;
SIGNAL \mean0|Add0~94\ : std_logic;
SIGNAL \mean0|Add0~89_sumout\ : std_logic;
SIGNAL \mean0|Add0~90\ : std_logic;
SIGNAL \mean0|Add0~85_sumout\ : std_logic;
SIGNAL \mean0|Add0~86\ : std_logic;
SIGNAL \mean0|Add0~81_sumout\ : std_logic;
SIGNAL \mean0|Add0~82\ : std_logic;
SIGNAL \mean0|Add0~9_sumout\ : std_logic;
SIGNAL \mean0|Add0~10\ : std_logic;
SIGNAL \mean0|Add0~69_sumout\ : std_logic;
SIGNAL \mean0|Add0~70\ : std_logic;
SIGNAL \mean0|Add0~1_sumout\ : std_logic;
SIGNAL \mean0|Equal0~1_combout\ : std_logic;
SIGNAL \mean0|Equal0~4_combout\ : std_logic;
SIGNAL \mean0|Equal0~2_combout\ : std_logic;
SIGNAL \mean0|Equal0~3_combout\ : std_logic;
SIGNAL \mean0|Add0~2\ : std_logic;
SIGNAL \mean0|Add0~25_sumout\ : std_logic;
SIGNAL \mean0|Add0~26\ : std_logic;
SIGNAL \mean0|Add0~5_sumout\ : std_logic;
SIGNAL \mean0|Add0~6\ : std_logic;
SIGNAL \mean0|Add0~21_sumout\ : std_logic;
SIGNAL \mean0|Add0~22\ : std_logic;
SIGNAL \mean0|Add0~17_sumout\ : std_logic;
SIGNAL \mean0|Equal0~0_combout\ : std_logic;
SIGNAL \mean0|Equal0~5_combout\ : std_logic;
SIGNAL \mean0|Equal1~0_combout\ : std_logic;
SIGNAL \mean0|Add1~2\ : std_logic;
SIGNAL \mean0|Add1~89_sumout\ : std_logic;
SIGNAL \mean0|Add1~90\ : std_logic;
SIGNAL \mean0|Add1~61_sumout\ : std_logic;
SIGNAL \mean0|Add1~62\ : std_logic;
SIGNAL \mean0|Add1~93_sumout\ : std_logic;
SIGNAL \mean0|Add1~94\ : std_logic;
SIGNAL \mean0|Add1~97_sumout\ : std_logic;
SIGNAL \mean0|Add1~98\ : std_logic;
SIGNAL \mean0|Add1~101_sumout\ : std_logic;
SIGNAL \mean0|Add1~102\ : std_logic;
SIGNAL \mean0|Add1~29_sumout\ : std_logic;
SIGNAL \mean0|Add1~30\ : std_logic;
SIGNAL \mean0|Add1~105_sumout\ : std_logic;
SIGNAL \mean0|Add1~106\ : std_logic;
SIGNAL \mean0|Add1~109_sumout\ : std_logic;
SIGNAL \mean0|Add1~110\ : std_logic;
SIGNAL \mean0|Add1~113_sumout\ : std_logic;
SIGNAL \mean0|Add1~114\ : std_logic;
SIGNAL \mean0|Add1~117_sumout\ : std_logic;
SIGNAL \mean0|Add1~118\ : std_logic;
SIGNAL \mean0|Add1~121_sumout\ : std_logic;
SIGNAL \mean0|Equal1~4_combout\ : std_logic;
SIGNAL \mean0|Add1~122\ : std_logic;
SIGNAL \mean0|Add1~33_sumout\ : std_logic;
SIGNAL \mean0|Equal1~3_combout\ : std_logic;
SIGNAL \mean0|Equal1~2_combout\ : std_logic;
SIGNAL \mean0|Equal1~1_combout\ : std_logic;
SIGNAL \mean0|Equal1~5_combout\ : std_logic;
SIGNAL \mean0|process_0~0_combout\ : std_logic;
SIGNAL \mean0|Add1~70\ : std_logic;
SIGNAL \mean0|Add1~65_sumout\ : std_logic;
SIGNAL \mean0|Add1~66\ : std_logic;
SIGNAL \mean0|Add1~73_sumout\ : std_logic;
SIGNAL \mean0|Add1~74\ : std_logic;
SIGNAL \mean0|Add1~77_sumout\ : std_logic;
SIGNAL \mean0|Add1~78\ : std_logic;
SIGNAL \mean0|Add1~81_sumout\ : std_logic;
SIGNAL \mean0|Add1~82\ : std_logic;
SIGNAL \mean0|Add1~37_sumout\ : std_logic;
SIGNAL \mean0|Add1~38\ : std_logic;
SIGNAL \mean0|Add1~41_sumout\ : std_logic;
SIGNAL \mean0|Add1~42\ : std_logic;
SIGNAL \mean0|Add1~45_sumout\ : std_logic;
SIGNAL \mean0|Add1~46\ : std_logic;
SIGNAL \mean0|Add1~49_sumout\ : std_logic;
SIGNAL \mean0|Add1~50\ : std_logic;
SIGNAL \mean0|Add1~53_sumout\ : std_logic;
SIGNAL \mean0|Add1~54\ : std_logic;
SIGNAL \mean0|Add1~57_sumout\ : std_logic;
SIGNAL \mean0|Add1~58\ : std_logic;
SIGNAL \mean0|Add1~5_sumout\ : std_logic;
SIGNAL \mean0|Add1~6\ : std_logic;
SIGNAL \mean0|Add1~9_sumout\ : std_logic;
SIGNAL \mean0|Add1~10\ : std_logic;
SIGNAL \mean0|Add1~13_sumout\ : std_logic;
SIGNAL \mean0|Add1~14\ : std_logic;
SIGNAL \mean0|Add1~85_sumout\ : std_logic;
SIGNAL \mean0|Add1~86\ : std_logic;
SIGNAL \mean0|Add1~17_sumout\ : std_logic;
SIGNAL \mean0|Add1~18\ : std_logic;
SIGNAL \mean0|Add1~21_sumout\ : std_logic;
SIGNAL \mean0|Add1~22\ : std_logic;
SIGNAL \mean0|Add1~25_sumout\ : std_logic;
SIGNAL \mean0|Add1~26\ : std_logic;
SIGNAL \mean0|Add1~1_sumout\ : std_logic;
SIGNAL \mean0|init_flag_a~0_combout\ : std_logic;
SIGNAL \mean0|init_flag_a~q\ : std_logic;
SIGNAL \prob_2[1]~input_o\ : std_logic;
SIGNAL \mean0|b_stable_valid[9]~0_combout\ : std_logic;
SIGNAL \prob_1[1]~input_o\ : std_logic;
SIGNAL \mean0|a_stable_valid[15]~0_combout\ : std_logic;
SIGNAL \prob_1[0]~input_o\ : std_logic;
SIGNAL \prob_2[0]~input_o\ : std_logic;
SIGNAL \mean0|Add2~94_cout\ : std_logic;
SIGNAL \mean0|Add2~1_sumout\ : std_logic;
SIGNAL \mean0|init_flag_b~0_combout\ : std_logic;
SIGNAL \mean0|init_flag_b~q\ : std_logic;
SIGNAL \mean0|c[0]~0_combout\ : std_logic;
SIGNAL \prob_2[2]~input_o\ : std_logic;
SIGNAL \mean0|b_stable_valid[2]~feeder_combout\ : std_logic;
SIGNAL \prob_1[2]~input_o\ : std_logic;
SIGNAL \mean0|Add2~2\ : std_logic;
SIGNAL \mean0|Add2~5_sumout\ : std_logic;
SIGNAL \mean0|c[1]~1_combout\ : std_logic;
SIGNAL \prob_2[3]~input_o\ : std_logic;
SIGNAL \prob_1[3]~input_o\ : std_logic;
SIGNAL \mean0|Add2~6\ : std_logic;
SIGNAL \mean0|Add2~9_sumout\ : std_logic;
SIGNAL \mean0|c[2]~2_combout\ : std_logic;
SIGNAL \prob_1[4]~input_o\ : std_logic;
SIGNAL \prob_2[4]~input_o\ : std_logic;
SIGNAL \mean0|b_stable_valid[4]~feeder_combout\ : std_logic;
SIGNAL \mean0|Add2~10\ : std_logic;
SIGNAL \mean0|Add2~13_sumout\ : std_logic;
SIGNAL \mean0|c[3]~3_combout\ : std_logic;
SIGNAL \prob_2[5]~input_o\ : std_logic;
SIGNAL \prob_1[5]~input_o\ : std_logic;
SIGNAL \mean0|Add2~14\ : std_logic;
SIGNAL \mean0|Add2~17_sumout\ : std_logic;
SIGNAL \mean0|c[4]~4_combout\ : std_logic;
SIGNAL \prob_2[6]~input_o\ : std_logic;
SIGNAL \mean0|b_stable_valid[6]~feeder_combout\ : std_logic;
SIGNAL \prob_1[6]~input_o\ : std_logic;
SIGNAL \mean0|Add2~18\ : std_logic;
SIGNAL \mean0|Add2~21_sumout\ : std_logic;
SIGNAL \mean0|c[5]~5_combout\ : std_logic;
SIGNAL \prob_1[7]~input_o\ : std_logic;
SIGNAL \prob_2[7]~input_o\ : std_logic;
SIGNAL \mean0|Add2~22\ : std_logic;
SIGNAL \mean0|Add2~25_sumout\ : std_logic;
SIGNAL \mean0|c[6]~6_combout\ : std_logic;
SIGNAL \prob_2[8]~input_o\ : std_logic;
SIGNAL \mean0|b_stable_valid[8]~feeder_combout\ : std_logic;
SIGNAL \prob_1[8]~input_o\ : std_logic;
SIGNAL \mean0|Add2~26\ : std_logic;
SIGNAL \mean0|Add2~29_sumout\ : std_logic;
SIGNAL \mean0|c[7]~7_combout\ : std_logic;
SIGNAL \prob_1[9]~input_o\ : std_logic;
SIGNAL \prob_2[9]~input_o\ : std_logic;
SIGNAL \mean0|b_stable_valid[9]~feeder_combout\ : std_logic;
SIGNAL \mean0|Add2~30\ : std_logic;
SIGNAL \mean0|Add2~33_sumout\ : std_logic;
SIGNAL \mean0|c[8]~8_combout\ : std_logic;
SIGNAL \prob_2[10]~input_o\ : std_logic;
SIGNAL \mean0|b_stable_valid[10]~feeder_combout\ : std_logic;
SIGNAL \prob_1[10]~input_o\ : std_logic;
SIGNAL \mean0|Add2~34\ : std_logic;
SIGNAL \mean0|Add2~37_sumout\ : std_logic;
SIGNAL \mean0|c[9]~9_combout\ : std_logic;
SIGNAL \prob_2[11]~input_o\ : std_logic;
SIGNAL \prob_1[11]~input_o\ : std_logic;
SIGNAL \mean0|Add2~38\ : std_logic;
SIGNAL \mean0|Add2~41_sumout\ : std_logic;
SIGNAL \mean0|c[10]~10_combout\ : std_logic;
SIGNAL \prob_1[12]~input_o\ : std_logic;
SIGNAL \prob_2[12]~input_o\ : std_logic;
SIGNAL \mean0|Add2~42\ : std_logic;
SIGNAL \mean0|Add2~45_sumout\ : std_logic;
SIGNAL \decision0|LessThan0~0_combout\ : std_logic;
SIGNAL \prob_2[13]~input_o\ : std_logic;
SIGNAL \mean0|b_stable_valid[13]~feeder_combout\ : std_logic;
SIGNAL \prob_1[13]~input_o\ : std_logic;
SIGNAL \mean0|Add2~46\ : std_logic;
SIGNAL \mean0|Add2~49_sumout\ : std_logic;
SIGNAL \mean0|c[12]~11_combout\ : std_logic;
SIGNAL \prob_1[14]~input_o\ : std_logic;
SIGNAL \prob_2[14]~input_o\ : std_logic;
SIGNAL \mean0|b_stable_valid[14]~feeder_combout\ : std_logic;
SIGNAL \mean0|Add2~50\ : std_logic;
SIGNAL \mean0|Add2~53_sumout\ : std_logic;
SIGNAL \mean0|c[13]~12_combout\ : std_logic;
SIGNAL \prob_1[15]~input_o\ : std_logic;
SIGNAL \prob_2[15]~input_o\ : std_logic;
SIGNAL \mean0|b_stable_valid[15]~feeder_combout\ : std_logic;
SIGNAL \mean0|Add2~54\ : std_logic;
SIGNAL \mean0|Add2~57_sumout\ : std_logic;
SIGNAL \mean0|c[14]~13_combout\ : std_logic;
SIGNAL \prob_1[16]~input_o\ : std_logic;
SIGNAL \prob_2[16]~input_o\ : std_logic;
SIGNAL \mean0|b_stable_valid[16]~feeder_combout\ : std_logic;
SIGNAL \mean0|Add2~58\ : std_logic;
SIGNAL \mean0|Add2~61_sumout\ : std_logic;
SIGNAL \mean0|c[15]~14_combout\ : std_logic;
SIGNAL \prob_1[17]~input_o\ : std_logic;
SIGNAL \prob_2[17]~input_o\ : std_logic;
SIGNAL \mean0|Add2~62\ : std_logic;
SIGNAL \mean0|Add2~65_sumout\ : std_logic;
SIGNAL \mean0|c[16]~15_combout\ : std_logic;
SIGNAL \prob_1[18]~input_o\ : std_logic;
SIGNAL \prob_2[18]~input_o\ : std_logic;
SIGNAL \mean0|Add2~66\ : std_logic;
SIGNAL \mean0|Add2~69_sumout\ : std_logic;
SIGNAL \mean0|c[17]~16_combout\ : std_logic;
SIGNAL \prob_2[19]~input_o\ : std_logic;
SIGNAL \prob_1[19]~input_o\ : std_logic;
SIGNAL \mean0|Add2~70\ : std_logic;
SIGNAL \mean0|Add2~73_sumout\ : std_logic;
SIGNAL \mean0|c[18]~17_combout\ : std_logic;
SIGNAL \prob_2[20]~input_o\ : std_logic;
SIGNAL \mean0|b_stable_valid[20]~feeder_combout\ : std_logic;
SIGNAL \prob_1[20]~input_o\ : std_logic;
SIGNAL \mean0|Add2~74\ : std_logic;
SIGNAL \mean0|Add2~77_sumout\ : std_logic;
SIGNAL \mean0|c[19]~18_combout\ : std_logic;
SIGNAL \prob_1[21]~input_o\ : std_logic;
SIGNAL \prob_2[21]~input_o\ : std_logic;
SIGNAL \mean0|Add2~78\ : std_logic;
SIGNAL \mean0|Add2~81_sumout\ : std_logic;
SIGNAL \mean0|c[20]~19_combout\ : std_logic;
SIGNAL \prob_1[22]~input_o\ : std_logic;
SIGNAL \prob_2[22]~input_o\ : std_logic;
SIGNAL \mean0|Add2~82\ : std_logic;
SIGNAL \mean0|Add2~85_sumout\ : std_logic;
SIGNAL \mean0|c[21]~20_combout\ : std_logic;
SIGNAL \prob_1[23]~input_o\ : std_logic;
SIGNAL \prob_2[23]~input_o\ : std_logic;
SIGNAL \mean0|b_stable_valid[23]~feeder_combout\ : std_logic;
SIGNAL \mean0|Add2~86\ : std_logic;
SIGNAL \mean0|Add2~89_sumout\ : std_logic;
SIGNAL \mean0|c[22]~21_combout\ : std_logic;
SIGNAL \decision0|LessThan0~1_combout\ : std_logic;
SIGNAL \decision0|LessThan0~2_combout\ : std_logic;
SIGNAL \decision0|LessThan0~3_combout\ : std_logic;
SIGNAL \mean0|loss_comm_count_b\ : std_logic_vector(30 DOWNTO 0);
SIGNAL \mean0|loss_comm_count_a\ : std_logic_vector(30 DOWNTO 0);
SIGNAL \mean0|b_stable_valid\ : std_logic_vector(23 DOWNTO 0);
SIGNAL \mean0|a_stable_valid\ : std_logic_vector(23 DOWNTO 0);
SIGNAL \ALT_INV_prob_2[23]~input_o\ : std_logic;
SIGNAL \ALT_INV_prob_2[20]~input_o\ : std_logic;
SIGNAL \ALT_INV_prob_2[16]~input_o\ : std_logic;
SIGNAL \ALT_INV_prob_2[15]~input_o\ : std_logic;
SIGNAL \ALT_INV_prob_2[14]~input_o\ : std_logic;
SIGNAL \ALT_INV_prob_2[13]~input_o\ : std_logic;
SIGNAL \ALT_INV_prob_2[10]~input_o\ : std_logic;
SIGNAL \ALT_INV_prob_2[9]~input_o\ : std_logic;
SIGNAL \ALT_INV_prob_2[8]~input_o\ : std_logic;
SIGNAL \ALT_INV_prob_2[6]~input_o\ : std_logic;
SIGNAL \ALT_INV_prob_2[4]~input_o\ : std_logic;
SIGNAL \ALT_INV_prob_2[2]~input_o\ : std_logic;
SIGNAL \ALT_INV_prob_valid_1~input_o\ : std_logic;
SIGNAL \ALT_INV_prob_valid_2~input_o\ : std_logic;
SIGNAL \mean0|ALT_INV_process_0~0_combout\ : std_logic;
SIGNAL \mean0|ALT_INV_Equal1~5_combout\ : std_logic;
SIGNAL \mean0|ALT_INV_Equal1~4_combout\ : std_logic;
SIGNAL \mean0|ALT_INV_Equal1~3_combout\ : std_logic;
SIGNAL \mean0|ALT_INV_Equal1~2_combout\ : std_logic;
SIGNAL \mean0|ALT_INV_Equal1~1_combout\ : std_logic;
SIGNAL \mean0|ALT_INV_Equal1~0_combout\ : std_logic;
SIGNAL \mean0|ALT_INV_Equal0~5_combout\ : std_logic;
SIGNAL \mean0|ALT_INV_Equal0~4_combout\ : std_logic;
SIGNAL \mean0|ALT_INV_Equal0~3_combout\ : std_logic;
SIGNAL \mean0|ALT_INV_Equal0~2_combout\ : std_logic;
SIGNAL \mean0|ALT_INV_Equal0~1_combout\ : std_logic;
SIGNAL \mean0|ALT_INV_Equal0~0_combout\ : std_logic;
SIGNAL \decision0|ALT_INV_LessThan0~3_combout\ : std_logic;
SIGNAL \decision0|ALT_INV_LessThan0~2_combout\ : std_logic;
SIGNAL \decision0|ALT_INV_LessThan0~1_combout\ : std_logic;
SIGNAL \mean0|ALT_INV_init_flag_a~q\ : std_logic;
SIGNAL \mean0|ALT_INV_init_flag_b~q\ : std_logic;
SIGNAL \mean0|ALT_INV_a_stable_valid\ : std_logic_vector(23 DOWNTO 0);
SIGNAL \mean0|ALT_INV_b_stable_valid\ : std_logic_vector(23 DOWNTO 0);
SIGNAL \mean0|ALT_INV_loss_comm_count_b\ : std_logic_vector(30 DOWNTO 0);
SIGNAL \mean0|ALT_INV_loss_comm_count_a\ : std_logic_vector(30 DOWNTO 0);
SIGNAL \mean0|ALT_INV_Add2~89_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~85_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~81_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~77_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~73_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~69_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~65_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~61_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~57_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~53_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~49_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~45_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~41_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~37_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~33_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~29_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~25_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~21_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~17_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~13_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~9_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~5_sumout\ : std_logic;
SIGNAL \mean0|ALT_INV_Add2~1_sumout\ : std_logic;

BEGIN

ww_prob_1 <= prob_1;
ww_prob_2 <= prob_2;
ww_prob_valid_1 <= prob_valid_1;
ww_prob_valid_2 <= prob_valid_2;
ww_clk_voting <= clk_voting;
prob_mean <= ww_prob_mean;
prediction <= ww_prediction;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;
\ALT_INV_prob_2[23]~input_o\ <= NOT \prob_2[23]~input_o\;
\ALT_INV_prob_2[20]~input_o\ <= NOT \prob_2[20]~input_o\;
\ALT_INV_prob_2[16]~input_o\ <= NOT \prob_2[16]~input_o\;
\ALT_INV_prob_2[15]~input_o\ <= NOT \prob_2[15]~input_o\;
\ALT_INV_prob_2[14]~input_o\ <= NOT \prob_2[14]~input_o\;
\ALT_INV_prob_2[13]~input_o\ <= NOT \prob_2[13]~input_o\;
\ALT_INV_prob_2[10]~input_o\ <= NOT \prob_2[10]~input_o\;
\ALT_INV_prob_2[9]~input_o\ <= NOT \prob_2[9]~input_o\;
\ALT_INV_prob_2[8]~input_o\ <= NOT \prob_2[8]~input_o\;
\ALT_INV_prob_2[6]~input_o\ <= NOT \prob_2[6]~input_o\;
\ALT_INV_prob_2[4]~input_o\ <= NOT \prob_2[4]~input_o\;
\ALT_INV_prob_2[2]~input_o\ <= NOT \prob_2[2]~input_o\;
\ALT_INV_prob_valid_1~input_o\ <= NOT \prob_valid_1~input_o\;
\ALT_INV_prob_valid_2~input_o\ <= NOT \prob_valid_2~input_o\;
\mean0|ALT_INV_process_0~0_combout\ <= NOT \mean0|process_0~0_combout\;
\mean0|ALT_INV_Equal1~5_combout\ <= NOT \mean0|Equal1~5_combout\;
\mean0|ALT_INV_Equal1~4_combout\ <= NOT \mean0|Equal1~4_combout\;
\mean0|ALT_INV_Equal1~3_combout\ <= NOT \mean0|Equal1~3_combout\;
\mean0|ALT_INV_Equal1~2_combout\ <= NOT \mean0|Equal1~2_combout\;
\mean0|ALT_INV_Equal1~1_combout\ <= NOT \mean0|Equal1~1_combout\;
\mean0|ALT_INV_Equal1~0_combout\ <= NOT \mean0|Equal1~0_combout\;
\mean0|ALT_INV_Equal0~5_combout\ <= NOT \mean0|Equal0~5_combout\;
\mean0|ALT_INV_Equal0~4_combout\ <= NOT \mean0|Equal0~4_combout\;
\mean0|ALT_INV_Equal0~3_combout\ <= NOT \mean0|Equal0~3_combout\;
\mean0|ALT_INV_Equal0~2_combout\ <= NOT \mean0|Equal0~2_combout\;
\mean0|ALT_INV_Equal0~1_combout\ <= NOT \mean0|Equal0~1_combout\;
\mean0|ALT_INV_Equal0~0_combout\ <= NOT \mean0|Equal0~0_combout\;
\decision0|ALT_INV_LessThan0~3_combout\ <= NOT \decision0|LessThan0~3_combout\;
\decision0|ALT_INV_LessThan0~2_combout\ <= NOT \decision0|LessThan0~2_combout\;
\decision0|ALT_INV_LessThan0~1_combout\ <= NOT \decision0|LessThan0~1_combout\;
\mean0|ALT_INV_init_flag_a~q\ <= NOT \mean0|init_flag_a~q\;
\mean0|ALT_INV_init_flag_b~q\ <= NOT \mean0|init_flag_b~q\;
\mean0|ALT_INV_a_stable_valid\(0) <= NOT \mean0|a_stable_valid\(0);
\mean0|ALT_INV_b_stable_valid\(0) <= NOT \mean0|b_stable_valid\(0);
\mean0|ALT_INV_a_stable_valid\(23) <= NOT \mean0|a_stable_valid\(23);
\mean0|ALT_INV_b_stable_valid\(23) <= NOT \mean0|b_stable_valid\(23);
\mean0|ALT_INV_a_stable_valid\(22) <= NOT \mean0|a_stable_valid\(22);
\mean0|ALT_INV_b_stable_valid\(22) <= NOT \mean0|b_stable_valid\(22);
\mean0|ALT_INV_a_stable_valid\(21) <= NOT \mean0|a_stable_valid\(21);
\mean0|ALT_INV_b_stable_valid\(21) <= NOT \mean0|b_stable_valid\(21);
\mean0|ALT_INV_a_stable_valid\(20) <= NOT \mean0|a_stable_valid\(20);
\mean0|ALT_INV_b_stable_valid\(20) <= NOT \mean0|b_stable_valid\(20);
\mean0|ALT_INV_a_stable_valid\(19) <= NOT \mean0|a_stable_valid\(19);
\mean0|ALT_INV_b_stable_valid\(19) <= NOT \mean0|b_stable_valid\(19);
\mean0|ALT_INV_a_stable_valid\(18) <= NOT \mean0|a_stable_valid\(18);
\mean0|ALT_INV_b_stable_valid\(18) <= NOT \mean0|b_stable_valid\(18);
\mean0|ALT_INV_a_stable_valid\(17) <= NOT \mean0|a_stable_valid\(17);
\mean0|ALT_INV_b_stable_valid\(17) <= NOT \mean0|b_stable_valid\(17);
\mean0|ALT_INV_a_stable_valid\(16) <= NOT \mean0|a_stable_valid\(16);
\mean0|ALT_INV_b_stable_valid\(16) <= NOT \mean0|b_stable_valid\(16);
\mean0|ALT_INV_a_stable_valid\(15) <= NOT \mean0|a_stable_valid\(15);
\mean0|ALT_INV_b_stable_valid\(15) <= NOT \mean0|b_stable_valid\(15);
\mean0|ALT_INV_a_stable_valid\(14) <= NOT \mean0|a_stable_valid\(14);
\mean0|ALT_INV_b_stable_valid\(14) <= NOT \mean0|b_stable_valid\(14);
\mean0|ALT_INV_a_stable_valid\(13) <= NOT \mean0|a_stable_valid\(13);
\mean0|ALT_INV_b_stable_valid\(13) <= NOT \mean0|b_stable_valid\(13);
\mean0|ALT_INV_a_stable_valid\(12) <= NOT \mean0|a_stable_valid\(12);
\mean0|ALT_INV_b_stable_valid\(12) <= NOT \mean0|b_stable_valid\(12);
\mean0|ALT_INV_a_stable_valid\(11) <= NOT \mean0|a_stable_valid\(11);
\mean0|ALT_INV_b_stable_valid\(11) <= NOT \mean0|b_stable_valid\(11);
\mean0|ALT_INV_a_stable_valid\(10) <= NOT \mean0|a_stable_valid\(10);
\mean0|ALT_INV_b_stable_valid\(10) <= NOT \mean0|b_stable_valid\(10);
\mean0|ALT_INV_a_stable_valid\(9) <= NOT \mean0|a_stable_valid\(9);
\mean0|ALT_INV_b_stable_valid\(9) <= NOT \mean0|b_stable_valid\(9);
\mean0|ALT_INV_a_stable_valid\(8) <= NOT \mean0|a_stable_valid\(8);
\mean0|ALT_INV_b_stable_valid\(8) <= NOT \mean0|b_stable_valid\(8);
\mean0|ALT_INV_a_stable_valid\(7) <= NOT \mean0|a_stable_valid\(7);
\mean0|ALT_INV_b_stable_valid\(7) <= NOT \mean0|b_stable_valid\(7);
\mean0|ALT_INV_a_stable_valid\(6) <= NOT \mean0|a_stable_valid\(6);
\mean0|ALT_INV_b_stable_valid\(6) <= NOT \mean0|b_stable_valid\(6);
\mean0|ALT_INV_a_stable_valid\(5) <= NOT \mean0|a_stable_valid\(5);
\mean0|ALT_INV_b_stable_valid\(5) <= NOT \mean0|b_stable_valid\(5);
\mean0|ALT_INV_a_stable_valid\(4) <= NOT \mean0|a_stable_valid\(4);
\mean0|ALT_INV_b_stable_valid\(4) <= NOT \mean0|b_stable_valid\(4);
\mean0|ALT_INV_a_stable_valid\(3) <= NOT \mean0|a_stable_valid\(3);
\mean0|ALT_INV_b_stable_valid\(3) <= NOT \mean0|b_stable_valid\(3);
\mean0|ALT_INV_a_stable_valid\(2) <= NOT \mean0|a_stable_valid\(2);
\mean0|ALT_INV_b_stable_valid\(2) <= NOT \mean0|b_stable_valid\(2);
\mean0|ALT_INV_a_stable_valid\(1) <= NOT \mean0|a_stable_valid\(1);
\mean0|ALT_INV_b_stable_valid\(1) <= NOT \mean0|b_stable_valid\(1);
\mean0|ALT_INV_loss_comm_count_b\(29) <= NOT \mean0|loss_comm_count_b\(29);
\mean0|ALT_INV_loss_comm_count_b\(28) <= NOT \mean0|loss_comm_count_b\(28);
\mean0|ALT_INV_loss_comm_count_b\(27) <= NOT \mean0|loss_comm_count_b\(27);
\mean0|ALT_INV_loss_comm_count_b\(26) <= NOT \mean0|loss_comm_count_b\(26);
\mean0|ALT_INV_loss_comm_count_b\(25) <= NOT \mean0|loss_comm_count_b\(25);
\mean0|ALT_INV_loss_comm_count_b\(23) <= NOT \mean0|loss_comm_count_b\(23);
\mean0|ALT_INV_loss_comm_count_b\(22) <= NOT \mean0|loss_comm_count_b\(22);
\mean0|ALT_INV_loss_comm_count_b\(21) <= NOT \mean0|loss_comm_count_b\(21);
\mean0|ALT_INV_loss_comm_count_b\(19) <= NOT \mean0|loss_comm_count_b\(19);
\mean0|ALT_INV_loss_comm_count_b\(14) <= NOT \mean0|loss_comm_count_b\(14);
\mean0|ALT_INV_loss_comm_count_b\(4) <= NOT \mean0|loss_comm_count_b\(4);
\mean0|ALT_INV_loss_comm_count_b\(3) <= NOT \mean0|loss_comm_count_b\(3);
\mean0|ALT_INV_loss_comm_count_b\(2) <= NOT \mean0|loss_comm_count_b\(2);
\mean0|ALT_INV_loss_comm_count_b\(0) <= NOT \mean0|loss_comm_count_b\(0);
\mean0|ALT_INV_loss_comm_count_b\(1) <= NOT \mean0|loss_comm_count_b\(1);
\mean0|ALT_INV_loss_comm_count_b\(20) <= NOT \mean0|loss_comm_count_b\(20);
\mean0|ALT_INV_loss_comm_count_b\(10) <= NOT \mean0|loss_comm_count_b\(10);
\mean0|ALT_INV_loss_comm_count_b\(9) <= NOT \mean0|loss_comm_count_b\(9);
\mean0|ALT_INV_loss_comm_count_b\(8) <= NOT \mean0|loss_comm_count_b\(8);
\mean0|ALT_INV_loss_comm_count_b\(7) <= NOT \mean0|loss_comm_count_b\(7);
\mean0|ALT_INV_loss_comm_count_b\(6) <= NOT \mean0|loss_comm_count_b\(6);
\mean0|ALT_INV_loss_comm_count_b\(5) <= NOT \mean0|loss_comm_count_b\(5);
\mean0|ALT_INV_loss_comm_count_b\(30) <= NOT \mean0|loss_comm_count_b\(30);
\mean0|ALT_INV_loss_comm_count_b\(24) <= NOT \mean0|loss_comm_count_b\(24);
\mean0|ALT_INV_loss_comm_count_b\(17) <= NOT \mean0|loss_comm_count_b\(17);
\mean0|ALT_INV_loss_comm_count_b\(16) <= NOT \mean0|loss_comm_count_b\(16);
\mean0|ALT_INV_loss_comm_count_b\(15) <= NOT \mean0|loss_comm_count_b\(15);
\mean0|ALT_INV_loss_comm_count_b\(13) <= NOT \mean0|loss_comm_count_b\(13);
\mean0|ALT_INV_loss_comm_count_b\(12) <= NOT \mean0|loss_comm_count_b\(12);
\mean0|ALT_INV_loss_comm_count_b\(11) <= NOT \mean0|loss_comm_count_b\(11);
\mean0|ALT_INV_loss_comm_count_a\(13) <= NOT \mean0|loss_comm_count_a\(13);
\mean0|ALT_INV_loss_comm_count_a\(4) <= NOT \mean0|loss_comm_count_a\(4);
\mean0|ALT_INV_loss_comm_count_a\(15) <= NOT \mean0|loss_comm_count_a\(15);
\mean0|ALT_INV_loss_comm_count_a\(16) <= NOT \mean0|loss_comm_count_a\(16);
\mean0|ALT_INV_loss_comm_count_a\(17) <= NOT \mean0|loss_comm_count_a\(17);
\mean0|ALT_INV_loss_comm_count_a\(18) <= NOT \mean0|loss_comm_count_a\(18);
\mean0|ALT_INV_loss_comm_count_a\(19) <= NOT \mean0|loss_comm_count_a\(19);
\mean0|ALT_INV_loss_comm_count_a\(20) <= NOT \mean0|loss_comm_count_a\(20);
\mean0|ALT_INV_loss_comm_count_a\(21) <= NOT \mean0|loss_comm_count_a\(21);
\mean0|ALT_INV_loss_comm_count_a\(22) <= NOT \mean0|loss_comm_count_a\(22);
\mean0|ALT_INV_loss_comm_count_a\(23) <= NOT \mean0|loss_comm_count_a\(23);
\mean0|ALT_INV_loss_comm_count_a\(14) <= NOT \mean0|loss_comm_count_a\(14);
\mean0|ALT_INV_loss_comm_count_a\(7) <= NOT \mean0|loss_comm_count_a\(7);
\mean0|ALT_INV_loss_comm_count_a\(25) <= NOT \mean0|loss_comm_count_a\(25);
\mean0|ALT_INV_loss_comm_count_a\(8) <= NOT \mean0|loss_comm_count_a\(8);
\mean0|ALT_INV_loss_comm_count_a\(9) <= NOT \mean0|loss_comm_count_a\(9);
\mean0|ALT_INV_loss_comm_count_a\(10) <= NOT \mean0|loss_comm_count_a\(10);
\mean0|ALT_INV_loss_comm_count_a\(12) <= NOT \mean0|loss_comm_count_a\(12);
\mean0|ALT_INV_loss_comm_count_a\(1) <= NOT \mean0|loss_comm_count_a\(1);
\mean0|ALT_INV_loss_comm_count_a\(2) <= NOT \mean0|loss_comm_count_a\(2);
\mean0|ALT_INV_loss_comm_count_a\(3) <= NOT \mean0|loss_comm_count_a\(3);
\mean0|ALT_INV_loss_comm_count_a\(0) <= NOT \mean0|loss_comm_count_a\(0);
\mean0|ALT_INV_loss_comm_count_a\(5) <= NOT \mean0|loss_comm_count_a\(5);
\mean0|ALT_INV_loss_comm_count_a\(6) <= NOT \mean0|loss_comm_count_a\(6);
\mean0|ALT_INV_loss_comm_count_a\(27) <= NOT \mean0|loss_comm_count_a\(27);
\mean0|ALT_INV_loss_comm_count_a\(29) <= NOT \mean0|loss_comm_count_a\(29);
\mean0|ALT_INV_loss_comm_count_a\(30) <= NOT \mean0|loss_comm_count_a\(30);
\mean0|ALT_INV_loss_comm_count_a\(11) <= NOT \mean0|loss_comm_count_a\(11);
\mean0|ALT_INV_loss_comm_count_a\(24) <= NOT \mean0|loss_comm_count_a\(24);
\mean0|ALT_INV_loss_comm_count_a\(28) <= NOT \mean0|loss_comm_count_a\(28);
\mean0|ALT_INV_loss_comm_count_a\(26) <= NOT \mean0|loss_comm_count_a\(26);
\mean0|ALT_INV_loss_comm_count_b\(18) <= NOT \mean0|loss_comm_count_b\(18);
\mean0|ALT_INV_Add2~89_sumout\ <= NOT \mean0|Add2~89_sumout\;
\mean0|ALT_INV_Add2~85_sumout\ <= NOT \mean0|Add2~85_sumout\;
\mean0|ALT_INV_Add2~81_sumout\ <= NOT \mean0|Add2~81_sumout\;
\mean0|ALT_INV_Add2~77_sumout\ <= NOT \mean0|Add2~77_sumout\;
\mean0|ALT_INV_Add2~73_sumout\ <= NOT \mean0|Add2~73_sumout\;
\mean0|ALT_INV_Add2~69_sumout\ <= NOT \mean0|Add2~69_sumout\;
\mean0|ALT_INV_Add2~65_sumout\ <= NOT \mean0|Add2~65_sumout\;
\mean0|ALT_INV_Add2~61_sumout\ <= NOT \mean0|Add2~61_sumout\;
\mean0|ALT_INV_Add2~57_sumout\ <= NOT \mean0|Add2~57_sumout\;
\mean0|ALT_INV_Add2~53_sumout\ <= NOT \mean0|Add2~53_sumout\;
\mean0|ALT_INV_Add2~49_sumout\ <= NOT \mean0|Add2~49_sumout\;
\mean0|ALT_INV_Add2~45_sumout\ <= NOT \mean0|Add2~45_sumout\;
\mean0|ALT_INV_Add2~41_sumout\ <= NOT \mean0|Add2~41_sumout\;
\mean0|ALT_INV_Add2~37_sumout\ <= NOT \mean0|Add2~37_sumout\;
\mean0|ALT_INV_Add2~33_sumout\ <= NOT \mean0|Add2~33_sumout\;
\mean0|ALT_INV_Add2~29_sumout\ <= NOT \mean0|Add2~29_sumout\;
\mean0|ALT_INV_Add2~25_sumout\ <= NOT \mean0|Add2~25_sumout\;
\mean0|ALT_INV_Add2~21_sumout\ <= NOT \mean0|Add2~21_sumout\;
\mean0|ALT_INV_Add2~17_sumout\ <= NOT \mean0|Add2~17_sumout\;
\mean0|ALT_INV_Add2~13_sumout\ <= NOT \mean0|Add2~13_sumout\;
\mean0|ALT_INV_Add2~9_sumout\ <= NOT \mean0|Add2~9_sumout\;
\mean0|ALT_INV_Add2~5_sumout\ <= NOT \mean0|Add2~5_sumout\;
\mean0|ALT_INV_Add2~1_sumout\ <= NOT \mean0|Add2~1_sumout\;

-- Location: IOOBUF_X24_Y0_N19
\prob_mean[0]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[0]~0_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(0));

-- Location: IOOBUF_X12_Y0_N2
\prob_mean[1]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[1]~1_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(1));

-- Location: IOOBUF_X24_Y0_N53
\prob_mean[2]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[2]~2_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(2));

-- Location: IOOBUF_X34_Y0_N36
\prob_mean[3]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[3]~3_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(3));

-- Location: IOOBUF_X29_Y0_N53
\prob_mean[4]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[4]~4_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(4));

-- Location: IOOBUF_X23_Y0_N59
\prob_mean[5]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[5]~5_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(5));

-- Location: IOOBUF_X12_Y0_N19
\prob_mean[6]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[6]~6_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(6));

-- Location: IOOBUF_X0_Y21_N39
\prob_mean[7]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[7]~7_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(7));

-- Location: IOOBUF_X24_Y0_N2
\prob_mean[8]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[8]~8_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(8));

-- Location: IOOBUF_X22_Y0_N36
\prob_mean[9]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[9]~9_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(9));

-- Location: IOOBUF_X11_Y0_N36
\prob_mean[10]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[10]~10_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(10));

-- Location: IOOBUF_X14_Y0_N19
\prob_mean[11]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \decision0|LessThan0~0_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(11));

-- Location: IOOBUF_X22_Y0_N19
\prob_mean[12]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[12]~11_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(12));

-- Location: IOOBUF_X29_Y0_N36
\prob_mean[13]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[13]~12_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(13));

-- Location: IOOBUF_X23_Y0_N93
\prob_mean[14]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[14]~13_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(14));

-- Location: IOOBUF_X33_Y0_N42
\prob_mean[15]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[15]~14_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(15));

-- Location: IOOBUF_X23_Y0_N76
\prob_mean[16]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[16]~15_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(16));

-- Location: IOOBUF_X18_Y0_N19
\prob_mean[17]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[17]~16_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(17));

-- Location: IOOBUF_X22_Y0_N2
\prob_mean[18]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[18]~17_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(18));

-- Location: IOOBUF_X22_Y0_N53
\prob_mean[19]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[19]~18_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(19));

-- Location: IOOBUF_X24_Y0_N36
\prob_mean[20]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[20]~19_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(20));

-- Location: IOOBUF_X23_Y0_N42
\prob_mean[21]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[21]~20_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(21));

-- Location: IOOBUF_X29_Y0_N19
\prob_mean[22]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[22]~21_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(22));

-- Location: IOOBUF_X29_Y0_N2
\prob_mean[23]~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \mean0|c[22]~21_combout\,
	devoe => ww_devoe,
	o => ww_prob_mean(23));

-- Location: IOOBUF_X12_Y0_N53
\prediction~output\ : cyclonev_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false",
	shift_series_termination_control => "false")
-- pragma translate_on
PORT MAP (
	i => \decision0|ALT_INV_LessThan0~3_combout\,
	devoe => ww_devoe,
	o => ww_prediction);

-- Location: IOIBUF_X54_Y18_N61
\clk_voting~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_clk_voting,
	o => \clk_voting~input_o\);

-- Location: CLKCTRL_G10
\clk_voting~inputCLKENA0\ : cyclonev_clkena
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	disable_mode => "low",
	ena_register_mode => "always enabled",
	ena_register_power_up => "high",
	test_syn => "high")
-- pragma translate_on
PORT MAP (
	inclk => \clk_voting~input_o\,
	outclk => \clk_voting~inputCLKENA0_outclk\);

-- Location: LABCELL_X12_Y9_N0
\mean0|Add1~69\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~69_sumout\ = SUM(( \mean0|loss_comm_count_b\(0) ) + ( VCC ) + ( !VCC ))
-- \mean0|Add1~70\ = CARRY(( \mean0|loss_comm_count_b\(0) ) + ( VCC ) + ( !VCC ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_b\(0),
	cin => GND,
	sumout => \mean0|Add1~69_sumout\,
	cout => \mean0|Add1~70\);

-- Location: IOIBUF_X12_Y0_N35
\prob_valid_2~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_valid_2,
	o => \prob_valid_2~input_o\);

-- Location: LABCELL_X14_Y8_N0
\mean0|Add0~37\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~37_sumout\ = SUM(( \mean0|loss_comm_count_a\(0) ) + ( VCC ) + ( !VCC ))
-- \mean0|Add0~38\ = CARRY(( \mean0|loss_comm_count_a\(0) ) + ( VCC ) + ( !VCC ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_a\(0),
	cin => GND,
	sumout => \mean0|Add0~37_sumout\,
	cout => \mean0|Add0~38\);

-- Location: IOIBUF_X16_Y0_N58
\prob_valid_1~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_valid_1,
	o => \prob_valid_1~input_o\);

-- Location: FF_X14_Y8_N2
\mean0|loss_comm_count_a[0]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~37_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(0));

-- Location: LABCELL_X14_Y8_N3
\mean0|Add0~49\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~49_sumout\ = SUM(( \mean0|loss_comm_count_a\(1) ) + ( GND ) + ( \mean0|Add0~38\ ))
-- \mean0|Add0~50\ = CARRY(( \mean0|loss_comm_count_a\(1) ) + ( GND ) + ( \mean0|Add0~38\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_a\(1),
	cin => \mean0|Add0~38\,
	sumout => \mean0|Add0~49_sumout\,
	cout => \mean0|Add0~50\);

-- Location: FF_X14_Y8_N5
\mean0|loss_comm_count_a[1]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~49_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(1));

-- Location: LABCELL_X14_Y8_N6
\mean0|Add0~45\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~45_sumout\ = SUM(( \mean0|loss_comm_count_a\(2) ) + ( GND ) + ( \mean0|Add0~50\ ))
-- \mean0|Add0~46\ = CARRY(( \mean0|loss_comm_count_a\(2) ) + ( GND ) + ( \mean0|Add0~50\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000011001100110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_loss_comm_count_a\(2),
	cin => \mean0|Add0~50\,
	sumout => \mean0|Add0~45_sumout\,
	cout => \mean0|Add0~46\);

-- Location: FF_X14_Y8_N8
\mean0|loss_comm_count_a[2]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~45_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(2));

-- Location: LABCELL_X14_Y8_N9
\mean0|Add0~41\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~41_sumout\ = SUM(( \mean0|loss_comm_count_a\(3) ) + ( GND ) + ( \mean0|Add0~46\ ))
-- \mean0|Add0~42\ = CARRY(( \mean0|loss_comm_count_a\(3) ) + ( GND ) + ( \mean0|Add0~46\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_a\(3),
	cin => \mean0|Add0~46\,
	sumout => \mean0|Add0~41_sumout\,
	cout => \mean0|Add0~42\);

-- Location: FF_X14_Y8_N11
\mean0|loss_comm_count_a[3]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~41_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(3));

-- Location: LABCELL_X14_Y8_N12
\mean0|Add0~117\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~117_sumout\ = SUM(( \mean0|loss_comm_count_a\(4) ) + ( GND ) + ( \mean0|Add0~42\ ))
-- \mean0|Add0~118\ = CARRY(( \mean0|loss_comm_count_a\(4) ) + ( GND ) + ( \mean0|Add0~42\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000011001100110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_loss_comm_count_a\(4),
	cin => \mean0|Add0~42\,
	sumout => \mean0|Add0~117_sumout\,
	cout => \mean0|Add0~118\);

-- Location: FF_X14_Y8_N14
\mean0|loss_comm_count_a[4]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~117_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(4));

-- Location: LABCELL_X14_Y8_N15
\mean0|Add0~33\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~33_sumout\ = SUM(( \mean0|loss_comm_count_a\(5) ) + ( GND ) + ( \mean0|Add0~118\ ))
-- \mean0|Add0~34\ = CARRY(( \mean0|loss_comm_count_a\(5) ) + ( GND ) + ( \mean0|Add0~118\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_a\(5),
	cin => \mean0|Add0~118\,
	sumout => \mean0|Add0~33_sumout\,
	cout => \mean0|Add0~34\);

-- Location: FF_X14_Y8_N17
\mean0|loss_comm_count_a[5]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~33_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(5));

-- Location: LABCELL_X14_Y8_N18
\mean0|Add0~29\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~29_sumout\ = SUM(( \mean0|loss_comm_count_a\(6) ) + ( GND ) + ( \mean0|Add0~34\ ))
-- \mean0|Add0~30\ = CARRY(( \mean0|loss_comm_count_a\(6) ) + ( GND ) + ( \mean0|Add0~34\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_a\(6),
	cin => \mean0|Add0~34\,
	sumout => \mean0|Add0~29_sumout\,
	cout => \mean0|Add0~30\);

-- Location: FF_X14_Y8_N20
\mean0|loss_comm_count_a[6]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~29_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(6));

-- Location: LABCELL_X14_Y8_N21
\mean0|Add0~73\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~73_sumout\ = SUM(( \mean0|loss_comm_count_a\(7) ) + ( GND ) + ( \mean0|Add0~30\ ))
-- \mean0|Add0~74\ = CARRY(( \mean0|loss_comm_count_a\(7) ) + ( GND ) + ( \mean0|Add0~30\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_a\(7),
	cin => \mean0|Add0~30\,
	sumout => \mean0|Add0~73_sumout\,
	cout => \mean0|Add0~74\);

-- Location: FF_X14_Y8_N23
\mean0|loss_comm_count_a[7]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~73_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(7));

-- Location: LABCELL_X14_Y8_N24
\mean0|Add0~65\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~65_sumout\ = SUM(( \mean0|loss_comm_count_a\(8) ) + ( GND ) + ( \mean0|Add0~74\ ))
-- \mean0|Add0~66\ = CARRY(( \mean0|loss_comm_count_a\(8) ) + ( GND ) + ( \mean0|Add0~74\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_a\(8),
	cin => \mean0|Add0~74\,
	sumout => \mean0|Add0~65_sumout\,
	cout => \mean0|Add0~66\);

-- Location: FF_X14_Y8_N26
\mean0|loss_comm_count_a[8]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~65_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(8));

-- Location: LABCELL_X14_Y8_N27
\mean0|Add0~61\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~61_sumout\ = SUM(( \mean0|loss_comm_count_a\(9) ) + ( GND ) + ( \mean0|Add0~66\ ))
-- \mean0|Add0~62\ = CARRY(( \mean0|loss_comm_count_a\(9) ) + ( GND ) + ( \mean0|Add0~66\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_a\(9),
	cin => \mean0|Add0~66\,
	sumout => \mean0|Add0~61_sumout\,
	cout => \mean0|Add0~62\);

-- Location: FF_X14_Y8_N29
\mean0|loss_comm_count_a[9]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~61_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(9));

-- Location: LABCELL_X14_Y8_N30
\mean0|Add0~57\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~57_sumout\ = SUM(( \mean0|loss_comm_count_a\(10) ) + ( GND ) + ( \mean0|Add0~62\ ))
-- \mean0|Add0~58\ = CARRY(( \mean0|loss_comm_count_a\(10) ) + ( GND ) + ( \mean0|Add0~62\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000011001100110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_loss_comm_count_a\(10),
	cin => \mean0|Add0~62\,
	sumout => \mean0|Add0~57_sumout\,
	cout => \mean0|Add0~58\);

-- Location: FF_X14_Y8_N32
\mean0|loss_comm_count_a[10]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~57_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(10));

-- Location: LABCELL_X14_Y8_N33
\mean0|Add0~13\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~13_sumout\ = SUM(( \mean0|loss_comm_count_a\(11) ) + ( GND ) + ( \mean0|Add0~58\ ))
-- \mean0|Add0~14\ = CARRY(( \mean0|loss_comm_count_a\(11) ) + ( GND ) + ( \mean0|Add0~58\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000101010101010101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_loss_comm_count_a\(11),
	cin => \mean0|Add0~58\,
	sumout => \mean0|Add0~13_sumout\,
	cout => \mean0|Add0~14\);

-- Location: FF_X14_Y8_N35
\mean0|loss_comm_count_a[11]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~13_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(11));

-- Location: LABCELL_X14_Y8_N36
\mean0|Add0~53\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~53_sumout\ = SUM(( \mean0|loss_comm_count_a\(12) ) + ( GND ) + ( \mean0|Add0~14\ ))
-- \mean0|Add0~54\ = CARRY(( \mean0|loss_comm_count_a\(12) ) + ( GND ) + ( \mean0|Add0~14\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_a\(12),
	cin => \mean0|Add0~14\,
	sumout => \mean0|Add0~53_sumout\,
	cout => \mean0|Add0~54\);

-- Location: FF_X14_Y8_N38
\mean0|loss_comm_count_a[12]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~53_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(12));

-- Location: LABCELL_X14_Y8_N39
\mean0|Add0~121\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~121_sumout\ = SUM(( \mean0|loss_comm_count_a\(13) ) + ( GND ) + ( \mean0|Add0~54\ ))
-- \mean0|Add0~122\ = CARRY(( \mean0|loss_comm_count_a\(13) ) + ( GND ) + ( \mean0|Add0~54\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_a\(13),
	cin => \mean0|Add0~54\,
	sumout => \mean0|Add0~121_sumout\,
	cout => \mean0|Add0~122\);

-- Location: FF_X14_Y8_N41
\mean0|loss_comm_count_a[13]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~121_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(13));

-- Location: LABCELL_X14_Y8_N42
\mean0|Add0~77\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~77_sumout\ = SUM(( \mean0|loss_comm_count_a\(14) ) + ( GND ) + ( \mean0|Add0~122\ ))
-- \mean0|Add0~78\ = CARRY(( \mean0|loss_comm_count_a\(14) ) + ( GND ) + ( \mean0|Add0~122\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000011001100110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_loss_comm_count_a\(14),
	cin => \mean0|Add0~122\,
	sumout => \mean0|Add0~77_sumout\,
	cout => \mean0|Add0~78\);

-- Location: FF_X14_Y8_N44
\mean0|loss_comm_count_a[14]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~77_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(14));

-- Location: LABCELL_X14_Y8_N45
\mean0|Add0~113\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~113_sumout\ = SUM(( \mean0|loss_comm_count_a\(15) ) + ( GND ) + ( \mean0|Add0~78\ ))
-- \mean0|Add0~114\ = CARRY(( \mean0|loss_comm_count_a\(15) ) + ( GND ) + ( \mean0|Add0~78\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_a\(15),
	cin => \mean0|Add0~78\,
	sumout => \mean0|Add0~113_sumout\,
	cout => \mean0|Add0~114\);

-- Location: FF_X14_Y8_N47
\mean0|loss_comm_count_a[15]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~113_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(15));

-- Location: LABCELL_X14_Y8_N48
\mean0|Add0~109\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~109_sumout\ = SUM(( \mean0|loss_comm_count_a\(16) ) + ( GND ) + ( \mean0|Add0~114\ ))
-- \mean0|Add0~110\ = CARRY(( \mean0|loss_comm_count_a\(16) ) + ( GND ) + ( \mean0|Add0~114\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_a\(16),
	cin => \mean0|Add0~114\,
	sumout => \mean0|Add0~109_sumout\,
	cout => \mean0|Add0~110\);

-- Location: FF_X14_Y8_N50
\mean0|loss_comm_count_a[16]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~109_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(16));

-- Location: LABCELL_X14_Y8_N51
\mean0|Add0~105\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~105_sumout\ = SUM(( \mean0|loss_comm_count_a\(17) ) + ( GND ) + ( \mean0|Add0~110\ ))
-- \mean0|Add0~106\ = CARRY(( \mean0|loss_comm_count_a\(17) ) + ( GND ) + ( \mean0|Add0~110\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000101010101010101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_loss_comm_count_a\(17),
	cin => \mean0|Add0~110\,
	sumout => \mean0|Add0~105_sumout\,
	cout => \mean0|Add0~106\);

-- Location: FF_X14_Y8_N53
\mean0|loss_comm_count_a[17]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~105_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(17));

-- Location: LABCELL_X14_Y8_N54
\mean0|Add0~101\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~101_sumout\ = SUM(( \mean0|loss_comm_count_a\(18) ) + ( GND ) + ( \mean0|Add0~106\ ))
-- \mean0|Add0~102\ = CARRY(( \mean0|loss_comm_count_a\(18) ) + ( GND ) + ( \mean0|Add0~106\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_a\(18),
	cin => \mean0|Add0~106\,
	sumout => \mean0|Add0~101_sumout\,
	cout => \mean0|Add0~102\);

-- Location: FF_X14_Y8_N56
\mean0|loss_comm_count_a[18]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~101_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(18));

-- Location: LABCELL_X14_Y8_N57
\mean0|Add0~97\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~97_sumout\ = SUM(( \mean0|loss_comm_count_a\(19) ) + ( GND ) + ( \mean0|Add0~102\ ))
-- \mean0|Add0~98\ = CARRY(( \mean0|loss_comm_count_a\(19) ) + ( GND ) + ( \mean0|Add0~102\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_a\(19),
	cin => \mean0|Add0~102\,
	sumout => \mean0|Add0~97_sumout\,
	cout => \mean0|Add0~98\);

-- Location: FF_X14_Y8_N59
\mean0|loss_comm_count_a[19]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~97_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(19));

-- Location: LABCELL_X14_Y7_N0
\mean0|Add0~93\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~93_sumout\ = SUM(( \mean0|loss_comm_count_a\(20) ) + ( GND ) + ( \mean0|Add0~98\ ))
-- \mean0|Add0~94\ = CARRY(( \mean0|loss_comm_count_a\(20) ) + ( GND ) + ( \mean0|Add0~98\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_a\(20),
	cin => \mean0|Add0~98\,
	sumout => \mean0|Add0~93_sumout\,
	cout => \mean0|Add0~94\);

-- Location: FF_X14_Y7_N2
\mean0|loss_comm_count_a[20]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~93_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(20));

-- Location: LABCELL_X14_Y7_N3
\mean0|Add0~89\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~89_sumout\ = SUM(( \mean0|loss_comm_count_a\(21) ) + ( GND ) + ( \mean0|Add0~94\ ))
-- \mean0|Add0~90\ = CARRY(( \mean0|loss_comm_count_a\(21) ) + ( GND ) + ( \mean0|Add0~94\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_a\(21),
	cin => \mean0|Add0~94\,
	sumout => \mean0|Add0~89_sumout\,
	cout => \mean0|Add0~90\);

-- Location: FF_X14_Y7_N5
\mean0|loss_comm_count_a[21]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~89_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(21));

-- Location: LABCELL_X14_Y7_N6
\mean0|Add0~85\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~85_sumout\ = SUM(( \mean0|loss_comm_count_a\(22) ) + ( GND ) + ( \mean0|Add0~90\ ))
-- \mean0|Add0~86\ = CARRY(( \mean0|loss_comm_count_a\(22) ) + ( GND ) + ( \mean0|Add0~90\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000011001100110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_loss_comm_count_a\(22),
	cin => \mean0|Add0~90\,
	sumout => \mean0|Add0~85_sumout\,
	cout => \mean0|Add0~86\);

-- Location: FF_X14_Y7_N8
\mean0|loss_comm_count_a[22]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~85_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(22));

-- Location: LABCELL_X14_Y7_N9
\mean0|Add0~81\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~81_sumout\ = SUM(( \mean0|loss_comm_count_a\(23) ) + ( GND ) + ( \mean0|Add0~86\ ))
-- \mean0|Add0~82\ = CARRY(( \mean0|loss_comm_count_a\(23) ) + ( GND ) + ( \mean0|Add0~86\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_a\(23),
	cin => \mean0|Add0~86\,
	sumout => \mean0|Add0~81_sumout\,
	cout => \mean0|Add0~82\);

-- Location: FF_X14_Y7_N11
\mean0|loss_comm_count_a[23]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~81_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(23));

-- Location: LABCELL_X14_Y7_N12
\mean0|Add0~9\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~9_sumout\ = SUM(( \mean0|loss_comm_count_a\(24) ) + ( GND ) + ( \mean0|Add0~82\ ))
-- \mean0|Add0~10\ = CARRY(( \mean0|loss_comm_count_a\(24) ) + ( GND ) + ( \mean0|Add0~82\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000011001100110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_loss_comm_count_a\(24),
	cin => \mean0|Add0~82\,
	sumout => \mean0|Add0~9_sumout\,
	cout => \mean0|Add0~10\);

-- Location: FF_X14_Y7_N14
\mean0|loss_comm_count_a[24]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~9_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(24));

-- Location: LABCELL_X14_Y7_N15
\mean0|Add0~69\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~69_sumout\ = SUM(( \mean0|loss_comm_count_a\(25) ) + ( GND ) + ( \mean0|Add0~10\ ))
-- \mean0|Add0~70\ = CARRY(( \mean0|loss_comm_count_a\(25) ) + ( GND ) + ( \mean0|Add0~10\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_a\(25),
	cin => \mean0|Add0~10\,
	sumout => \mean0|Add0~69_sumout\,
	cout => \mean0|Add0~70\);

-- Location: FF_X14_Y7_N17
\mean0|loss_comm_count_a[25]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~69_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(25));

-- Location: LABCELL_X14_Y7_N18
\mean0|Add0~1\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~1_sumout\ = SUM(( \mean0|loss_comm_count_a\(26) ) + ( GND ) + ( \mean0|Add0~70\ ))
-- \mean0|Add0~2\ = CARRY(( \mean0|loss_comm_count_a\(26) ) + ( GND ) + ( \mean0|Add0~70\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_a\(26),
	cin => \mean0|Add0~70\,
	sumout => \mean0|Add0~1_sumout\,
	cout => \mean0|Add0~2\);

-- Location: FF_X14_Y7_N20
\mean0|loss_comm_count_a[26]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~1_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(26));

-- Location: MLABCELL_X13_Y8_N57
\mean0|Equal0~1\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Equal0~1_combout\ = ( \mean0|loss_comm_count_a\(3) & ( \mean0|loss_comm_count_a\(2) & ( (!\mean0|loss_comm_count_a\(1) & (!\mean0|loss_comm_count_a\(6) & (!\mean0|loss_comm_count_a\(5) & \mean0|loss_comm_count_a\(0)))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000000000000000000000010000000",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_loss_comm_count_a\(1),
	datab => \mean0|ALT_INV_loss_comm_count_a\(6),
	datac => \mean0|ALT_INV_loss_comm_count_a\(5),
	datad => \mean0|ALT_INV_loss_comm_count_a\(0),
	datae => \mean0|ALT_INV_loss_comm_count_a\(3),
	dataf => \mean0|ALT_INV_loss_comm_count_a\(2),
	combout => \mean0|Equal0~1_combout\);

-- Location: MLABCELL_X13_Y8_N36
\mean0|Equal0~4\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Equal0~4_combout\ = ( !\mean0|loss_comm_count_a\(18) & ( !\mean0|loss_comm_count_a\(13) & ( (!\mean0|loss_comm_count_a\(17) & (!\mean0|loss_comm_count_a\(16) & (!\mean0|loss_comm_count_a\(15) & \mean0|loss_comm_count_a\(4)))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000010000000000000000000000000000000000000000000000000000000",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_loss_comm_count_a\(17),
	datab => \mean0|ALT_INV_loss_comm_count_a\(16),
	datac => \mean0|ALT_INV_loss_comm_count_a\(15),
	datad => \mean0|ALT_INV_loss_comm_count_a\(4),
	datae => \mean0|ALT_INV_loss_comm_count_a\(18),
	dataf => \mean0|ALT_INV_loss_comm_count_a\(13),
	combout => \mean0|Equal0~4_combout\);

-- Location: MLABCELL_X13_Y8_N12
\mean0|Equal0~2\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Equal0~2_combout\ = ( !\mean0|loss_comm_count_a\(9) & ( !\mean0|loss_comm_count_a\(25) & ( (!\mean0|loss_comm_count_a\(10) & (!\mean0|loss_comm_count_a\(8) & (!\mean0|loss_comm_count_a\(7) & !\mean0|loss_comm_count_a\(12)))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "1000000000000000000000000000000000000000000000000000000000000000",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_loss_comm_count_a\(10),
	datab => \mean0|ALT_INV_loss_comm_count_a\(8),
	datac => \mean0|ALT_INV_loss_comm_count_a\(7),
	datad => \mean0|ALT_INV_loss_comm_count_a\(12),
	datae => \mean0|ALT_INV_loss_comm_count_a\(9),
	dataf => \mean0|ALT_INV_loss_comm_count_a\(25),
	combout => \mean0|Equal0~2_combout\);

-- Location: MLABCELL_X13_Y8_N0
\mean0|Equal0~3\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Equal0~3_combout\ = ( !\mean0|loss_comm_count_a\(21) & ( !\mean0|loss_comm_count_a\(23) & ( (!\mean0|loss_comm_count_a\(20) & (!\mean0|loss_comm_count_a\(19) & (!\mean0|loss_comm_count_a\(22) & !\mean0|loss_comm_count_a\(14)))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "1000000000000000000000000000000000000000000000000000000000000000",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_loss_comm_count_a\(20),
	datab => \mean0|ALT_INV_loss_comm_count_a\(19),
	datac => \mean0|ALT_INV_loss_comm_count_a\(22),
	datad => \mean0|ALT_INV_loss_comm_count_a\(14),
	datae => \mean0|ALT_INV_loss_comm_count_a\(21),
	dataf => \mean0|ALT_INV_loss_comm_count_a\(23),
	combout => \mean0|Equal0~3_combout\);

-- Location: LABCELL_X14_Y7_N21
\mean0|Add0~25\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~25_sumout\ = SUM(( \mean0|loss_comm_count_a\(27) ) + ( GND ) + ( \mean0|Add0~2\ ))
-- \mean0|Add0~26\ = CARRY(( \mean0|loss_comm_count_a\(27) ) + ( GND ) + ( \mean0|Add0~2\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_a\(27),
	cin => \mean0|Add0~2\,
	sumout => \mean0|Add0~25_sumout\,
	cout => \mean0|Add0~26\);

-- Location: FF_X14_Y7_N23
\mean0|loss_comm_count_a[27]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~25_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(27));

-- Location: LABCELL_X14_Y7_N24
\mean0|Add0~5\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~5_sumout\ = SUM(( \mean0|loss_comm_count_a\(28) ) + ( GND ) + ( \mean0|Add0~26\ ))
-- \mean0|Add0~6\ = CARRY(( \mean0|loss_comm_count_a\(28) ) + ( GND ) + ( \mean0|Add0~26\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_a\(28),
	cin => \mean0|Add0~26\,
	sumout => \mean0|Add0~5_sumout\,
	cout => \mean0|Add0~6\);

-- Location: FF_X14_Y7_N26
\mean0|loss_comm_count_a[28]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~5_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(28));

-- Location: LABCELL_X14_Y7_N27
\mean0|Add0~21\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~21_sumout\ = SUM(( \mean0|loss_comm_count_a\(29) ) + ( GND ) + ( \mean0|Add0~6\ ))
-- \mean0|Add0~22\ = CARRY(( \mean0|loss_comm_count_a\(29) ) + ( GND ) + ( \mean0|Add0~6\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_a\(29),
	cin => \mean0|Add0~6\,
	sumout => \mean0|Add0~21_sumout\,
	cout => \mean0|Add0~22\);

-- Location: FF_X14_Y7_N29
\mean0|loss_comm_count_a[29]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~21_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(29));

-- Location: LABCELL_X14_Y7_N30
\mean0|Add0~17\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add0~17_sumout\ = SUM(( \mean0|loss_comm_count_a\(30) ) + ( GND ) + ( \mean0|Add0~22\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000011001100110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_loss_comm_count_a\(30),
	cin => \mean0|Add0~22\,
	sumout => \mean0|Add0~17_sumout\);

-- Location: FF_X14_Y7_N32
\mean0|loss_comm_count_a[30]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add0~17_sumout\,
	sclr => \prob_valid_1~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_a\(30));

-- Location: LABCELL_X14_Y7_N54
\mean0|Equal0~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Equal0~0_combout\ = ( !\mean0|loss_comm_count_a\(29) & ( !\mean0|loss_comm_count_a\(11) & ( (!\mean0|loss_comm_count_a\(27) & (!\mean0|loss_comm_count_a\(24) & (!\mean0|loss_comm_count_a\(28) & !\mean0|loss_comm_count_a\(30)))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "1000000000000000000000000000000000000000000000000000000000000000",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_loss_comm_count_a\(27),
	datab => \mean0|ALT_INV_loss_comm_count_a\(24),
	datac => \mean0|ALT_INV_loss_comm_count_a\(28),
	datad => \mean0|ALT_INV_loss_comm_count_a\(30),
	datae => \mean0|ALT_INV_loss_comm_count_a\(29),
	dataf => \mean0|ALT_INV_loss_comm_count_a\(11),
	combout => \mean0|Equal0~0_combout\);

-- Location: MLABCELL_X13_Y8_N48
\mean0|Equal0~5\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Equal0~5_combout\ = ( \mean0|Equal0~3_combout\ & ( \mean0|Equal0~0_combout\ & ( (!\mean0|loss_comm_count_a\(26) & (\mean0|Equal0~1_combout\ & (\mean0|Equal0~4_combout\ & \mean0|Equal0~2_combout\))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000000000000000000000000000010",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_loss_comm_count_a\(26),
	datab => \mean0|ALT_INV_Equal0~1_combout\,
	datac => \mean0|ALT_INV_Equal0~4_combout\,
	datad => \mean0|ALT_INV_Equal0~2_combout\,
	datae => \mean0|ALT_INV_Equal0~3_combout\,
	dataf => \mean0|ALT_INV_Equal0~0_combout\,
	combout => \mean0|Equal0~5_combout\);

-- Location: MLABCELL_X13_Y9_N48
\mean0|Equal1~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Equal1~0_combout\ = ( !\mean0|loss_comm_count_b\(16) & ( !\mean0|loss_comm_count_b\(11) & ( (!\mean0|loss_comm_count_b\(12) & (!\mean0|loss_comm_count_b\(15) & (!\mean0|loss_comm_count_b\(13) & !\mean0|loss_comm_count_b\(17)))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "1000000000000000000000000000000000000000000000000000000000000000",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_loss_comm_count_b\(12),
	datab => \mean0|ALT_INV_loss_comm_count_b\(15),
	datac => \mean0|ALT_INV_loss_comm_count_b\(13),
	datad => \mean0|ALT_INV_loss_comm_count_b\(17),
	datae => \mean0|ALT_INV_loss_comm_count_b\(16),
	dataf => \mean0|ALT_INV_loss_comm_count_b\(11),
	combout => \mean0|Equal1~0_combout\);

-- Location: LABCELL_X12_Y9_N54
\mean0|Add1~1\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~1_sumout\ = SUM(( \mean0|loss_comm_count_b\(18) ) + ( GND ) + ( \mean0|Add1~26\ ))
-- \mean0|Add1~2\ = CARRY(( \mean0|loss_comm_count_b\(18) ) + ( GND ) + ( \mean0|Add1~26\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_b\(18),
	cin => \mean0|Add1~26\,
	sumout => \mean0|Add1~1_sumout\,
	cout => \mean0|Add1~2\);

-- Location: LABCELL_X12_Y9_N57
\mean0|Add1~89\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~89_sumout\ = SUM(( \mean0|loss_comm_count_b\(19) ) + ( GND ) + ( \mean0|Add1~2\ ))
-- \mean0|Add1~90\ = CARRY(( \mean0|loss_comm_count_b\(19) ) + ( GND ) + ( \mean0|Add1~2\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_b\(19),
	cin => \mean0|Add1~2\,
	sumout => \mean0|Add1~89_sumout\,
	cout => \mean0|Add1~90\);

-- Location: FF_X12_Y9_N59
\mean0|loss_comm_count_b[19]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~89_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(19));

-- Location: LABCELL_X12_Y8_N0
\mean0|Add1~61\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~61_sumout\ = SUM(( \mean0|loss_comm_count_b\(20) ) + ( GND ) + ( \mean0|Add1~90\ ))
-- \mean0|Add1~62\ = CARRY(( \mean0|loss_comm_count_b\(20) ) + ( GND ) + ( \mean0|Add1~90\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_b\(20),
	cin => \mean0|Add1~90\,
	sumout => \mean0|Add1~61_sumout\,
	cout => \mean0|Add1~62\);

-- Location: FF_X12_Y8_N2
\mean0|loss_comm_count_b[20]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~61_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(20));

-- Location: LABCELL_X12_Y8_N3
\mean0|Add1~93\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~93_sumout\ = SUM(( \mean0|loss_comm_count_b\(21) ) + ( GND ) + ( \mean0|Add1~62\ ))
-- \mean0|Add1~94\ = CARRY(( \mean0|loss_comm_count_b\(21) ) + ( GND ) + ( \mean0|Add1~62\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_b\(21),
	cin => \mean0|Add1~62\,
	sumout => \mean0|Add1~93_sumout\,
	cout => \mean0|Add1~94\);

-- Location: FF_X12_Y8_N5
\mean0|loss_comm_count_b[21]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~93_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(21));

-- Location: LABCELL_X12_Y8_N6
\mean0|Add1~97\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~97_sumout\ = SUM(( \mean0|loss_comm_count_b\(22) ) + ( GND ) + ( \mean0|Add1~94\ ))
-- \mean0|Add1~98\ = CARRY(( \mean0|loss_comm_count_b\(22) ) + ( GND ) + ( \mean0|Add1~94\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000011001100110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_loss_comm_count_b\(22),
	cin => \mean0|Add1~94\,
	sumout => \mean0|Add1~97_sumout\,
	cout => \mean0|Add1~98\);

-- Location: FF_X12_Y8_N8
\mean0|loss_comm_count_b[22]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~97_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(22));

-- Location: LABCELL_X12_Y8_N9
\mean0|Add1~101\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~101_sumout\ = SUM(( \mean0|loss_comm_count_b\(23) ) + ( GND ) + ( \mean0|Add1~98\ ))
-- \mean0|Add1~102\ = CARRY(( \mean0|loss_comm_count_b\(23) ) + ( GND ) + ( \mean0|Add1~98\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_b\(23),
	cin => \mean0|Add1~98\,
	sumout => \mean0|Add1~101_sumout\,
	cout => \mean0|Add1~102\);

-- Location: FF_X12_Y8_N11
\mean0|loss_comm_count_b[23]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~101_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(23));

-- Location: LABCELL_X12_Y8_N12
\mean0|Add1~29\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~29_sumout\ = SUM(( \mean0|loss_comm_count_b\(24) ) + ( GND ) + ( \mean0|Add1~102\ ))
-- \mean0|Add1~30\ = CARRY(( \mean0|loss_comm_count_b\(24) ) + ( GND ) + ( \mean0|Add1~102\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000011001100110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_loss_comm_count_b\(24),
	cin => \mean0|Add1~102\,
	sumout => \mean0|Add1~29_sumout\,
	cout => \mean0|Add1~30\);

-- Location: FF_X12_Y8_N14
\mean0|loss_comm_count_b[24]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~29_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(24));

-- Location: LABCELL_X12_Y8_N15
\mean0|Add1~105\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~105_sumout\ = SUM(( \mean0|loss_comm_count_b\(25) ) + ( GND ) + ( \mean0|Add1~30\ ))
-- \mean0|Add1~106\ = CARRY(( \mean0|loss_comm_count_b\(25) ) + ( GND ) + ( \mean0|Add1~30\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_b\(25),
	cin => \mean0|Add1~30\,
	sumout => \mean0|Add1~105_sumout\,
	cout => \mean0|Add1~106\);

-- Location: FF_X12_Y8_N17
\mean0|loss_comm_count_b[25]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~105_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(25));

-- Location: LABCELL_X12_Y8_N18
\mean0|Add1~109\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~109_sumout\ = SUM(( \mean0|loss_comm_count_b\(26) ) + ( GND ) + ( \mean0|Add1~106\ ))
-- \mean0|Add1~110\ = CARRY(( \mean0|loss_comm_count_b\(26) ) + ( GND ) + ( \mean0|Add1~106\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_b\(26),
	cin => \mean0|Add1~106\,
	sumout => \mean0|Add1~109_sumout\,
	cout => \mean0|Add1~110\);

-- Location: FF_X12_Y8_N20
\mean0|loss_comm_count_b[26]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~109_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(26));

-- Location: LABCELL_X12_Y8_N21
\mean0|Add1~113\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~113_sumout\ = SUM(( \mean0|loss_comm_count_b\(27) ) + ( GND ) + ( \mean0|Add1~110\ ))
-- \mean0|Add1~114\ = CARRY(( \mean0|loss_comm_count_b\(27) ) + ( GND ) + ( \mean0|Add1~110\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_b\(27),
	cin => \mean0|Add1~110\,
	sumout => \mean0|Add1~113_sumout\,
	cout => \mean0|Add1~114\);

-- Location: FF_X12_Y8_N23
\mean0|loss_comm_count_b[27]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~113_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(27));

-- Location: LABCELL_X12_Y8_N24
\mean0|Add1~117\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~117_sumout\ = SUM(( \mean0|loss_comm_count_b\(28) ) + ( GND ) + ( \mean0|Add1~114\ ))
-- \mean0|Add1~118\ = CARRY(( \mean0|loss_comm_count_b\(28) ) + ( GND ) + ( \mean0|Add1~114\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_b\(28),
	cin => \mean0|Add1~114\,
	sumout => \mean0|Add1~117_sumout\,
	cout => \mean0|Add1~118\);

-- Location: FF_X12_Y8_N26
\mean0|loss_comm_count_b[28]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~117_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(28));

-- Location: LABCELL_X12_Y8_N27
\mean0|Add1~121\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~121_sumout\ = SUM(( \mean0|loss_comm_count_b\(29) ) + ( GND ) + ( \mean0|Add1~118\ ))
-- \mean0|Add1~122\ = CARRY(( \mean0|loss_comm_count_b\(29) ) + ( GND ) + ( \mean0|Add1~118\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_b\(29),
	cin => \mean0|Add1~118\,
	sumout => \mean0|Add1~121_sumout\,
	cout => \mean0|Add1~122\);

-- Location: FF_X12_Y8_N29
\mean0|loss_comm_count_b[29]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~121_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(29));

-- Location: LABCELL_X12_Y8_N42
\mean0|Equal1~4\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Equal1~4_combout\ = ( !\mean0|loss_comm_count_b\(29) & ( !\mean0|loss_comm_count_b\(28) & ( (!\mean0|loss_comm_count_b\(27) & (!\mean0|loss_comm_count_b\(26) & !\mean0|loss_comm_count_b\(25))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "1010000000000000000000000000000000000000000000000000000000000000",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_loss_comm_count_b\(27),
	datac => \mean0|ALT_INV_loss_comm_count_b\(26),
	datad => \mean0|ALT_INV_loss_comm_count_b\(25),
	datae => \mean0|ALT_INV_loss_comm_count_b\(29),
	dataf => \mean0|ALT_INV_loss_comm_count_b\(28),
	combout => \mean0|Equal1~4_combout\);

-- Location: LABCELL_X12_Y8_N30
\mean0|Add1~33\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~33_sumout\ = SUM(( \mean0|loss_comm_count_b\(30) ) + ( GND ) + ( \mean0|Add1~122\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000011001100110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_loss_comm_count_b\(30),
	cin => \mean0|Add1~122\,
	sumout => \mean0|Add1~33_sumout\);

-- Location: FF_X12_Y8_N32
\mean0|loss_comm_count_b[30]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~33_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(30));

-- Location: LABCELL_X12_Y8_N48
\mean0|Equal1~3\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Equal1~3_combout\ = ( !\mean0|loss_comm_count_b\(19) & ( (!\mean0|loss_comm_count_b\(21) & (!\mean0|loss_comm_count_b\(22) & (!\mean0|loss_comm_count_b\(23) & !\mean0|loss_comm_count_b\(14)))) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "1000000000000000100000000000000000000000000000000000000000000000",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_loss_comm_count_b\(21),
	datab => \mean0|ALT_INV_loss_comm_count_b\(22),
	datac => \mean0|ALT_INV_loss_comm_count_b\(23),
	datad => \mean0|ALT_INV_loss_comm_count_b\(14),
	dataf => \mean0|ALT_INV_loss_comm_count_b\(19),
	combout => \mean0|Equal1~3_combout\);

-- Location: LABCELL_X12_Y8_N57
\mean0|Equal1~2\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Equal1~2_combout\ = ( \mean0|loss_comm_count_b\(2) & ( \mean0|loss_comm_count_b\(0) & ( (!\mean0|loss_comm_count_b\(20) & (\mean0|loss_comm_count_b\(4) & (\mean0|loss_comm_count_b\(3) & !\mean0|loss_comm_count_b\(1)))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000000000000000000001000000000",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_loss_comm_count_b\(20),
	datab => \mean0|ALT_INV_loss_comm_count_b\(4),
	datac => \mean0|ALT_INV_loss_comm_count_b\(3),
	datad => \mean0|ALT_INV_loss_comm_count_b\(1),
	datae => \mean0|ALT_INV_loss_comm_count_b\(2),
	dataf => \mean0|ALT_INV_loss_comm_count_b\(0),
	combout => \mean0|Equal1~2_combout\);

-- Location: MLABCELL_X13_Y9_N6
\mean0|Equal1~1\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Equal1~1_combout\ = ( !\mean0|loss_comm_count_b\(10) & ( !\mean0|loss_comm_count_b\(5) & ( (!\mean0|loss_comm_count_b\(6) & (!\mean0|loss_comm_count_b\(9) & (!\mean0|loss_comm_count_b\(7) & !\mean0|loss_comm_count_b\(8)))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "1000000000000000000000000000000000000000000000000000000000000000",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_loss_comm_count_b\(6),
	datab => \mean0|ALT_INV_loss_comm_count_b\(9),
	datac => \mean0|ALT_INV_loss_comm_count_b\(7),
	datad => \mean0|ALT_INV_loss_comm_count_b\(8),
	datae => \mean0|ALT_INV_loss_comm_count_b\(10),
	dataf => \mean0|ALT_INV_loss_comm_count_b\(5),
	combout => \mean0|Equal1~1_combout\);

-- Location: MLABCELL_X13_Y8_N6
\mean0|Equal1~5\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Equal1~5_combout\ = ( \mean0|Equal1~2_combout\ & ( \mean0|Equal1~1_combout\ & ( (!\mean0|loss_comm_count_b\(24) & (\mean0|Equal1~4_combout\ & (!\mean0|loss_comm_count_b\(30) & \mean0|Equal1~3_combout\))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000000000000000000000000100000",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_loss_comm_count_b\(24),
	datab => \mean0|ALT_INV_Equal1~4_combout\,
	datac => \mean0|ALT_INV_loss_comm_count_b\(30),
	datad => \mean0|ALT_INV_Equal1~3_combout\,
	datae => \mean0|ALT_INV_Equal1~2_combout\,
	dataf => \mean0|ALT_INV_Equal1~1_combout\,
	combout => \mean0|Equal1~5_combout\);

-- Location: MLABCELL_X13_Y8_N24
\mean0|process_0~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|process_0~0_combout\ = ( \mean0|Equal1~0_combout\ & ( \mean0|Equal1~5_combout\ & ( (!\mean0|loss_comm_count_b\(18)) # (\mean0|Equal0~5_combout\) ) ) ) # ( !\mean0|Equal1~0_combout\ & ( \mean0|Equal1~5_combout\ & ( \mean0|Equal0~5_combout\ ) ) ) # ( 
-- \mean0|Equal1~0_combout\ & ( !\mean0|Equal1~5_combout\ & ( \mean0|Equal0~5_combout\ ) ) ) # ( !\mean0|Equal1~0_combout\ & ( !\mean0|Equal1~5_combout\ & ( \mean0|Equal0~5_combout\ ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000111100001111000011110000111100001111000011111010111110101111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_loss_comm_count_b\(18),
	datac => \mean0|ALT_INV_Equal0~5_combout\,
	datae => \mean0|ALT_INV_Equal1~0_combout\,
	dataf => \mean0|ALT_INV_Equal1~5_combout\,
	combout => \mean0|process_0~0_combout\);

-- Location: FF_X12_Y9_N2
\mean0|loss_comm_count_b[0]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~69_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(0));

-- Location: LABCELL_X12_Y9_N3
\mean0|Add1~65\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~65_sumout\ = SUM(( \mean0|loss_comm_count_b\(1) ) + ( GND ) + ( \mean0|Add1~70\ ))
-- \mean0|Add1~66\ = CARRY(( \mean0|loss_comm_count_b\(1) ) + ( GND ) + ( \mean0|Add1~70\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_b\(1),
	cin => \mean0|Add1~70\,
	sumout => \mean0|Add1~65_sumout\,
	cout => \mean0|Add1~66\);

-- Location: FF_X12_Y9_N5
\mean0|loss_comm_count_b[1]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~65_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(1));

-- Location: LABCELL_X12_Y9_N6
\mean0|Add1~73\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~73_sumout\ = SUM(( \mean0|loss_comm_count_b\(2) ) + ( GND ) + ( \mean0|Add1~66\ ))
-- \mean0|Add1~74\ = CARRY(( \mean0|loss_comm_count_b\(2) ) + ( GND ) + ( \mean0|Add1~66\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_b\(2),
	cin => \mean0|Add1~66\,
	sumout => \mean0|Add1~73_sumout\,
	cout => \mean0|Add1~74\);

-- Location: FF_X12_Y8_N38
\mean0|loss_comm_count_b[2]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \mean0|Add1~73_sumout\,
	sclr => \prob_valid_2~input_o\,
	sload => VCC,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(2));

-- Location: LABCELL_X12_Y9_N9
\mean0|Add1~77\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~77_sumout\ = SUM(( \mean0|loss_comm_count_b\(3) ) + ( GND ) + ( \mean0|Add1~74\ ))
-- \mean0|Add1~78\ = CARRY(( \mean0|loss_comm_count_b\(3) ) + ( GND ) + ( \mean0|Add1~74\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_b\(3),
	cin => \mean0|Add1~74\,
	sumout => \mean0|Add1~77_sumout\,
	cout => \mean0|Add1~78\);

-- Location: FF_X12_Y9_N11
\mean0|loss_comm_count_b[3]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~77_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(3));

-- Location: LABCELL_X12_Y9_N12
\mean0|Add1~81\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~81_sumout\ = SUM(( \mean0|loss_comm_count_b\(4) ) + ( GND ) + ( \mean0|Add1~78\ ))
-- \mean0|Add1~82\ = CARRY(( \mean0|loss_comm_count_b\(4) ) + ( GND ) + ( \mean0|Add1~78\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000011001100110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_loss_comm_count_b\(4),
	cin => \mean0|Add1~78\,
	sumout => \mean0|Add1~81_sumout\,
	cout => \mean0|Add1~82\);

-- Location: FF_X12_Y9_N14
\mean0|loss_comm_count_b[4]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~81_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(4));

-- Location: LABCELL_X12_Y9_N15
\mean0|Add1~37\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~37_sumout\ = SUM(( \mean0|loss_comm_count_b\(5) ) + ( GND ) + ( \mean0|Add1~82\ ))
-- \mean0|Add1~38\ = CARRY(( \mean0|loss_comm_count_b\(5) ) + ( GND ) + ( \mean0|Add1~82\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_b\(5),
	cin => \mean0|Add1~82\,
	sumout => \mean0|Add1~37_sumout\,
	cout => \mean0|Add1~38\);

-- Location: FF_X12_Y9_N17
\mean0|loss_comm_count_b[5]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~37_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(5));

-- Location: LABCELL_X12_Y9_N18
\mean0|Add1~41\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~41_sumout\ = SUM(( \mean0|loss_comm_count_b\(6) ) + ( GND ) + ( \mean0|Add1~38\ ))
-- \mean0|Add1~42\ = CARRY(( \mean0|loss_comm_count_b\(6) ) + ( GND ) + ( \mean0|Add1~38\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_b\(6),
	cin => \mean0|Add1~38\,
	sumout => \mean0|Add1~41_sumout\,
	cout => \mean0|Add1~42\);

-- Location: FF_X12_Y9_N20
\mean0|loss_comm_count_b[6]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~41_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(6));

-- Location: LABCELL_X12_Y9_N21
\mean0|Add1~45\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~45_sumout\ = SUM(( \mean0|loss_comm_count_b\(7) ) + ( GND ) + ( \mean0|Add1~42\ ))
-- \mean0|Add1~46\ = CARRY(( \mean0|loss_comm_count_b\(7) ) + ( GND ) + ( \mean0|Add1~42\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_b\(7),
	cin => \mean0|Add1~42\,
	sumout => \mean0|Add1~45_sumout\,
	cout => \mean0|Add1~46\);

-- Location: FF_X12_Y9_N23
\mean0|loss_comm_count_b[7]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~45_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(7));

-- Location: LABCELL_X12_Y9_N24
\mean0|Add1~49\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~49_sumout\ = SUM(( \mean0|loss_comm_count_b\(8) ) + ( GND ) + ( \mean0|Add1~46\ ))
-- \mean0|Add1~50\ = CARRY(( \mean0|loss_comm_count_b\(8) ) + ( GND ) + ( \mean0|Add1~46\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_b\(8),
	cin => \mean0|Add1~46\,
	sumout => \mean0|Add1~49_sumout\,
	cout => \mean0|Add1~50\);

-- Location: FF_X12_Y9_N26
\mean0|loss_comm_count_b[8]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~49_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(8));

-- Location: LABCELL_X12_Y9_N27
\mean0|Add1~53\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~53_sumout\ = SUM(( \mean0|loss_comm_count_b\(9) ) + ( GND ) + ( \mean0|Add1~50\ ))
-- \mean0|Add1~54\ = CARRY(( \mean0|loss_comm_count_b\(9) ) + ( GND ) + ( \mean0|Add1~50\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_b\(9),
	cin => \mean0|Add1~50\,
	sumout => \mean0|Add1~53_sumout\,
	cout => \mean0|Add1~54\);

-- Location: FF_X12_Y9_N29
\mean0|loss_comm_count_b[9]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~53_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(9));

-- Location: LABCELL_X12_Y9_N30
\mean0|Add1~57\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~57_sumout\ = SUM(( \mean0|loss_comm_count_b\(10) ) + ( GND ) + ( \mean0|Add1~54\ ))
-- \mean0|Add1~58\ = CARRY(( \mean0|loss_comm_count_b\(10) ) + ( GND ) + ( \mean0|Add1~54\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000011001100110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_loss_comm_count_b\(10),
	cin => \mean0|Add1~54\,
	sumout => \mean0|Add1~57_sumout\,
	cout => \mean0|Add1~58\);

-- Location: FF_X12_Y9_N32
\mean0|loss_comm_count_b[10]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~57_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(10));

-- Location: LABCELL_X12_Y9_N33
\mean0|Add1~5\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~5_sumout\ = SUM(( \mean0|loss_comm_count_b\(11) ) + ( GND ) + ( \mean0|Add1~58\ ))
-- \mean0|Add1~6\ = CARRY(( \mean0|loss_comm_count_b\(11) ) + ( GND ) + ( \mean0|Add1~58\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000101010101010101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_loss_comm_count_b\(11),
	cin => \mean0|Add1~58\,
	sumout => \mean0|Add1~5_sumout\,
	cout => \mean0|Add1~6\);

-- Location: FF_X12_Y9_N35
\mean0|loss_comm_count_b[11]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~5_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(11));

-- Location: LABCELL_X12_Y9_N36
\mean0|Add1~9\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~9_sumout\ = SUM(( \mean0|loss_comm_count_b\(12) ) + ( GND ) + ( \mean0|Add1~6\ ))
-- \mean0|Add1~10\ = CARRY(( \mean0|loss_comm_count_b\(12) ) + ( GND ) + ( \mean0|Add1~6\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_b\(12),
	cin => \mean0|Add1~6\,
	sumout => \mean0|Add1~9_sumout\,
	cout => \mean0|Add1~10\);

-- Location: FF_X12_Y9_N38
\mean0|loss_comm_count_b[12]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~9_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(12));

-- Location: LABCELL_X12_Y9_N39
\mean0|Add1~13\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~13_sumout\ = SUM(( \mean0|loss_comm_count_b\(13) ) + ( GND ) + ( \mean0|Add1~10\ ))
-- \mean0|Add1~14\ = CARRY(( \mean0|loss_comm_count_b\(13) ) + ( GND ) + ( \mean0|Add1~10\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_b\(13),
	cin => \mean0|Add1~10\,
	sumout => \mean0|Add1~13_sumout\,
	cout => \mean0|Add1~14\);

-- Location: FF_X12_Y9_N41
\mean0|loss_comm_count_b[13]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~13_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(13));

-- Location: LABCELL_X12_Y9_N42
\mean0|Add1~85\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~85_sumout\ = SUM(( \mean0|loss_comm_count_b\(14) ) + ( GND ) + ( \mean0|Add1~14\ ))
-- \mean0|Add1~86\ = CARRY(( \mean0|loss_comm_count_b\(14) ) + ( GND ) + ( \mean0|Add1~14\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000011001100110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_loss_comm_count_b\(14),
	cin => \mean0|Add1~14\,
	sumout => \mean0|Add1~85_sumout\,
	cout => \mean0|Add1~86\);

-- Location: FF_X12_Y9_N44
\mean0|loss_comm_count_b[14]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~85_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(14));

-- Location: LABCELL_X12_Y9_N45
\mean0|Add1~17\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~17_sumout\ = SUM(( \mean0|loss_comm_count_b\(15) ) + ( GND ) + ( \mean0|Add1~86\ ))
-- \mean0|Add1~18\ = CARRY(( \mean0|loss_comm_count_b\(15) ) + ( GND ) + ( \mean0|Add1~86\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datad => \mean0|ALT_INV_loss_comm_count_b\(15),
	cin => \mean0|Add1~86\,
	sumout => \mean0|Add1~17_sumout\,
	cout => \mean0|Add1~18\);

-- Location: FF_X12_Y9_N47
\mean0|loss_comm_count_b[15]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~17_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(15));

-- Location: LABCELL_X12_Y9_N48
\mean0|Add1~21\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~21_sumout\ = SUM(( \mean0|loss_comm_count_b\(16) ) + ( GND ) + ( \mean0|Add1~18\ ))
-- \mean0|Add1~22\ = CARRY(( \mean0|loss_comm_count_b\(16) ) + ( GND ) + ( \mean0|Add1~18\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_loss_comm_count_b\(16),
	cin => \mean0|Add1~18\,
	sumout => \mean0|Add1~21_sumout\,
	cout => \mean0|Add1~22\);

-- Location: FF_X12_Y9_N50
\mean0|loss_comm_count_b[16]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~21_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(16));

-- Location: LABCELL_X12_Y9_N51
\mean0|Add1~25\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add1~25_sumout\ = SUM(( \mean0|loss_comm_count_b\(17) ) + ( GND ) + ( \mean0|Add1~22\ ))
-- \mean0|Add1~26\ = CARRY(( \mean0|loss_comm_count_b\(17) ) + ( GND ) + ( \mean0|Add1~22\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111111111111100000000000000000101010101010101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_loss_comm_count_b\(17),
	cin => \mean0|Add1~22\,
	sumout => \mean0|Add1~25_sumout\,
	cout => \mean0|Add1~26\);

-- Location: FF_X12_Y9_N53
\mean0|loss_comm_count_b[17]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~25_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(17));

-- Location: FF_X12_Y9_N56
\mean0|loss_comm_count_b[18]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|Add1~1_sumout\,
	sclr => \prob_valid_2~input_o\,
	ena => \mean0|ALT_INV_process_0~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|loss_comm_count_b\(18));

-- Location: MLABCELL_X13_Y8_N21
\mean0|init_flag_a~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|init_flag_a~0_combout\ = ( \mean0|init_flag_a~q\ & ( \mean0|Equal0~5_combout\ ) ) # ( \mean0|init_flag_a~q\ & ( !\mean0|Equal0~5_combout\ ) ) # ( !\mean0|init_flag_a~q\ & ( !\mean0|Equal0~5_combout\ & ( (\prob_valid_1~input_o\ & 
-- (((!\mean0|Equal1~0_combout\) # (!\mean0|Equal1~5_combout\)) # (\mean0|loss_comm_count_b\(18)))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000011111101111111111111111100000000000000001111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_loss_comm_count_b\(18),
	datab => \mean0|ALT_INV_Equal1~0_combout\,
	datac => \mean0|ALT_INV_Equal1~5_combout\,
	datad => \ALT_INV_prob_valid_1~input_o\,
	datae => \mean0|ALT_INV_init_flag_a~q\,
	dataf => \mean0|ALT_INV_Equal0~5_combout\,
	combout => \mean0|init_flag_a~0_combout\);

-- Location: FF_X13_Y8_N23
\mean0|init_flag_a\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|init_flag_a~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|init_flag_a~q\);

-- Location: IOIBUF_X16_Y0_N75
\prob_2[1]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(1),
	o => \prob_2[1]~input_o\);

-- Location: MLABCELL_X13_Y9_N18
\mean0|b_stable_valid[9]~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|b_stable_valid[9]~0_combout\ = ( \mean0|Equal0~5_combout\ & ( \mean0|Equal1~5_combout\ ) ) # ( !\mean0|Equal0~5_combout\ & ( \mean0|Equal1~5_combout\ & ( ((\mean0|Equal1~0_combout\ & !\mean0|loss_comm_count_b\(18))) # (\prob_valid_2~input_o\) ) ) ) 
-- # ( \mean0|Equal0~5_combout\ & ( !\mean0|Equal1~5_combout\ ) ) # ( !\mean0|Equal0~5_combout\ & ( !\mean0|Equal1~5_combout\ & ( \prob_valid_2~input_o\ ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000111100001111111111111111111101001111010011111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_Equal1~0_combout\,
	datab => \mean0|ALT_INV_loss_comm_count_b\(18),
	datac => \ALT_INV_prob_valid_2~input_o\,
	datae => \mean0|ALT_INV_Equal0~5_combout\,
	dataf => \mean0|ALT_INV_Equal1~5_combout\,
	combout => \mean0|b_stable_valid[9]~0_combout\);

-- Location: FF_X13_Y9_N11
\mean0|b_stable_valid[1]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_2[1]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(1));

-- Location: IOIBUF_X25_Y0_N35
\prob_1[1]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(1),
	o => \prob_1[1]~input_o\);

-- Location: MLABCELL_X13_Y8_N33
\mean0|a_stable_valid[15]~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|a_stable_valid[15]~0_combout\ = ( \mean0|loss_comm_count_b\(18) & ( \mean0|Equal1~5_combout\ & ( (\mean0|Equal0~5_combout\) # (\prob_valid_1~input_o\) ) ) ) # ( !\mean0|loss_comm_count_b\(18) & ( \mean0|Equal1~5_combout\ & ( 
-- ((\mean0|Equal0~5_combout\) # (\mean0|Equal1~0_combout\)) # (\prob_valid_1~input_o\) ) ) ) # ( \mean0|loss_comm_count_b\(18) & ( !\mean0|Equal1~5_combout\ & ( (\mean0|Equal0~5_combout\) # (\prob_valid_1~input_o\) ) ) ) # ( !\mean0|loss_comm_count_b\(18) & 
-- ( !\mean0|Equal1~5_combout\ & ( (\mean0|Equal0~5_combout\) # (\prob_valid_1~input_o\) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0101010111111111010101011111111101011111111111110101010111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \ALT_INV_prob_valid_1~input_o\,
	datac => \mean0|ALT_INV_Equal1~0_combout\,
	datad => \mean0|ALT_INV_Equal0~5_combout\,
	datae => \mean0|ALT_INV_loss_comm_count_b\(18),
	dataf => \mean0|ALT_INV_Equal1~5_combout\,
	combout => \mean0|a_stable_valid[15]~0_combout\);

-- Location: FF_X14_Y10_N35
\mean0|a_stable_valid[1]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[1]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(1));

-- Location: IOIBUF_X0_Y20_N4
\prob_1[0]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(0),
	o => \prob_1[0]~input_o\);

-- Location: FF_X14_Y10_N32
\mean0|a_stable_valid[0]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[0]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(0));

-- Location: IOIBUF_X0_Y18_N44
\prob_2[0]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(0),
	o => \prob_2[0]~input_o\);

-- Location: FF_X14_Y10_N5
\mean0|b_stable_valid[0]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_2[0]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(0));

-- Location: LABCELL_X14_Y10_N30
\mean0|Add2~94\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~94_cout\ = CARRY(( \mean0|b_stable_valid\(0) ) + ( \mean0|a_stable_valid\(0) ) + ( !VCC ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000110011001100110000000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_a_stable_valid\(0),
	datac => \mean0|ALT_INV_b_stable_valid\(0),
	cin => GND,
	cout => \mean0|Add2~94_cout\);

-- Location: LABCELL_X14_Y10_N33
\mean0|Add2~1\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~1_sumout\ = SUM(( \mean0|b_stable_valid\(1) ) + ( \mean0|a_stable_valid\(1) ) + ( \mean0|Add2~94_cout\ ))
-- \mean0|Add2~2\ = CARRY(( \mean0|b_stable_valid\(1) ) + ( \mean0|a_stable_valid\(1) ) + ( \mean0|Add2~94_cout\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111110000000000000000000000000101010101010101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_b_stable_valid\(1),
	dataf => \mean0|ALT_INV_a_stable_valid\(1),
	cin => \mean0|Add2~94_cout\,
	sumout => \mean0|Add2~1_sumout\,
	cout => \mean0|Add2~2\);

-- Location: MLABCELL_X13_Y8_N42
\mean0|init_flag_b~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|init_flag_b~0_combout\ = ( \mean0|init_flag_b~q\ & ( \mean0|Equal0~5_combout\ ) ) # ( \mean0|init_flag_b~q\ & ( !\mean0|Equal0~5_combout\ ) ) # ( !\mean0|init_flag_b~q\ & ( !\mean0|Equal0~5_combout\ & ( (\prob_valid_2~input_o\ & 
-- ((!\mean0|Equal1~5_combout\) # ((!\mean0|Equal1~0_combout\) # (\mean0|loss_comm_count_b\(18))))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0011001100100011111111111111111100000000000000001111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_Equal1~5_combout\,
	datab => \ALT_INV_prob_valid_2~input_o\,
	datac => \mean0|ALT_INV_loss_comm_count_b\(18),
	datad => \mean0|ALT_INV_Equal1~0_combout\,
	datae => \mean0|ALT_INV_init_flag_b~q\,
	dataf => \mean0|ALT_INV_Equal0~5_combout\,
	combout => \mean0|init_flag_b~0_combout\);

-- Location: FF_X13_Y8_N44
\mean0|init_flag_b\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|init_flag_b~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|init_flag_b~q\);

-- Location: MLABCELL_X18_Y8_N24
\mean0|c[0]~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[0]~0_combout\ = ( \mean0|init_flag_b~q\ & ( (\mean0|init_flag_a~q\ & \mean0|Add2~1_sumout\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000011000000110000001100000011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_init_flag_a~q\,
	datac => \mean0|ALT_INV_Add2~1_sumout\,
	dataf => \mean0|ALT_INV_init_flag_b~q\,
	combout => \mean0|c[0]~0_combout\);

-- Location: IOIBUF_X25_Y0_N18
\prob_2[2]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(2),
	o => \prob_2[2]~input_o\);

-- Location: LABCELL_X14_Y9_N57
\mean0|b_stable_valid[2]~feeder\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|b_stable_valid[2]~feeder_combout\ = ( \prob_2[2]~input_o\ )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000011111111111111111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataf => \ALT_INV_prob_2[2]~input_o\,
	combout => \mean0|b_stable_valid[2]~feeder_combout\);

-- Location: FF_X14_Y9_N58
\mean0|b_stable_valid[2]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|b_stable_valid[2]~feeder_combout\,
	sclr => \mean0|process_0~0_combout\,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(2));

-- Location: IOIBUF_X0_Y20_N38
\prob_1[2]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(2),
	o => \prob_1[2]~input_o\);

-- Location: FF_X14_Y10_N38
\mean0|a_stable_valid[2]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[2]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(2));

-- Location: LABCELL_X14_Y10_N36
\mean0|Add2~5\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~5_sumout\ = SUM(( \mean0|b_stable_valid\(2) ) + ( \mean0|a_stable_valid\(2) ) + ( \mean0|Add2~2\ ))
-- \mean0|Add2~6\ = CARRY(( \mean0|b_stable_valid\(2) ) + ( \mean0|a_stable_valid\(2) ) + ( \mean0|Add2~2\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111100001111000000000000000000000011001100110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_b_stable_valid\(2),
	datac => \mean0|ALT_INV_a_stable_valid\(2),
	cin => \mean0|Add2~2\,
	sumout => \mean0|Add2~5_sumout\,
	cout => \mean0|Add2~6\);

-- Location: LABCELL_X12_Y8_N36
\mean0|c[1]~1\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[1]~1_combout\ = ( \mean0|init_flag_b~q\ & ( (\mean0|Add2~5_sumout\ & \mean0|init_flag_a~q\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000110000001100000000000000000000001100000011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_Add2~5_sumout\,
	datac => \mean0|ALT_INV_init_flag_a~q\,
	datae => \mean0|ALT_INV_init_flag_b~q\,
	combout => \mean0|c[1]~1_combout\);

-- Location: IOIBUF_X0_Y19_N21
\prob_2[3]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(3),
	o => \prob_2[3]~input_o\);

-- Location: FF_X13_Y9_N13
\mean0|b_stable_valid[3]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_2[3]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(3));

-- Location: IOIBUF_X0_Y20_N55
\prob_1[3]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(3),
	o => \prob_1[3]~input_o\);

-- Location: FF_X13_Y8_N53
\mean0|a_stable_valid[3]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[3]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(3));

-- Location: LABCELL_X14_Y10_N39
\mean0|Add2~9\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~9_sumout\ = SUM(( \mean0|b_stable_valid\(3) ) + ( \mean0|a_stable_valid\(3) ) + ( \mean0|Add2~6\ ))
-- \mean0|Add2~10\ = CARRY(( \mean0|b_stable_valid\(3) ) + ( \mean0|a_stable_valid\(3) ) + ( \mean0|Add2~6\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111110000000000000000000000000101010101010101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_b_stable_valid\(3),
	dataf => \mean0|ALT_INV_a_stable_valid\(3),
	cin => \mean0|Add2~6\,
	sumout => \mean0|Add2~9_sumout\,
	cout => \mean0|Add2~10\);

-- Location: MLABCELL_X18_Y8_N57
\mean0|c[2]~2\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[2]~2_combout\ = ( \mean0|Add2~9_sumout\ & ( (\mean0|init_flag_b~q\ & \mean0|init_flag_a~q\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000010001000100010001000100010001",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_init_flag_b~q\,
	datab => \mean0|ALT_INV_init_flag_a~q\,
	dataf => \mean0|ALT_INV_Add2~9_sumout\,
	combout => \mean0|c[2]~2_combout\);

-- Location: IOIBUF_X34_Y0_N52
\prob_1[4]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(4),
	o => \prob_1[4]~input_o\);

-- Location: FF_X14_Y10_N44
\mean0|a_stable_valid[4]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[4]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(4));

-- Location: IOIBUF_X0_Y18_N78
\prob_2[4]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(4),
	o => \prob_2[4]~input_o\);

-- Location: LABCELL_X14_Y10_N24
\mean0|b_stable_valid[4]~feeder\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|b_stable_valid[4]~feeder_combout\ = ( \prob_2[4]~input_o\ )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000011111111111111111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataf => \ALT_INV_prob_2[4]~input_o\,
	combout => \mean0|b_stable_valid[4]~feeder_combout\);

-- Location: FF_X14_Y10_N26
\mean0|b_stable_valid[4]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|b_stable_valid[4]~feeder_combout\,
	sclr => \mean0|process_0~0_combout\,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(4));

-- Location: LABCELL_X14_Y10_N42
\mean0|Add2~13\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~13_sumout\ = SUM(( \mean0|b_stable_valid\(4) ) + ( \mean0|a_stable_valid\(4) ) + ( \mean0|Add2~10\ ))
-- \mean0|Add2~14\ = CARRY(( \mean0|b_stable_valid\(4) ) + ( \mean0|a_stable_valid\(4) ) + ( \mean0|Add2~10\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000110011001100110000000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_a_stable_valid\(4),
	datac => \mean0|ALT_INV_b_stable_valid\(4),
	cin => \mean0|Add2~10\,
	sumout => \mean0|Add2~13_sumout\,
	cout => \mean0|Add2~14\);

-- Location: MLABCELL_X18_Y8_N0
\mean0|c[3]~3\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[3]~3_combout\ = ( \mean0|Add2~13_sumout\ & ( (\mean0|init_flag_a~q\ & \mean0|init_flag_b~q\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000011000000110000001100000011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_init_flag_a~q\,
	datac => \mean0|ALT_INV_init_flag_b~q\,
	dataf => \mean0|ALT_INV_Add2~13_sumout\,
	combout => \mean0|c[3]~3_combout\);

-- Location: IOIBUF_X0_Y19_N38
\prob_2[5]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(5),
	o => \prob_2[5]~input_o\);

-- Location: FF_X14_Y9_N34
\mean0|b_stable_valid[5]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_2[5]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(5));

-- Location: IOIBUF_X0_Y18_N95
\prob_1[5]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(5),
	o => \prob_1[5]~input_o\);

-- Location: FF_X14_Y10_N46
\mean0|a_stable_valid[5]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[5]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(5));

-- Location: LABCELL_X14_Y10_N45
\mean0|Add2~17\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~17_sumout\ = SUM(( \mean0|b_stable_valid\(5) ) + ( \mean0|a_stable_valid\(5) ) + ( \mean0|Add2~14\ ))
-- \mean0|Add2~18\ = CARRY(( \mean0|b_stable_valid\(5) ) + ( \mean0|a_stable_valid\(5) ) + ( \mean0|Add2~14\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111100001111000000000000000000000101010101010101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_b_stable_valid\(5),
	datac => \mean0|ALT_INV_a_stable_valid\(5),
	cin => \mean0|Add2~14\,
	sumout => \mean0|Add2~17_sumout\,
	cout => \mean0|Add2~18\);

-- Location: MLABCELL_X18_Y8_N6
\mean0|c[4]~4\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[4]~4_combout\ = ( \mean0|Add2~17_sumout\ & ( (\mean0|init_flag_a~q\ & \mean0|init_flag_b~q\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000011000000110000001100000011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_init_flag_a~q\,
	datac => \mean0|ALT_INV_init_flag_b~q\,
	dataf => \mean0|ALT_INV_Add2~17_sumout\,
	combout => \mean0|c[4]~4_combout\);

-- Location: IOIBUF_X54_Y14_N44
\prob_2[6]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(6),
	o => \prob_2[6]~input_o\);

-- Location: LABCELL_X14_Y9_N51
\mean0|b_stable_valid[6]~feeder\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|b_stable_valid[6]~feeder_combout\ = ( \prob_2[6]~input_o\ )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000011111111111111111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataf => \ALT_INV_prob_2[6]~input_o\,
	combout => \mean0|b_stable_valid[6]~feeder_combout\);

-- Location: FF_X14_Y9_N52
\mean0|b_stable_valid[6]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|b_stable_valid[6]~feeder_combout\,
	sclr => \mean0|process_0~0_combout\,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(6));

-- Location: IOIBUF_X19_Y0_N18
\prob_1[6]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(6),
	o => \prob_1[6]~input_o\);

-- Location: FF_X14_Y10_N50
\mean0|a_stable_valid[6]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[6]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(6));

-- Location: LABCELL_X14_Y10_N48
\mean0|Add2~21\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~21_sumout\ = SUM(( \mean0|b_stable_valid\(6) ) + ( \mean0|a_stable_valid\(6) ) + ( \mean0|Add2~18\ ))
-- \mean0|Add2~22\ = CARRY(( \mean0|b_stable_valid\(6) ) + ( \mean0|a_stable_valid\(6) ) + ( \mean0|Add2~18\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111100001111000000000000000000000101010101010101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_b_stable_valid\(6),
	datac => \mean0|ALT_INV_a_stable_valid\(6),
	cin => \mean0|Add2~18\,
	sumout => \mean0|Add2~21_sumout\,
	cout => \mean0|Add2~22\);

-- Location: MLABCELL_X18_Y8_N9
\mean0|c[5]~5\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[5]~5_combout\ = ( \mean0|Add2~21_sumout\ & ( (\mean0|init_flag_b~q\ & \mean0|init_flag_a~q\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000010001000100010001000100010001",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_init_flag_b~q\,
	datab => \mean0|ALT_INV_init_flag_a~q\,
	dataf => \mean0|ALT_INV_Add2~21_sumout\,
	combout => \mean0|c[5]~5_combout\);

-- Location: IOIBUF_X33_Y0_N58
\prob_1[7]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(7),
	o => \prob_1[7]~input_o\);

-- Location: FF_X14_Y10_N52
\mean0|a_stable_valid[7]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[7]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(7));

-- Location: IOIBUF_X11_Y0_N18
\prob_2[7]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(7),
	o => \prob_2[7]~input_o\);

-- Location: FF_X13_Y9_N40
\mean0|b_stable_valid[7]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_2[7]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(7));

-- Location: LABCELL_X14_Y10_N51
\mean0|Add2~25\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~25_sumout\ = SUM(( \mean0|b_stable_valid\(7) ) + ( \mean0|a_stable_valid\(7) ) + ( \mean0|Add2~22\ ))
-- \mean0|Add2~26\ = CARRY(( \mean0|b_stable_valid\(7) ) + ( \mean0|a_stable_valid\(7) ) + ( \mean0|Add2~22\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000110011001100110000000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_a_stable_valid\(7),
	datac => \mean0|ALT_INV_b_stable_valid\(7),
	cin => \mean0|Add2~22\,
	sumout => \mean0|Add2~25_sumout\,
	cout => \mean0|Add2~26\);

-- Location: LABCELL_X12_Y8_N51
\mean0|c[6]~6\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[6]~6_combout\ = ( \mean0|Add2~25_sumout\ & ( (\mean0|init_flag_b~q\ & \mean0|init_flag_a~q\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000000000011110000000000001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_init_flag_b~q\,
	datad => \mean0|ALT_INV_init_flag_a~q\,
	dataf => \mean0|ALT_INV_Add2~25_sumout\,
	combout => \mean0|c[6]~6_combout\);

-- Location: IOIBUF_X0_Y18_N61
\prob_2[8]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(8),
	o => \prob_2[8]~input_o\);

-- Location: LABCELL_X14_Y10_N6
\mean0|b_stable_valid[8]~feeder\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|b_stable_valid[8]~feeder_combout\ = ( \prob_2[8]~input_o\ )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000011111111111111111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataf => \ALT_INV_prob_2[8]~input_o\,
	combout => \mean0|b_stable_valid[8]~feeder_combout\);

-- Location: FF_X14_Y10_N8
\mean0|b_stable_valid[8]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|b_stable_valid[8]~feeder_combout\,
	sclr => \mean0|process_0~0_combout\,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(8));

-- Location: IOIBUF_X19_Y0_N52
\prob_1[8]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(8),
	o => \prob_1[8]~input_o\);

-- Location: FF_X14_Y10_N56
\mean0|a_stable_valid[8]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[8]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(8));

-- Location: LABCELL_X14_Y10_N54
\mean0|Add2~29\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~29_sumout\ = SUM(( \mean0|b_stable_valid\(8) ) + ( \mean0|a_stable_valid\(8) ) + ( \mean0|Add2~26\ ))
-- \mean0|Add2~30\ = CARRY(( \mean0|b_stable_valid\(8) ) + ( \mean0|a_stable_valid\(8) ) + ( \mean0|Add2~26\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111100001111000000000000000000000011001100110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_b_stable_valid\(8),
	datac => \mean0|ALT_INV_a_stable_valid\(8),
	cin => \mean0|Add2~26\,
	sumout => \mean0|Add2~29_sumout\,
	cout => \mean0|Add2~30\);

-- Location: MLABCELL_X13_Y9_N15
\mean0|c[7]~7\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[7]~7_combout\ = ( \mean0|init_flag_b~q\ & ( (\mean0|init_flag_a~q\ & \mean0|Add2~29_sumout\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000001010000010100000000000000000000010100000101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_init_flag_a~q\,
	datac => \mean0|ALT_INV_Add2~29_sumout\,
	datae => \mean0|ALT_INV_init_flag_b~q\,
	combout => \mean0|c[7]~7_combout\);

-- Location: IOIBUF_X25_Y0_N52
\prob_1[9]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(9),
	o => \prob_1[9]~input_o\);

-- Location: FF_X14_Y10_N59
\mean0|a_stable_valid[9]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[9]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(9));

-- Location: IOIBUF_X34_Y0_N1
\prob_2[9]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(9),
	o => \prob_2[9]~input_o\);

-- Location: LABCELL_X14_Y10_N15
\mean0|b_stable_valid[9]~feeder\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|b_stable_valid[9]~feeder_combout\ = ( \prob_2[9]~input_o\ )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000011111111111111111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataf => \ALT_INV_prob_2[9]~input_o\,
	combout => \mean0|b_stable_valid[9]~feeder_combout\);

-- Location: FF_X14_Y10_N17
\mean0|b_stable_valid[9]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|b_stable_valid[9]~feeder_combout\,
	sclr => \mean0|process_0~0_combout\,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(9));

-- Location: LABCELL_X14_Y10_N57
\mean0|Add2~33\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~33_sumout\ = SUM(( \mean0|a_stable_valid\(9) ) + ( \mean0|b_stable_valid\(9) ) + ( \mean0|Add2~30\ ))
-- \mean0|Add2~34\ = CARRY(( \mean0|a_stable_valid\(9) ) + ( \mean0|b_stable_valid\(9) ) + ( \mean0|Add2~30\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111110000000000000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_a_stable_valid\(9),
	dataf => \mean0|ALT_INV_b_stable_valid\(9),
	cin => \mean0|Add2~30\,
	sumout => \mean0|Add2~33_sumout\,
	cout => \mean0|Add2~34\);

-- Location: MLABCELL_X18_Y8_N12
\mean0|c[8]~8\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[8]~8_combout\ = ( \mean0|init_flag_b~q\ & ( (\mean0|init_flag_a~q\ & \mean0|Add2~33_sumout\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000000001100110000000000110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_init_flag_a~q\,
	datad => \mean0|ALT_INV_Add2~33_sumout\,
	dataf => \mean0|ALT_INV_init_flag_b~q\,
	combout => \mean0|c[8]~8_combout\);

-- Location: IOIBUF_X16_Y0_N92
\prob_2[10]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(10),
	o => \prob_2[10]~input_o\);

-- Location: MLABCELL_X13_Y9_N36
\mean0|b_stable_valid[10]~feeder\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|b_stable_valid[10]~feeder_combout\ = ( \prob_2[10]~input_o\ )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000011111111111111111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataf => \ALT_INV_prob_2[10]~input_o\,
	combout => \mean0|b_stable_valid[10]~feeder_combout\);

-- Location: FF_X13_Y9_N37
\mean0|b_stable_valid[10]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|b_stable_valid[10]~feeder_combout\,
	sclr => \mean0|process_0~0_combout\,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(10));

-- Location: IOIBUF_X14_Y0_N1
\prob_1[10]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(10),
	o => \prob_1[10]~input_o\);

-- Location: FF_X14_Y9_N2
\mean0|a_stable_valid[10]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[10]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(10));

-- Location: LABCELL_X14_Y9_N0
\mean0|Add2~37\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~37_sumout\ = SUM(( \mean0|b_stable_valid\(10) ) + ( \mean0|a_stable_valid\(10) ) + ( \mean0|Add2~34\ ))
-- \mean0|Add2~38\ = CARRY(( \mean0|b_stable_valid\(10) ) + ( \mean0|a_stable_valid\(10) ) + ( \mean0|Add2~34\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111100001111000000000000000000000101010101010101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_b_stable_valid\(10),
	datac => \mean0|ALT_INV_a_stable_valid\(10),
	cin => \mean0|Add2~34\,
	sumout => \mean0|Add2~37_sumout\,
	cout => \mean0|Add2~38\);

-- Location: MLABCELL_X18_Y8_N15
\mean0|c[9]~9\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[9]~9_combout\ = ( \mean0|Add2~37_sumout\ & ( (\mean0|init_flag_b~q\ & \mean0|init_flag_a~q\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000010001000100010001000100010001",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_init_flag_b~q\,
	datab => \mean0|ALT_INV_init_flag_a~q\,
	dataf => \mean0|ALT_INV_Add2~37_sumout\,
	combout => \mean0|c[9]~9_combout\);

-- Location: IOIBUF_X54_Y15_N21
\prob_2[11]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(11),
	o => \prob_2[11]~input_o\);

-- Location: FF_X13_Y9_N43
\mean0|b_stable_valid[11]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_2[11]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(11));

-- Location: IOIBUF_X25_Y0_N1
\prob_1[11]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(11),
	o => \prob_1[11]~input_o\);

-- Location: FF_X14_Y9_N38
\mean0|a_stable_valid[11]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[11]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(11));

-- Location: LABCELL_X14_Y9_N3
\mean0|Add2~41\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~41_sumout\ = SUM(( \mean0|a_stable_valid\(11) ) + ( \mean0|b_stable_valid\(11) ) + ( \mean0|Add2~38\ ))
-- \mean0|Add2~42\ = CARRY(( \mean0|a_stable_valid\(11) ) + ( \mean0|b_stable_valid\(11) ) + ( \mean0|Add2~38\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000110011001100110000000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_b_stable_valid\(11),
	datad => \mean0|ALT_INV_a_stable_valid\(11),
	cin => \mean0|Add2~38\,
	sumout => \mean0|Add2~41_sumout\,
	cout => \mean0|Add2~42\);

-- Location: MLABCELL_X13_Y9_N54
\mean0|c[10]~10\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[10]~10_combout\ = ( \mean0|init_flag_a~q\ & ( (\mean0|init_flag_b~q\ & \mean0|Add2~41_sumout\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000101000001010000010100000101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_init_flag_b~q\,
	datac => \mean0|ALT_INV_Add2~41_sumout\,
	dataf => \mean0|ALT_INV_init_flag_a~q\,
	combout => \mean0|c[10]~10_combout\);

-- Location: IOIBUF_X33_Y0_N92
\prob_1[12]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(12),
	o => \prob_1[12]~input_o\);

-- Location: FF_X14_Y9_N8
\mean0|a_stable_valid[12]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[12]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(12));

-- Location: IOIBUF_X10_Y0_N92
\prob_2[12]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(12),
	o => \prob_2[12]~input_o\);

-- Location: FF_X13_Y9_N46
\mean0|b_stable_valid[12]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_2[12]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(12));

-- Location: LABCELL_X14_Y9_N6
\mean0|Add2~45\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~45_sumout\ = SUM(( \mean0|b_stable_valid\(12) ) + ( \mean0|a_stable_valid\(12) ) + ( \mean0|Add2~42\ ))
-- \mean0|Add2~46\ = CARRY(( \mean0|b_stable_valid\(12) ) + ( \mean0|a_stable_valid\(12) ) + ( \mean0|Add2~42\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000110011001100110000000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_a_stable_valid\(12),
	datac => \mean0|ALT_INV_b_stable_valid\(12),
	cin => \mean0|Add2~42\,
	sumout => \mean0|Add2~45_sumout\,
	cout => \mean0|Add2~46\);

-- Location: MLABCELL_X13_Y9_N57
\decision0|LessThan0~0\ : cyclonev_lcell_comb
-- Equation(s):
-- \decision0|LessThan0~0_combout\ = ( \mean0|init_flag_a~q\ & ( (\mean0|init_flag_b~q\ & \mean0|Add2~45_sumout\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000101000001010000010100000101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_init_flag_b~q\,
	datac => \mean0|ALT_INV_Add2~45_sumout\,
	dataf => \mean0|ALT_INV_init_flag_a~q\,
	combout => \decision0|LessThan0~0_combout\);

-- Location: IOIBUF_X10_Y0_N58
\prob_2[13]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(13),
	o => \prob_2[13]~input_o\);

-- Location: MLABCELL_X13_Y9_N0
\mean0|b_stable_valid[13]~feeder\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|b_stable_valid[13]~feeder_combout\ = ( \prob_2[13]~input_o\ )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000011111111111111111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataf => \ALT_INV_prob_2[13]~input_o\,
	combout => \mean0|b_stable_valid[13]~feeder_combout\);

-- Location: FF_X13_Y9_N1
\mean0|b_stable_valid[13]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|b_stable_valid[13]~feeder_combout\,
	sclr => \mean0|process_0~0_combout\,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(13));

-- Location: IOIBUF_X19_Y0_N1
\prob_1[13]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(13),
	o => \prob_1[13]~input_o\);

-- Location: FF_X14_Y9_N14
\mean0|a_stable_valid[13]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[13]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(13));

-- Location: LABCELL_X14_Y9_N9
\mean0|Add2~49\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~49_sumout\ = SUM(( \mean0|b_stable_valid\(13) ) + ( \mean0|a_stable_valid\(13) ) + ( \mean0|Add2~46\ ))
-- \mean0|Add2~50\ = CARRY(( \mean0|b_stable_valid\(13) ) + ( \mean0|a_stable_valid\(13) ) + ( \mean0|Add2~46\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111100001111000000000000000000000101010101010101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_b_stable_valid\(13),
	datac => \mean0|ALT_INV_a_stable_valid\(13),
	cin => \mean0|Add2~46\,
	sumout => \mean0|Add2~49_sumout\,
	cout => \mean0|Add2~50\);

-- Location: MLABCELL_X18_Y8_N33
\mean0|c[12]~11\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[12]~11_combout\ = ( \mean0|Add2~49_sumout\ & ( \mean0|init_flag_b~q\ & ( \mean0|init_flag_a~q\ ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_init_flag_a~q\,
	datae => \mean0|ALT_INV_Add2~49_sumout\,
	dataf => \mean0|ALT_INV_init_flag_b~q\,
	combout => \mean0|c[12]~11_combout\);

-- Location: IOIBUF_X36_Y0_N1
\prob_1[14]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(14),
	o => \prob_1[14]~input_o\);

-- Location: FF_X14_Y9_N47
\mean0|a_stable_valid[14]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[14]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(14));

-- Location: IOIBUF_X18_Y0_N52
\prob_2[14]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(14),
	o => \prob_2[14]~input_o\);

-- Location: LABCELL_X14_Y9_N54
\mean0|b_stable_valid[14]~feeder\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|b_stable_valid[14]~feeder_combout\ = ( \prob_2[14]~input_o\ )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000011111111111111111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataf => \ALT_INV_prob_2[14]~input_o\,
	combout => \mean0|b_stable_valid[14]~feeder_combout\);

-- Location: FF_X14_Y9_N56
\mean0|b_stable_valid[14]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|b_stable_valid[14]~feeder_combout\,
	sclr => \mean0|process_0~0_combout\,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(14));

-- Location: LABCELL_X14_Y9_N12
\mean0|Add2~53\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~53_sumout\ = SUM(( \mean0|b_stable_valid\(14) ) + ( \mean0|a_stable_valid\(14) ) + ( \mean0|Add2~50\ ))
-- \mean0|Add2~54\ = CARRY(( \mean0|b_stable_valid\(14) ) + ( \mean0|a_stable_valid\(14) ) + ( \mean0|Add2~50\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000110011001100110000000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_a_stable_valid\(14),
	datac => \mean0|ALT_INV_b_stable_valid\(14),
	cin => \mean0|Add2~50\,
	sumout => \mean0|Add2~53_sumout\,
	cout => \mean0|Add2~54\);

-- Location: MLABCELL_X18_Y8_N48
\mean0|c[13]~12\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[13]~12_combout\ = ( \mean0|init_flag_b~q\ & ( (\mean0|init_flag_a~q\ & \mean0|Add2~53_sumout\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000011000000110000001100000011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_init_flag_a~q\,
	datac => \mean0|ALT_INV_Add2~53_sumout\,
	dataf => \mean0|ALT_INV_init_flag_b~q\,
	combout => \mean0|c[13]~12_combout\);

-- Location: IOIBUF_X14_Y0_N35
\prob_1[15]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(15),
	o => \prob_1[15]~input_o\);

-- Location: FF_X14_Y9_N23
\mean0|a_stable_valid[15]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[15]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(15));

-- Location: IOIBUF_X0_Y21_N55
\prob_2[15]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(15),
	o => \prob_2[15]~input_o\);

-- Location: MLABCELL_X13_Y9_N3
\mean0|b_stable_valid[15]~feeder\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|b_stable_valid[15]~feeder_combout\ = ( \prob_2[15]~input_o\ )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000011111111111111111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataf => \ALT_INV_prob_2[15]~input_o\,
	combout => \mean0|b_stable_valid[15]~feeder_combout\);

-- Location: FF_X13_Y9_N4
\mean0|b_stable_valid[15]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|b_stable_valid[15]~feeder_combout\,
	sclr => \mean0|process_0~0_combout\,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(15));

-- Location: LABCELL_X14_Y9_N15
\mean0|Add2~57\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~57_sumout\ = SUM(( \mean0|b_stable_valid\(15) ) + ( \mean0|a_stable_valid\(15) ) + ( \mean0|Add2~54\ ))
-- \mean0|Add2~58\ = CARRY(( \mean0|b_stable_valid\(15) ) + ( \mean0|a_stable_valid\(15) ) + ( \mean0|Add2~54\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000101010101010101000000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_a_stable_valid\(15),
	datac => \mean0|ALT_INV_b_stable_valid\(15),
	cin => \mean0|Add2~54\,
	sumout => \mean0|Add2~57_sumout\,
	cout => \mean0|Add2~58\);

-- Location: MLABCELL_X18_Y8_N54
\mean0|c[14]~13\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[14]~13_combout\ = ( \mean0|Add2~57_sumout\ & ( (\mean0|init_flag_b~q\ & \mean0|init_flag_a~q\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000010001000100010001000100010001",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_init_flag_b~q\,
	datab => \mean0|ALT_INV_init_flag_a~q\,
	dataf => \mean0|ALT_INV_Add2~57_sumout\,
	combout => \mean0|c[14]~13_combout\);

-- Location: IOIBUF_X34_Y0_N18
\prob_1[16]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(16),
	o => \prob_1[16]~input_o\);

-- Location: FF_X14_Y9_N44
\mean0|a_stable_valid[16]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[16]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(16));

-- Location: IOIBUF_X0_Y19_N55
\prob_2[16]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(16),
	o => \prob_2[16]~input_o\);

-- Location: MLABCELL_X13_Y9_N27
\mean0|b_stable_valid[16]~feeder\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|b_stable_valid[16]~feeder_combout\ = ( \prob_2[16]~input_o\ )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000011111111111111111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataf => \ALT_INV_prob_2[16]~input_o\,
	combout => \mean0|b_stable_valid[16]~feeder_combout\);

-- Location: FF_X13_Y9_N28
\mean0|b_stable_valid[16]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|b_stable_valid[16]~feeder_combout\,
	sclr => \mean0|process_0~0_combout\,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(16));

-- Location: LABCELL_X14_Y9_N18
\mean0|Add2~61\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~61_sumout\ = SUM(( \mean0|b_stable_valid\(16) ) + ( \mean0|a_stable_valid\(16) ) + ( \mean0|Add2~58\ ))
-- \mean0|Add2~62\ = CARRY(( \mean0|b_stable_valid\(16) ) + ( \mean0|a_stable_valid\(16) ) + ( \mean0|Add2~58\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000110011001100110000000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_a_stable_valid\(16),
	datac => \mean0|ALT_INV_b_stable_valid\(16),
	cin => \mean0|Add2~58\,
	sumout => \mean0|Add2~61_sumout\,
	cout => \mean0|Add2~62\);

-- Location: MLABCELL_X18_Y8_N51
\mean0|c[15]~14\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[15]~14_combout\ = ( \mean0|Add2~61_sumout\ & ( (\mean0|init_flag_b~q\ & \mean0|init_flag_a~q\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000010001000100010001000100010001",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_init_flag_b~q\,
	datab => \mean0|ALT_INV_init_flag_a~q\,
	dataf => \mean0|ALT_INV_Add2~61_sumout\,
	combout => \mean0|c[15]~14_combout\);

-- Location: IOIBUF_X18_Y0_N35
\prob_1[17]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(17),
	o => \prob_1[17]~input_o\);

-- Location: FF_X14_Y9_N20
\mean0|a_stable_valid[17]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[17]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(17));

-- Location: IOIBUF_X10_Y0_N75
\prob_2[17]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(17),
	o => \prob_2[17]~input_o\);

-- Location: FF_X13_Y9_N34
\mean0|b_stable_valid[17]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_2[17]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(17));

-- Location: LABCELL_X14_Y9_N21
\mean0|Add2~65\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~65_sumout\ = SUM(( \mean0|b_stable_valid\(17) ) + ( \mean0|a_stable_valid\(17) ) + ( \mean0|Add2~62\ ))
-- \mean0|Add2~66\ = CARRY(( \mean0|b_stable_valid\(17) ) + ( \mean0|a_stable_valid\(17) ) + ( \mean0|Add2~62\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000101010101010101000000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_a_stable_valid\(17),
	datac => \mean0|ALT_INV_b_stable_valid\(17),
	cin => \mean0|Add2~62\,
	sumout => \mean0|Add2~65_sumout\,
	cout => \mean0|Add2~66\);

-- Location: MLABCELL_X18_Y8_N18
\mean0|c[16]~15\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[16]~15_combout\ = (\mean0|init_flag_b~q\ & (\mean0|init_flag_a~q\ & \mean0|Add2~65_sumout\))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000100000001000000010000000100000001000000010000000100000001",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_init_flag_b~q\,
	datab => \mean0|ALT_INV_init_flag_a~q\,
	datac => \mean0|ALT_INV_Add2~65_sumout\,
	combout => \mean0|c[16]~15_combout\);

-- Location: IOIBUF_X33_Y0_N75
\prob_1[18]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(18),
	o => \prob_1[18]~input_o\);

-- Location: FF_X14_Y9_N17
\mean0|a_stable_valid[18]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[18]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(18));

-- Location: IOIBUF_X11_Y0_N1
\prob_2[18]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(18),
	o => \prob_2[18]~input_o\);

-- Location: FF_X13_Y9_N22
\mean0|b_stable_valid[18]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_2[18]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(18));

-- Location: LABCELL_X14_Y9_N24
\mean0|Add2~69\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~69_sumout\ = SUM(( \mean0|b_stable_valid\(18) ) + ( \mean0|a_stable_valid\(18) ) + ( \mean0|Add2~66\ ))
-- \mean0|Add2~70\ = CARRY(( \mean0|b_stable_valid\(18) ) + ( \mean0|a_stable_valid\(18) ) + ( \mean0|Add2~66\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000110011001100110000000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_a_stable_valid\(18),
	datac => \mean0|ALT_INV_b_stable_valid\(18),
	cin => \mean0|Add2~66\,
	sumout => \mean0|Add2~69_sumout\,
	cout => \mean0|Add2~70\);

-- Location: MLABCELL_X18_Y8_N21
\mean0|c[17]~16\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[17]~16_combout\ = ( \mean0|Add2~69_sumout\ & ( (\mean0|init_flag_b~q\ & \mean0|init_flag_a~q\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000010001000100010001000100010001",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_init_flag_b~q\,
	datab => \mean0|ALT_INV_init_flag_a~q\,
	dataf => \mean0|ALT_INV_Add2~69_sumout\,
	combout => \mean0|c[17]~16_combout\);

-- Location: IOIBUF_X0_Y19_N4
\prob_2[19]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(19),
	o => \prob_2[19]~input_o\);

-- Location: FF_X13_Y9_N52
\mean0|b_stable_valid[19]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_2[19]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(19));

-- Location: IOIBUF_X11_Y0_N52
\prob_1[19]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(19),
	o => \prob_1[19]~input_o\);

-- Location: FF_X13_Y8_N35
\mean0|a_stable_valid[19]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[19]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(19));

-- Location: LABCELL_X14_Y9_N27
\mean0|Add2~73\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~73_sumout\ = SUM(( \mean0|b_stable_valid\(19) ) + ( \mean0|a_stable_valid\(19) ) + ( \mean0|Add2~70\ ))
-- \mean0|Add2~74\ = CARRY(( \mean0|b_stable_valid\(19) ) + ( \mean0|a_stable_valid\(19) ) + ( \mean0|Add2~70\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111100001111000000000000000000000101010101010101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_b_stable_valid\(19),
	datac => \mean0|ALT_INV_a_stable_valid\(19),
	cin => \mean0|Add2~70\,
	sumout => \mean0|Add2~73_sumout\,
	cout => \mean0|Add2~74\);

-- Location: MLABCELL_X18_Y8_N36
\mean0|c[18]~17\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[18]~17_combout\ = ( \mean0|Add2~73_sumout\ & ( (\mean0|init_flag_a~q\ & \mean0|init_flag_b~q\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000011000000110000001100000011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_init_flag_a~q\,
	datac => \mean0|ALT_INV_init_flag_b~q\,
	dataf => \mean0|ALT_INV_Add2~73_sumout\,
	combout => \mean0|c[18]~17_combout\);

-- Location: IOIBUF_X36_Y0_N35
\prob_2[20]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(20),
	o => \prob_2[20]~input_o\);

-- Location: LABCELL_X14_Y9_N48
\mean0|b_stable_valid[20]~feeder\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|b_stable_valid[20]~feeder_combout\ = ( \prob_2[20]~input_o\ )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000011111111111111111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataf => \ALT_INV_prob_2[20]~input_o\,
	combout => \mean0|b_stable_valid[20]~feeder_combout\);

-- Location: FF_X14_Y9_N50
\mean0|b_stable_valid[20]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|b_stable_valid[20]~feeder_combout\,
	sclr => \mean0|process_0~0_combout\,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(20));

-- Location: IOIBUF_X10_Y0_N41
\prob_1[20]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(20),
	o => \prob_1[20]~input_o\);

-- Location: FF_X13_Y8_N26
\mean0|a_stable_valid[20]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[20]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(20));

-- Location: LABCELL_X14_Y9_N30
\mean0|Add2~77\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~77_sumout\ = SUM(( \mean0|b_stable_valid\(20) ) + ( \mean0|a_stable_valid\(20) ) + ( \mean0|Add2~74\ ))
-- \mean0|Add2~78\ = CARRY(( \mean0|b_stable_valid\(20) ) + ( \mean0|a_stable_valid\(20) ) + ( \mean0|Add2~74\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000110011001100110000000000000000000101010101010101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_b_stable_valid\(20),
	datab => \mean0|ALT_INV_a_stable_valid\(20),
	cin => \mean0|Add2~74\,
	sumout => \mean0|Add2~77_sumout\,
	cout => \mean0|Add2~78\);

-- Location: MLABCELL_X18_Y8_N3
\mean0|c[19]~18\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[19]~18_combout\ = ( \mean0|init_flag_b~q\ & ( (\mean0|init_flag_a~q\ & \mean0|Add2~77_sumout\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000011000000110000001100000011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_init_flag_a~q\,
	datac => \mean0|ALT_INV_Add2~77_sumout\,
	dataf => \mean0|ALT_INV_init_flag_b~q\,
	combout => \mean0|c[19]~18_combout\);

-- Location: IOIBUF_X14_Y0_N52
\prob_1[21]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(21),
	o => \prob_1[21]~input_o\);

-- Location: FF_X14_Y9_N11
\mean0|a_stable_valid[21]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[21]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(21));

-- Location: IOIBUF_X0_Y20_N21
\prob_2[21]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(21),
	o => \prob_2[21]~input_o\);

-- Location: FF_X13_Y9_N20
\mean0|b_stable_valid[21]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_2[21]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(21));

-- Location: LABCELL_X14_Y9_N33
\mean0|Add2~81\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~81_sumout\ = SUM(( \mean0|b_stable_valid\(21) ) + ( \mean0|a_stable_valid\(21) ) + ( \mean0|Add2~78\ ))
-- \mean0|Add2~82\ = CARRY(( \mean0|b_stable_valid\(21) ) + ( \mean0|a_stable_valid\(21) ) + ( \mean0|Add2~78\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111100001111000000000000000000000000000011111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_a_stable_valid\(21),
	datad => \mean0|ALT_INV_b_stable_valid\(21),
	cin => \mean0|Add2~78\,
	sumout => \mean0|Add2~81_sumout\,
	cout => \mean0|Add2~82\);

-- Location: MLABCELL_X18_Y8_N42
\mean0|c[20]~19\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[20]~19_combout\ = ( \mean0|Add2~81_sumout\ & ( (\mean0|init_flag_a~q\ & \mean0|init_flag_b~q\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000011000000110000001100000011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_init_flag_a~q\,
	datac => \mean0|ALT_INV_init_flag_b~q\,
	dataf => \mean0|ALT_INV_Add2~81_sumout\,
	combout => \mean0|c[20]~19_combout\);

-- Location: IOIBUF_X54_Y15_N38
\prob_1[22]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(22),
	o => \prob_1[22]~input_o\);

-- Location: FF_X14_Y10_N22
\mean0|a_stable_valid[22]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[22]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(22));

-- Location: IOIBUF_X19_Y0_N35
\prob_2[22]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(22),
	o => \prob_2[22]~input_o\);

-- Location: FF_X13_Y9_N50
\mean0|b_stable_valid[22]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_2[22]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(22));

-- Location: LABCELL_X14_Y9_N36
\mean0|Add2~85\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~85_sumout\ = SUM(( \mean0|b_stable_valid\(22) ) + ( \mean0|a_stable_valid\(22) ) + ( \mean0|Add2~82\ ))
-- \mean0|Add2~86\ = CARRY(( \mean0|b_stable_valid\(22) ) + ( \mean0|a_stable_valid\(22) ) + ( \mean0|Add2~82\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000101010101010101000000000000000000011001100110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_a_stable_valid\(22),
	datab => \mean0|ALT_INV_b_stable_valid\(22),
	cin => \mean0|Add2~82\,
	sumout => \mean0|Add2~85_sumout\,
	cout => \mean0|Add2~86\);

-- Location: MLABCELL_X18_Y8_N39
\mean0|c[21]~20\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[21]~20_combout\ = ( \mean0|init_flag_b~q\ & ( (\mean0|init_flag_a~q\ & \mean0|Add2~85_sumout\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000000001100110000000000110011",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datab => \mean0|ALT_INV_init_flag_a~q\,
	datad => \mean0|ALT_INV_Add2~85_sumout\,
	dataf => \mean0|ALT_INV_init_flag_b~q\,
	combout => \mean0|c[21]~20_combout\);

-- Location: IOIBUF_X18_Y0_N1
\prob_1[23]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_1(23),
	o => \prob_1[23]~input_o\);

-- Location: FF_X14_Y9_N41
\mean0|a_stable_valid[23]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	asdata => \prob_1[23]~input_o\,
	sclr => \mean0|process_0~0_combout\,
	sload => VCC,
	ena => \mean0|a_stable_valid[15]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|a_stable_valid\(23));

-- Location: IOIBUF_X16_Y0_N41
\prob_2[23]~input\ : cyclonev_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_prob_2(23),
	o => \prob_2[23]~input_o\);

-- Location: MLABCELL_X13_Y9_N24
\mean0|b_stable_valid[23]~feeder\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|b_stable_valid[23]~feeder_combout\ = ( \prob_2[23]~input_o\ )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000011111111111111111111111111111111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataf => \ALT_INV_prob_2[23]~input_o\,
	combout => \mean0|b_stable_valid[23]~feeder_combout\);

-- Location: FF_X13_Y9_N25
\mean0|b_stable_valid[23]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \clk_voting~inputCLKENA0_outclk\,
	d => \mean0|b_stable_valid[23]~feeder_combout\,
	sclr => \mean0|process_0~0_combout\,
	ena => \mean0|b_stable_valid[9]~0_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \mean0|b_stable_valid\(23));

-- Location: LABCELL_X14_Y9_N39
\mean0|Add2~89\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|Add2~89_sumout\ = SUM(( \mean0|a_stable_valid\(23) ) + ( \mean0|b_stable_valid\(23) ) + ( \mean0|Add2~86\ ))

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000111111110000000000000000000000000000111100001111",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	datac => \mean0|ALT_INV_a_stable_valid\(23),
	dataf => \mean0|ALT_INV_b_stable_valid\(23),
	cin => \mean0|Add2~86\,
	sumout => \mean0|Add2~89_sumout\);

-- Location: MLABCELL_X18_Y8_N45
\mean0|c[22]~21\ : cyclonev_lcell_comb
-- Equation(s):
-- \mean0|c[22]~21_combout\ = ( \mean0|Add2~89_sumout\ & ( (\mean0|init_flag_b~q\ & \mean0|init_flag_a~q\) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000010001000100010001000100010001",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_init_flag_b~q\,
	datab => \mean0|ALT_INV_init_flag_a~q\,
	dataf => \mean0|ALT_INV_Add2~89_sumout\,
	combout => \mean0|c[22]~21_combout\);

-- Location: LABCELL_X14_Y10_N18
\decision0|LessThan0~1\ : cyclonev_lcell_comb
-- Equation(s):
-- \decision0|LessThan0~1_combout\ = ( !\mean0|Add2~17_sumout\ & ( !\mean0|Add2~1_sumout\ & ( (!\mean0|Add2~5_sumout\ & (!\mean0|Add2~9_sumout\ & (!\mean0|Add2~21_sumout\ & !\mean0|Add2~13_sumout\))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "1000000000000000000000000000000000000000000000000000000000000000",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_Add2~5_sumout\,
	datab => \mean0|ALT_INV_Add2~9_sumout\,
	datac => \mean0|ALT_INV_Add2~21_sumout\,
	datad => \mean0|ALT_INV_Add2~13_sumout\,
	datae => \mean0|ALT_INV_Add2~17_sumout\,
	dataf => \mean0|ALT_INV_Add2~1_sumout\,
	combout => \decision0|LessThan0~1_combout\);

-- Location: LABCELL_X14_Y10_N0
\decision0|LessThan0~2\ : cyclonev_lcell_comb
-- Equation(s):
-- \decision0|LessThan0~2_combout\ = ( !\mean0|Add2~29_sumout\ & ( (!\mean0|Add2~25_sumout\ & (!\mean0|Add2~37_sumout\ & !\mean0|Add2~33_sumout\)) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "1000000010000000000000000000000010000000100000000000000000000000",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_Add2~25_sumout\,
	datab => \mean0|ALT_INV_Add2~37_sumout\,
	datac => \mean0|ALT_INV_Add2~33_sumout\,
	datae => \mean0|ALT_INV_Add2~29_sumout\,
	combout => \decision0|LessThan0~2_combout\);

-- Location: MLABCELL_X13_Y9_N30
\decision0|LessThan0~3\ : cyclonev_lcell_comb
-- Equation(s):
-- \decision0|LessThan0~3_combout\ = ( \mean0|Add2~41_sumout\ & ( \mean0|Add2~45_sumout\ & ( (\mean0|init_flag_a~q\ & \mean0|init_flag_b~q\) ) ) ) # ( !\mean0|Add2~41_sumout\ & ( \mean0|Add2~45_sumout\ & ( (\mean0|init_flag_a~q\ & (\mean0|init_flag_b~q\ & 
-- ((!\decision0|LessThan0~1_combout\) # (!\decision0|LessThan0~2_combout\)))) ) ) )

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000101000001000000010100000101",
	shared_arith => "off")
-- pragma translate_on
PORT MAP (
	dataa => \mean0|ALT_INV_init_flag_a~q\,
	datab => \decision0|ALT_INV_LessThan0~1_combout\,
	datac => \mean0|ALT_INV_init_flag_b~q\,
	datad => \decision0|ALT_INV_LessThan0~2_combout\,
	datae => \mean0|ALT_INV_Add2~41_sumout\,
	dataf => \mean0|ALT_INV_Add2~45_sumout\,
	combout => \decision0|LessThan0~3_combout\);

-- Location: LABCELL_X6_Y21_N0
\~QUARTUS_CREATED_GND~I\ : cyclonev_lcell_comb
-- Equation(s):

-- pragma translate_off
GENERIC MAP (
	extended_lut => "off",
	lut_mask => "0000000000000000000000000000000000000000000000000000000000000000",
	shared_arith => "off")
-- pragma translate_on
;
END structure;


