set terminalDir [pwd]
set filesDir $terminalDir/hardware
cd $filesDir

set Files {"mean" "decision" "voting" "testbench_voting"}

vlib work
vmap work work

foreach File $Files {
    vcom -reportprogress 300 -work work $filesDir/$File.vhd
}

quit -f