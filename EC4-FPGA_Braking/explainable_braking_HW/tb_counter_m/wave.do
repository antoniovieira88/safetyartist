onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /counter_m_tb/clock_in
add wave -noupdate /counter_m_tb/clear_as_in
add wave -noupdate /counter_m_tb/clear_s_in
add wave -noupdate /counter_m_tb/enable_in
add wave -noupdate -radix unsigned /counter_m_tb/q_out
add wave -noupdate /counter_m_tb/final_out
add wave -noupdate /counter_m_tb/mid_out
add wave -noupdate /counter_m_tb/test_case
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {0 ps} 0}
quietly wave cursor active 0
configure wave -namecolwidth 186
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
WaveRestoreZoom {11339610807218 ps} {11645283641725 ps}
