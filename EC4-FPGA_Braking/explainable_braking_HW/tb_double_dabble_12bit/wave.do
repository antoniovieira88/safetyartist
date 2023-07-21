onerror {resume}
quietly virtual signal -install /double_dabble_tb { /double_dabble_tb/bcd(15 downto 12)} bcd1000
quietly virtual signal -install /double_dabble_tb { /double_dabble_tb/bcd(11 downto 8)} bcd100
quietly virtual signal -install /double_dabble_tb { /double_dabble_tb/bcd(7 downto 4)} bcd_10
quietly virtual signal -install /double_dabble_tb { /double_dabble_tb/bcd(3 downto 0)} bcd_1
quietly WaveActivateNextPane {} 0
add wave -noupdate -radix decimal /double_dabble_tb/binary
add wave -noupdate -radix decimal /double_dabble_tb/bcd1000
add wave -noupdate -radix decimal /double_dabble_tb/bcd100
add wave -noupdate -radix decimal /double_dabble_tb/bcd_10
add wave -noupdate -radix decimal /double_dabble_tb/bcd_1
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {0 ps} 0}
quietly wave cursor active 0
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
WaveRestoreZoom {0 ps} {997 ps}
