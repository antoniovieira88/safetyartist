set terminalDir [pwd]
set filesDir $terminalDir/hardware
cd $filesDir

set TopEntity "tb_explainable_braking"

vsim -voptargs=+acc work.$TopEntity -wlf ./../waves/wave.wlf

radix define fixed_24 -fixed -fraction 12 -precision 12 -signed

add wave -noupdate -divider Clocks
add wave -noupdate /$TopEntity/Stimuli/clk_read
add wave -noupdate /$TopEntity/Stimuli/clk_random_forest_1
add wave -noupdate /$TopEntity/Stimuli/clk_random_forest_2
add wave -noupdate /$TopEntity/Stimuli/clk_voting

add wave -noupdate -divider Inputs
add wave -noupdate -radix fixed_24 /$TopEntity/Stimuli/distance
add wave -noupdate -radix fixed_24 /$TopEntity/Stimuli/speed
add wave -noupdate -radix fixed_24 /$TopEntity/Stimuli/deceleration

add wave -noupdate -divider Valid
add wave -noupdate -radix binary /$TopEntity/Stimuli/input_valid

add wave -noupdate -divider Outputs
add wave -noupdate -radix fixed_24 /$TopEntity/DUT/prob_mean
add wave -noupdate -radix binary /$TopEntity/DUT/prob_valid_mean
add wave -noupdate -radix binary /$TopEntity/DUT/prediction

add wave -noupdate -divider "Random Forest 1"
add wave -noupdate -radix fixed_24 /$TopEntity/DUT/db_prob_1
add wave -noupdate -radix binary /$TopEntity/DUT/db_prob_valid_1

add wave -noupdate -divider "Random Forest 2"
add wave -noupdate -radix fixed_24 /$TopEntity/DUT/db_prob_2
add wave -noupdate -radix binary /$TopEntity/DUT/db_prob_valid_2

run -all

quit -sim

quit -f