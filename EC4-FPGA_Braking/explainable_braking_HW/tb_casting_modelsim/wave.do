onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /tb_casting/in_bool_array
add wave -noupdate /tb_casting/out1_bool
add wave -noupdate /tb_casting/out0_bool
add wave -noupdate /tb_casting/out1_std_logic
add wave -noupdate /tb_casting/out0_std_logic
add wave -noupdate /tb_casting/out_std_logic_vector
add wave -noupdate /tb_casting/in_tx
add wave -noupdate /tb_casting/out_std_logic_vector_tx
add wave -noupdate /tb_casting/in_ty
add wave -noupdate /tb_casting/out_std_logic_vector_ty
add wave -noupdate /tb_casting/in_txArray
add wave -noupdate /tb_casting/out_std_logic_vector_txArray
add wave -noupdate /tb_casting/in_tyArray
add wave -noupdate /tb_casting/out_std_logic_vector_tyArray
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {0 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 150
configure wave -valuecolwidth 234
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
WaveRestoreZoom {0 ps} {874 ps}
