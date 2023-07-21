onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /rom_4096x16_tb/clk_rom_signal
add wave -noupdate /rom_4096x16_tb/clk_simulation
add wave -noupdate -radix unsigned /rom_4096x16_tb/address_signal
add wave -noupdate /rom_4096x16_tb/out_signal
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {1000000000 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 150
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ps
update
WaveRestoreZoom {0 ps} {21626486052 ps}
