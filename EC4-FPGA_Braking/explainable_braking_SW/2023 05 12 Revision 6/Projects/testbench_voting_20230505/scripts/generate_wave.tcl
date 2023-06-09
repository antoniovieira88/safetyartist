set terminalDir [pwd]
set filesDir $terminalDir/hardware
cd $filesDir

set TopEntity "testbench_voting"

vsim -voptargs=+acc work.$TopEntity -wlf ./../waves/wave.wlf

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
add wave -noupdate /testbench_voting/prob_valid_mean

add wave -noupdate -divider Signals
add wave -noupdate -radix decimal /testbench_voting/vote/mean0/sum
add wave -noupdate -radix decimal /testbench_voting/vote/mean0/c
add wave -noupdate /testbench_voting/vote/mean0/c_vld

run -all

quit -sim

quit -f