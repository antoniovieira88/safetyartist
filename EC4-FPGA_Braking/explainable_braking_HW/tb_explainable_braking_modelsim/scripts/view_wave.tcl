set terminalDir [pwd]
set filesDir $terminalDir/waves

set waveFilename "wave"
set TopEntity "tb_explainable_braking"

vsim -view $filesDir/$waveFilename.wlf

radix define fixed_24 -fixed -fraction 12 -precision 12 -signed

add wave -noupdate -divider Clocks
add wave -noupdate $waveFilename:/$TopEntity/Stimuli/clk_read
add wave -noupdate $waveFilename:/$TopEntity/Stimuli/clk_random_forest_1
add wave -noupdate $waveFilename:/$TopEntity/Stimuli/clk_random_forest_2
add wave -noupdate $waveFilename:/$TopEntity/Stimuli/clk_voting

add wave -noupdate -divider Inputs
add wave -noupdate -radix fixed_24 $waveFilename:/$TopEntity/Stimuli/distance
add wave -noupdate -radix fixed_24 $waveFilename:/$TopEntity/Stimuli/speed
add wave -noupdate -radix fixed_24 $waveFilename:/$TopEntity/Stimuli/deceleration

add wave -noupdate -divider Valid
add wave -noupdate -radix binary $waveFilename:/$TopEntity/Stimuli/input_valid

add wave -noupdate -divider Outputs
add wave -noupdate -radix fixed_24 $waveFilename:/$TopEntity/DUT/prob_mean
add wave -noupdate -radix binary $waveFilename:/$TopEntity/DUT/prob_valid_mean
add wave -noupdate -radix binary $waveFilename:/$TopEntity/DUT/prediction

add wave -noupdate -divider "Random Forest 1"
add wave -noupdate -radix fixed_24 $waveFilename:/$TopEntity/DUT/db_prob_1
add wave -noupdate -radix binary $waveFilename:/$TopEntity/DUT/db_prob_valid_1

add wave -noupdate -divider "Random Forest 2"
add wave -noupdate -radix fixed_24 $waveFilename:/$TopEntity/DUT/db_prob_2
add wave -noupdate -radix binary $waveFilename:/$TopEntity/DUT/db_prob_valid_2