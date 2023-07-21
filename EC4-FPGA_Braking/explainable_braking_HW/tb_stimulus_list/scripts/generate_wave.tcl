set terminalDir [pwd]
set filesDir $terminalDir/hardware
cd $filesDir

set TopEntity "tb_stimulus_list"

vsim -voptargs=+acc work.$TopEntity -wlf ./../waves/wave.wlf

add wave -noupdate -divider Clocks
add wave -noupdate  $TopEntity/clk_rom_signal
add wave -noupdate  $TopEntity/clk_simulation

add wave -noupdate -divider Inputs
add wave -noupdate  -radix unsigned $TopEntity/address_signal

add wave -noupdate -divider Outputs
add wave -noupdate  -radix unsigned $TopEntity/out_signal_distance
add wave -noupdate  -radix unsigned $TopEntity/out_signal_speed
add wave -noupdate  -radix unsigned $TopEntity/out_signal_deceleration
add wave -noupdate  -radix unsigned $TopEntity/out_signal_enable_rf_1
add wave -noupdate  -radix unsigned $TopEntity/out_signal_enable_rf_2

run -all

quit -sim

quit -f