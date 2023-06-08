set terminalDir [pwd]
set filesDir $terminalDir/waves

set waveFilename "wave"

vsim -view $filesDir/$waveFilename.wlf

add wave -noupdate -divider Clocks
add wave -noupdate $waveFilename:/testbench_voting/clk_read
add wave -noupdate $waveFilename:/testbench_voting/clk_voting

add wave -noupdate -divider Inputs
add wave -noupdate -radix decimal $waveFilename:/testbench_voting/prob_1
add wave -noupdate -radix decimal $waveFilename:/testbench_voting/prob_2
add wave -noupdate -color Cyan $waveFilename:/testbench_voting/prob_valid_1
add wave -noupdate -color Magenta $waveFilename:/testbench_voting/prob_valid_2

add wave -noupdate -divider Outputs
add wave -noupdate -radix decimal $waveFilename:/testbench_voting/prob_mean
add wave -noupdate $waveFilename:/testbench_voting/prediction
add wave -noupdate -color Gold $waveFilename:/testbench_voting/vote/prob_valid_mean

add wave -noupdate -divider Signals
add wave -noupdate -radix decimal $waveFilename:/testbench_voting/vote/mean0/sum
add wave -noupdate -radix decimal $waveFilename:/testbench_voting/vote/mean0/c
add wave -noupdate $waveFilename:/testbench_voting/vote/mean0/c_vld