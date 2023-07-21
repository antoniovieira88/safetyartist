set terminalDir [pwd]

set explainable_braking_files {"explainable_braking" "stimuli_explainable_braking" "tb_explainable_braking"}
set rf_1_files {"Constants" "Types" "Arrays0" "casting" "AddReduce" "Tree" "BDT" "BDTTop"}
set rf_2_files {"Constants_2" "Types_2" "Arrays_2" "casting_2" "AddReduce_2" "Tree_2" "BDT_2" "BDTTop_2"}
set voting_files {"mean" "decision" "voting"}

set filesDir $terminalDir/hardware

set explainable_braking_dir $filesDir
set rf_1_dir $filesDir/random_forest_1
set rf_2_dir $filesDir/random_forest_2
set voting_dir $filesDir/voting

cd $filesDir

vlib work
vmap work work

foreach File $voting_files {
    vcom -reportprogress 300 -work work $voting_dir/$File.vhd
}

foreach File $rf_1_files {
    vcom -reportprogress 300 -work work $rf_1_dir/$File.vhd
}

foreach File $rf_2_files {
    vcom -reportprogress 300 -work work $rf_2_dir/$File.vhd
}

foreach File $explainable_braking_files {
    vcom -reportprogress 300 -work work $explainable_braking_dir/$File.vhd
}

quit -f