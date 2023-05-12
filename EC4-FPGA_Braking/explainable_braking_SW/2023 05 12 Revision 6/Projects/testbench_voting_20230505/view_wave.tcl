set scriptDir [pwd]
set waveFilename "wave"
puts $waveFilename

cd $scriptDir


vsim -view $waveFilename.wlf

add wave -noupdate -divider Clocks
add wave -noupdate $waveFilename:/testbench_voting/clk_read
add wave -noupdate $waveFilename:/testbench_voting/clk_voting

add wave -noupdate -divider Inputs
add wave -noupdate -radix decimal $waveFilename:/testbench_voting/prob_1
add wave -noupdate -radix decimal $waveFilename:/testbench_voting/prob_2
add wave -noupdate $waveFilename:/testbench_voting/prob_valid_1
add wave -noupdate $waveFilename:/testbench_voting/prob_valid_2

add wave -noupdate -divider Outputs
add wave -noupdate -radix decimal $waveFilename:/testbench_voting/prob_mean
add wave -noupdate $waveFilename:/testbench_voting/prediction

add wave -noupdate -divider Signals
add wave -noupdate -radix decimal $waveFilename:/testbench_voting/vote/mean0/sum
add wave -noupdate -radix decimal $waveFilename:/testbench_voting/vote/mean0/c
add wave -noupdate $waveFilename:/testbench_voting/vote/mean0/c_vld