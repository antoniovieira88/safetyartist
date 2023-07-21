onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /stimuli_phy_tb_explainable_braking/clk_period_random_forest_1
add wave -noupdate /stimuli_phy_tb_explainable_braking/clk_period_random_forest_2
add wave -noupdate /stimuli_phy_tb_explainable_braking/clk_period_stimuli
add wave -noupdate /stimuli_phy_tb_explainable_braking/clk_period_voting
add wave -noupdate /stimuli_phy_tb_explainable_braking/clk_random_forest_1
add wave -noupdate /stimuli_phy_tb_explainable_braking/clk_random_forest_2
add wave -noupdate /stimuli_phy_tb_explainable_braking/clk_stimuli
add wave -noupdate /stimuli_phy_tb_explainable_braking/clk_voting
add wave -noupdate /stimuli_phy_tb_explainable_braking/prob_sel
add wave -noupdate /stimuli_phy_tb_explainable_braking/tb_iterate_and_run_test_case
add wave -noupdate /stimuli_phy_tb_explainable_braking/tb_reset
add wave -noupdate /stimuli_phy_tb_explainable_braking/test_cases
add wave -noupdate /stimuli_phy_tb_explainable_braking/valid_cycles_per_test_case
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {919000000000000 ps} 0} {{Cursor 2} {929000000000000 ps} 0}
quietly wave cursor active 2
configure wave -namecolwidth 395
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ps
update
WaveRestoreZoom {0 ps} {1067850 ms}
