set terminalDir [pwd]
set filesDir $terminalDir/hardware
cd $filesDir

set Files {"stimulus_list_distance" "stimulus_list_speed" "stimulus_list_deceleration" "stimulus_list_clk_enable_rf_2" "stimulus_list_clk_enable_rf_1" "tb_stimulus_list"}

vlib work
vmap work work

foreach File $Files {
    vcom -reportprogress 300 -work work $filesDir/$File.vhd
}

quit -f