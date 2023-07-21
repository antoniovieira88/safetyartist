onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /mux_m_tb/clock
add wave -noupdate /mux_m_tb/keep_simulating
add wave -noupdate /mux_m_tb/in0
add wave -noupdate /mux_m_tb/in1
add wave -noupdate /mux_m_tb/in2
add wave -noupdate /mux_m_tb/in3
add wave -noupdate /mux_m_tb/sel
add wave -noupdate /mux_m_tb/mux_out
add wave -noupdate /mux_m_tb/test_case
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {499999306 ps} 0}
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
WaveRestoreZoom {0 ps} {11025 us}
