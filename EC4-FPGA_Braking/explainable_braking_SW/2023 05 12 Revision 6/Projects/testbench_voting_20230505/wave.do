onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -radix decimal /testbench_voting/prob_1
add wave -noupdate -radix decimal /testbench_voting/prob_2
add wave -noupdate -radix decimal /testbench_voting/prob_mean
add wave -noupdate /testbench_voting/prob_valid_1
add wave -noupdate /testbench_voting/prob_valid_2
add wave -noupdate /testbench_voting/prediction
add wave -noupdate /testbench_voting/clk_read
add wave -noupdate /testbench_voting/clk_voting
add wave -noupdate /testbench_voting/vote/mean0/init_flag
add wave -noupdate /testbench_voting/vote/mean0/init_flag_a
add wave -noupdate /testbench_voting/vote/mean0/init_flag_b
add wave -noupdate /testbench_voting/vote/mean0/valid_process
add wave -noupdate /testbench_voting/vote/mean0/valid_process_a
add wave -noupdate /testbench_voting/vote/mean0/valid_process_b
add wave -noupdate -radix decimal /testbench_voting/vote/mean0/a_stable_valid
add wave -noupdate -radix decimal /testbench_voting/vote/mean0/b_stable_valid
add wave -noupdate /testbench_voting/vote/mean0/loss_comm_count_a
add wave -noupdate /testbench_voting/vote/mean0/loss_comm_count_b
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {0 ps} 0}
quietly wave cursor active 0
configure wave -namecolwidth 150
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
WaveRestoreZoom {0 ps} {203437500 ns}
