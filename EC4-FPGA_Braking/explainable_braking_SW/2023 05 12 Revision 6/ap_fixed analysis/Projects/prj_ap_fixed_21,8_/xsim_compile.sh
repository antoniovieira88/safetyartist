xvhdl -2008 -work BDT ./firmware/Constants.vhd
xvhdl -2008 -work BDT ./firmware/Types.vhd
xvhdl -2008 -work BDT ./firmware/Tree.vhd
xvhdl -2008 -work BDT ./firmware/AddReduce.vhd
xvhdl -2008 -work BDT ./firmware/Arrays0.vhd
xvhdl -2008 -work BDT ./firmware/BDT.vhd
xvhdl -2008 -work BDT ./firmware/BDTTop.vhd

xvhdl -2008 ./firmware/SimulationInput.vhd
xvhdl -2008 ./firmware/SimulationOutput.vhd
xvhdl -2008 ./firmware/BDTTestbench.vhd

xelab work.testbench -s bdt_tb