set terminalDir [pwd]
set filesDir $terminalDir/waves

set waveFilename "wave"
set TopEntity "tb_stimulus_list"

vsim -view $filesDir/$waveFilename.wlf

add wave -noupdate -divider Clocks
add wave -noupdate  $waveFilename:$TopEntity/clk_rom_signal
add wave -noupdate  $waveFilename:$TopEntity/clk_simulation

add wave -noupdate -divider Inputs
add wave -noupdate  -radix unsigned $waveFilename:$TopEntity/address_signal

add wave -noupdate -divider Outputs
add wave -noupdate  -radix unsigned $waveFilename:$TopEntity/out_signal_distance
add wave -noupdate  -radix unsigned $waveFilename:$TopEntity/out_signal_speed
add wave -noupdate  -radix unsigned $waveFilename:$TopEntity/out_signal_deceleration
add wave -noupdate  -radix unsigned $waveFilename:$TopEntity/out_signal_enable_rf_1
add wave -noupdate  -radix unsigned $waveFilename:$TopEntity/out_signal_enable_rf_2