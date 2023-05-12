set scriptDir [pwd]
set TopEntity "testbench_voting"
cd $scriptDir

vsim -voptargs=+acc work.$TopEntity -wlf wave.wlf

add wave -noupdate -divider Clocks
add wave -noupdate /testbench_voting/clk_read
add wave -noupdate /testbench_voting/clk_voting

add wave -noupdate -divider Inputs
add wave -noupdate -radix decimal /testbench_voting/prob_1
add wave -noupdate -radix decimal /testbench_voting/prob_2
add wave -noupdate /testbench_voting/prob_valid_1
add wave -noupdate /testbench_voting/prob_valid_2

add wave -noupdate -divider Outputs
add wave -noupdate -radix decimal /testbench_voting/prob_mean
add wave -noupdate /testbench_voting/prediction

add wave -noupdate -divider Signals
add wave -noupdate -radix decimal /testbench_voting/vote/mean0/sum
add wave -noupdate -radix decimal /testbench_voting/vote/mean0/c
add wave -noupdate /testbench_voting/vote/mean0/c_vld

run -all

add list *

write list test.lst

quit -sim

quit -f