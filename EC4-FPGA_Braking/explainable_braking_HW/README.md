Directory Structure:

explainable_braking_HW
Final VHDL design of the explainable braking control system

explainable_braking_HW_test_Quartus
Physical testbench for testing "explainable_braking_HW" on the terasIC DE0-CV board with Digilent Analog Discovery.

tb_XXX folders: ModelSim testbenches

tb_binary12bit_bcd16bit: Testbench for the "explainable_braking_HW_test_Quartus" component "rom_4096x16.vhd", which converts 12-bit binary numbers into 16-bit BCD numbers with a look-up table.

tb_casting_modelsim: Testbench for the "explainable_braking_HW" components "casting.vhd" and "casting_2.vhd", which convert data from HLS-generated types to std_logic / std_logic_vector and vice-versa.

tb_counter_m: Testbench for the "explainable_braking_HW_test_Quartus" component "counter_m.vhd", which implements a counter with generic module M.

tb_double_dabble_12bit: Testbench for the component "double_dabble_12bit", which converts 12-bit binary numbers into 16-bit BCD numbers by using an asynchronous implementation of the double dabble algorithm. This component was replaced by "rom_4096x16.vhd" for better performance and synthesizability.

tb_explainable_braking_HW_test_modelsim: Testbench for "explainable_braking_HW_test_Quartus".

tb_explainable_braking_modelsim: Testbench for "explainable_braking_HW".

tb_mux_m: Testbench for the "explainable_braking_HW_test_Quartus" component "mux_m.vhd", which implements a generic multiplexer with configurable number of inputs and input size.

tb_stimulus_list: Testbench for the "explainable_braking_HW_test_Quartus" components "stimulus_list_distance.vhd", "stimulus_list_speed.vhd", "stimulus_list_deceleration.vhd", "stimulus_list_clk_enable_rf_1.vhd", and "stimulus_list_clk_enable_rf_2.vhd". These components implement ROM modules with the input tuples (distance, speed, deceleration) for "explainable_braking_HW_test_Quartus", as well as the control for disabling the clock signals of random forests 1 and 2 to test the behavior of "explainable_braking_HW" when transient and permanent comunication loss occurs.
It also includes Jupyter Notebook scripts utilized to generate the aforementioned components (subfolder generators), as well as the dataset from which data has been extracted (subfolder dataset) and an Excel spreadsheet utilized to verify the proper data conversion to std_logic_vector with ap_fixed<24,12> format.

tb_virtual_stimuli_explainable_braking_HW_test: Testbench for the "tb_explainable_braking_HW_test_modelsim" component "stimuli_phy_tb_explainable_braking.vhd", which generates simulated stimuli to represent the respective inputs of "explainable_braking_HW_test_Quartus" produced by elements on the terasIC DE0-CV board and by Digilent Analog Discovery.