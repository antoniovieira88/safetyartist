set scriptDir [pwd]
cd $scriptDir

set Files {"mean" "decision" "voting" "testbench_voting"}

vlib work
vmap work work

foreach File $Files {
    vcom -reportprogress 300 -work work $scriptDir/$File.vhd
}

quit -f