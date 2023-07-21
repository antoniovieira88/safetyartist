set terminalDir [pwd]

set explainable_braking_files {"explainable_braking"}

set rf_1_files {"Constants" 
                "Types" 
                "Arrays0" 
                "casting" 
                "AddReduce" 
                "Tree" 
                "BDT" 
                "BDTTop"}

set rf_2_files {"Constants_2" 
                "Types_2" 
                "Arrays_2" 
                "casting_2" 
                "AddReduce_2" 
                "Tree_2" 
                "BDT_2" 
                "BDTTop_2"}

set voting_files {"mean" 
                "decision" 
                "voting"}

set test_utils_files {"counter_m" 
                    "edge_detector" 
                    "hexa7seg" 
                    "mux_package" 
                    "mux_m" 
                    "rom_4096x16"
                    "stimulus_list_clk_enable_rf_1" 
                    "stimulus_list_clk_enable_rf_2" 
                    "stimulus_list_deceleration"
                    "stimulus_list_speed"
                    "stimulus_list_distance"
                    "phy_stimuli_explainable_braking"}

set phy_tb_explainable_braking_files {"phy_tb_explainable_braking"}

set testbench_phy_tb_explainable_braking_files {"stimuli_phy_tb_explainable_braking"
                                                "testbench_phy_tb_explainable_braking"}



set filesDir $terminalDir/hardware


set explainable_braking_dir $filesDir/explainable_braking
set rf_1_dir $filesDir/random_forest_1
set rf_2_dir $filesDir/random_forest_2
set voting_dir $filesDir/voting
set test_utils_dir $filesDir/test_utils

set phy_tb_explainable_braking_dir $filesDir
set testbench_phy_tb_explainable_braking_dir $terminalDir

cd $filesDir

vlib work
vmap work work

foreach File $voting_files {
    vcom -2008 -quiet -reportprogress 300 -work work $voting_dir/$File.vhd
}

foreach File $rf_1_files {
    vcom -2008 -quiet -reportprogress 300 -work work $rf_1_dir/$File.vhd
}

foreach File $rf_2_files {
    vcom -2008 -quiet -reportprogress 300 -work work $rf_2_dir/$File.vhd
}

foreach File $explainable_braking_files {
    vcom -2008 -quiet -reportprogress 300 -work work $explainable_braking_dir/$File.vhd
}

foreach File $test_utils_files {
    vcom -2008 -quiet -reportprogress 300 -work work $test_utils_dir/$File.vhd
}

foreach File $phy_tb_explainable_braking_files {
    vcom -2008 -quiet -reportprogress 300 -work work $phy_tb_explainable_braking_dir/$File.vhd
}

foreach File $testbench_phy_tb_explainable_braking_files {
    vcom -2008 -quiet -reportprogress 300 -work work $testbench_phy_tb_explainable_braking_dir/$File.vhd
}

onerror { quit -f }

quit -f