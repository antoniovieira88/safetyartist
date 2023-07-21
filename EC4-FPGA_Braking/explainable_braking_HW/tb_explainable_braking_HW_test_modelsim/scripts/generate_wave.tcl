set terminalDir [pwd]
set filesDir $terminalDir/hardware
cd $filesDir

set TopEntity "testbench_phy_tb_explainable_braking"

vsim -voptargs=+acc work.$TopEntity -wlf ./../waves/wave.wlf

# phy_tb_explainable_braking
add wave -noupdate -divider phy_tb_explainable_braking

add wave -noupdate -group phy_tb_explainable_braking -divider Inputs
add wave -noupdate -group phy_tb_explainable_braking -radix unsigned -in $TopEntity/DUT/*

add wave -noupdate -group phy_tb_explainable_braking -divider Outputs
add wave -noupdate -group phy_tb_explainable_braking -radix unsigned -out $TopEntity/DUT/*

# stimuli_phy_tb_explainable_braking
add wave -noupdate -divider stimuli_phy_tb_explainable_braking

add wave -noupdate -group stimuli_phy_tb_explainable_braking -divider Outputs
add wave -noupdate -group stimuli_phy_tb_explainable_braking -radix unsigned -out $TopEntity/stimuli/*

# explainable_braking
add wave -noupdate -divider explainable_braking

add wave -noupdate -group random_forest_1 -divider Inputs
add wave -noupdate -group random_forest_1 -radix unsigned -in $TopEntity/DUT/exp_braking/random_forest_1/*
add wave -noupdate -group random_forest_1 -divider Outputs
add wave -noupdate -group random_forest_1 -radix unsigned -out $TopEntity/DUT/exp_braking/random_forest_1/*

add wave -noupdate -group random_forest_2 -divider Inputs
add wave -noupdate -group random_forest_2 -radix unsigned -in $TopEntity/DUT/exp_braking/random_forest_2/*
add wave -noupdate -group random_forest_2 -divider Outputs
add wave -noupdate -group random_forest_2 -radix unsigned -out $TopEntity/DUT/exp_braking/random_forest_2/*

add wave -noupdate -group voting -divider Inputs
add wave -noupdate -group voting -radix unsigned -in $TopEntity/DUT/exp_braking/voting0/*
add wave -noupdate -group voting -divider Outputs
add wave -noupdate -group voting -radix unsigned -out $TopEntity/DUT/exp_braking/voting0/*

# hex_bcd_prob
add wave -noupdate -divider hex_bcd_prob

add wave -noupdate -group hex_bcd_prob -divider Inputs
add wave -noupdate -group hex_bcd_prob -radix unsigned -in $TopEntity/DUT/hex_bcd_prob/*

add wave -noupdate -group hex_bcd_prob -divider Outputs
add wave -noupdate -group hex_bcd_prob -radix unsigned -out $TopEntity/DUT/hex_bcd_prob/*

# hex_bcd_tc
add wave -noupdate -divider hex_bcd_tc

add wave -noupdate -group hex_bcd_tc -divider Inputs
add wave -noupdate -group hex_bcd_tc -radix unsigned -in $TopEntity/DUT/hex_bcd_tc/*

add wave -noupdate -group hex_bcd_tc -divider Outputs
add wave -noupdate -group hex_bcd_tc -radix unsigned -out $TopEntity/DUT/hex_bcd_tc/*

# prob_mux
add wave -noupdate -divider prob_mux

add wave -noupdate -group prob_mux -divider Inputs
add wave -noupdate -group prob_mux -radix unsigned -in $TopEntity/DUT/prob_mux/*

add wave -noupdate -group prob_mux -divider Outputs
add wave -noupdate -group prob_mux -radix unsigned -out $TopEntity/DUT/prob_mux/*

# rf1_valid_count
add wave -noupdate -divider rf1_valid_count

add wave -noupdate -group rf1_valid_count -divider Inputs
add wave -noupdate -group rf1_valid_count -radix unsigned -in $TopEntity/DUT/rf1_valid_count/*

add wave -noupdate -group rf1_valid_count -divider Outputs
add wave -noupdate -group rf1_valid_count -radix unsigned -out $TopEntity/DUT/rf1_valid_count/*

# rf2_valid_count
add wave -noupdate -divider rf2_valid_count

add wave -noupdate -group rf2_valid_count -divider Inputs
add wave -noupdate -group rf2_valid_count -radix unsigned -in $TopEntity/DUT/rf2_valid_count/*

add wave -noupdate -group rf2_valid_count -divider Outputs
add wave -noupdate -group rf2_valid_count -radix unsigned -out $TopEntity/DUT/rf2_valid_count/*

# voting_valid_count
add wave -noupdate -divider voting_valid_count

add wave -noupdate -group voting_valid_count -divider Inputs
add wave -noupdate -group voting_valid_count -radix unsigned -in $TopEntity/DUT/voting_valid_count/*

add wave -noupdate -group voting_valid_count -divider Outputs
add wave -noupdate -group voting_valid_count -radix unsigned -out $TopEntity/DUT/voting_valid_count/*

# sseg_hex0_prob
add wave -noupdate -divider sseg_hex0_prob

add wave -noupdate -group sseg_hex0_prob -divider Inputs
add wave -noupdate -group sseg_hex0_prob -radix unsigned -in $TopEntity/DUT/sseg_hex0_prob/*

add wave -noupdate -group sseg_hex0_prob -divider Outputs
add wave -noupdate -group sseg_hex0_prob -radix unsigned -out $TopEntity/DUT/sseg_hex0_prob/*

# sseg_hex1_prob
add wave -noupdate -divider sseg_hex1_prob

add wave -noupdate -group sseg_hex1_prob -divider Inputs
add wave -noupdate -group sseg_hex1_prob -radix unsigned -in $TopEntity/DUT/sseg_hex1_prob/*

add wave -noupdate -group sseg_hex1_prob -divider Outputs
add wave -noupdate -group sseg_hex1_prob -radix unsigned -out $TopEntity/DUT/sseg_hex1_prob/*

# sseg_hex2_prob
add wave -noupdate -divider sseg_hex2_prob

add wave -noupdate -group sseg_hex2_prob -divider Inputs
add wave -noupdate -group sseg_hex2_prob -radix unsigned -in $TopEntity/DUT/sseg_hex2_prob/*

add wave -noupdate -group sseg_hex2_prob -divider Outputs
add wave -noupdate -group sseg_hex2_prob -radix unsigned -out $TopEntity/DUT/sseg_hex2_prob/*

# sseg_hex3_prob
add wave -noupdate -divider sseg_hex3_prob

add wave -noupdate -group sseg_hex3_prob -divider Inputs
add wave -noupdate -group sseg_hex3_prob -radix unsigned -in $TopEntity/DUT/sseg_hex3_prob/*

add wave -noupdate -group sseg_hex3_prob -divider Outputs
add wave -noupdate -group sseg_hex3_prob -radix unsigned -out $TopEntity/DUT/sseg_hex3_prob/*

# sseg_hex4_tc
add wave -noupdate -divider sseg_hex4_tc

add wave -noupdate -group sseg_hex4_tc -divider Inputs
add wave -noupdate -group sseg_hex4_tc -radix unsigned -in $TopEntity/DUT/sseg_hex4_tc/*

add wave -noupdate -group sseg_hex4_tc -divider Outputs
add wave -noupdate -group sseg_hex4_tc -radix unsigned -out $TopEntity/DUT/sseg_hex4_tc/*

# sseg_hex5_tc
add wave -noupdate -divider sseg_hex5_tc

add wave -noupdate -group sseg_hex5_tc -divider Inputs
add wave -noupdate -group sseg_hex5_tc -radix unsigned -in $TopEntity/DUT/sseg_hex5_tc/*

add wave -noupdate -group sseg_hex5_tc -divider Outputs
add wave -noupdate -group sseg_hex5_tc -radix unsigned -out $TopEntity/DUT/sseg_hex5_tc/*

# stimuli_generator
add wave -noupdate -divider stimuli_generator

add wave -noupdate -group stimuli_generator -divider Inputs
add wave -noupdate -group stimuli_generator -radix unsigned -in $TopEntity/DUT/stimuli_generator/*

add wave -noupdate -group stimuli_generator -divider Outputs
add wave -noupdate -group stimuli_generator -radix unsigned -out $TopEntity/DUT/stimuli_generator/*

# tc_counter
add wave -noupdate -divider tc_counter

add wave -noupdate -group tc_counter -divider Inputs
add wave -noupdate -group tc_counter -radix unsigned -in $TopEntity/DUT/tc_counter/*

add wave -noupdate -group tc_counter -divider Outputs
add wave -noupdate -group tc_counter -radix unsigned -out $TopEntity/DUT/tc_counter/*

run -all