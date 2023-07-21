library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity testbench_phy_tb_explainable_braking is
end entity;

architecture arch of testbench_phy_tb_explainable_braking is 

    signal tb_reset_signal : std_logic;

    signal clk_random_forest_1_signal : std_logic;
    signal clk_random_forest_2_signal : std_logic;
    signal clk_voting_signal : std_logic;
    signal clk_stimuli_signal : std_logic;

    signal prob_sel_signal : std_logic_vector(1 downto 0);

    signal tb_iterate_and_run_test_case_signal : std_logic;

    signal hexa_prob_0_signal : std_logic_vector(6 downto 0); 
    signal hexa_prob_1_signal : std_logic_vector(6 downto 0); 
    signal hexa_prob_2_signal : std_logic_vector(6 downto 0); 
    signal hexa_prob_3_signal : std_logic_vector(6 downto 0); 

    signal hexa_tc_4_signal : std_logic_vector(6 downto 0);
    signal hexa_tc_5_signal : std_logic_vector(6 downto 0);

    signal prob_int_signal : std_logic;

    signal db_prob_valid_1_signal : std_logic;
    signal db_prob_valid_2_signal : std_logic;
    signal prob_valid_mean_signal : std_logic;
    signal prediction_signal : std_logic;

    signal finished_test_case_signal : std_logic;
    signal finished_tests_signal : std_logic;

    begin
        -- Port map and physical testbench instanciation
        DUT : entity work.phy_tb_explainable_braking 
        generic map (
            loss_comm => 200,
            test_cases => 94,
            valid_cycles_per_test_case => 11
        )
        port map (
            tb_reset => tb_reset_signal,
            -- 1) Clock signals
            clk_random_forest_1 => clk_random_forest_1_signal,
            clk_random_forest_2 => clk_random_forest_2_signal,
            clk_voting => clk_voting_signal,
            clk_stimuli => clk_stimuli_signal,
            -- 2) Control signal for multiplexing test results on HEX displays and integer LED
            prob_sel => prob_sel_signal,
            -- 3) Test case trigger: iterates to next test case and runs it when enabled
            tb_iterate_and_run_test_case => tb_iterate_and_run_test_case_signal,

            -- Outputs
            -- 1) HEX display-coded BCD digits of output probability chosen through prob_sel
            hexa_prob_0 => hexa_prob_0_signal, 
            hexa_prob_1 => hexa_prob_1_signal, 
            hexa_prob_2 => hexa_prob_2_signal, 
            hexa_prob_3 => hexa_prob_3_signal,

            -- 2) HEX display-coded BCD digits of test case identification
            hexa_tc_4 => hexa_tc_4_signal, 
            hexa_tc_5 => hexa_tc_5_signal, 

            -- 3) LED to indicate whether the probability on hexa_prob is valid (always lower than 1)
            prob_int => prob_int_signal,

            -- 4) explainable_braking outputs
            db_prob_valid_1 => db_prob_valid_1_signal,
            db_prob_valid_2 => db_prob_valid_2_signal,
            prob_valid_mean => prob_valid_mean_signal,
            prediction => prediction_signal,

            -- 5) Indication of test end
            finished_test_case => finished_test_case_signal,  -- Indicates that a test case has been finished
            finished_tests => finished_tests_signal   -- Indicates that all test cases have been finished
        );

        -- Port map and physical testbench instanciation
        stimuli : entity work.stimuli_phy_tb_explainable_braking 
        port map(
            tb_reset => tb_reset_signal,
            -- 1) Clock signals
            clk_random_forest_1 => clk_random_forest_1_signal,
            clk_random_forest_2 => clk_random_forest_2_signal,
            clk_voting => clk_voting_signal,
            clk_stimuli => clk_stimuli_signal,
            -- 2) Control signal for multiplexing test results on HEX displays and integer LED
            prob_sel => prob_sel_signal,
            -- 3) Test case trigger: iterates to next test case and runs it when enabled
            tb_iterate_and_run_test_case => tb_iterate_and_run_test_case_signal
        );
end architecture;