vsim -c -do "./scripts/compile.tcl" > ".\logs\compile.log"
vsim -c -do "./scripts/generate_wave.tcl" > ".\logs\generate_wave.log"
vsim -do "./scripts/view_wave.tcl"