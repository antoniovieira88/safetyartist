library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

use std.env.finish;

entity stimuli_phy_tb_explainable_braking is
    generic (
        test_cases : natural := 100;
        valid_cycles_per_test_case: natural := 16
    );
    port (
        -- Outputs
        -- 0) Global testbench reset and test case iterator
        tb_reset : out std_logic;

        -- 1) Clock signals
        clk_random_forest_1 : out std_logic; -- Random forest 1 clock
        clk_random_forest_2 : out std_logic; -- Random forest 2 clock
        clk_voting : out std_logic; -- Voting clock
        clk_stimuli : out std_logic; -- Clock to generate the stimuli for each test case

        -- 2) Control signal for multiplexing test results on HEX displays and integer LED
        prob_sel : out std_logic_vector(1 downto 0);

        -- 3) Test case trigger: iterates to next test case and runs it when enabled
        tb_iterate_and_run_test_case : out std_logic
    );
end entity;

architecture arch of stimuli_phy_tb_explainable_braking is 

--- Intermediate Signals
signal tb_reset_signal : std_logic := '1'; -- Starts with '1' to represent the active-low buttons of DE0-CV
signal clk_random_forest_1_signal : std_logic := '0';
signal clk_random_forest_2_signal : std_logic := '0';
signal clk_voting_signal : std_logic := '0';
signal clk_stimuli_signal : std_logic := '0';
signal prob_sel_signal : std_logic_vector(1 downto 0) := "00";
signal tb_iterate_and_run_test_case_signal : std_logic := '1';  -- Starts with '1' to represent the active-low buttons of DE0-CV

-- Clocks periods
constant clk_period_random_forest_1 : time := 2.5 ms; -- period of clk_random_forest_1
constant clk_period_random_forest_2 : time := 2.5 ms; -- period of clk_random_forest_2
constant clk_period_voting : time := 2.5 ms; -- period of clk_voting
constant clk_period_stimuli : time := 0.1 ms; -- period of clk_stimuli

begin       
    

    GenerateClkRF1 : process
    begin
        wait for clk_period_random_forest_1/2;
        clk_random_forest_1_signal <= not(clk_random_forest_1_signal);
    end process;

    GenerateClkRF2 : process
    begin
        wait for clk_period_random_forest_2/2;
        clk_random_forest_2_signal <= not(clk_random_forest_2_signal);
    end process;

    GenerateClkVoting : process
    begin
        wait for clk_period_voting/2;
        clk_voting_signal <= not(clk_voting_signal);
    end process;

    GenerateClkStimuli : process
    begin
        wait for clk_period_stimuli/2;
        clk_stimuli_signal <= not(clk_stimuli_signal);
    end process;
    
    GenerateOtherStimuli : process
    variable DelayIteration : time := 10000 ms; -- 10 seconds per test
    begin
        wait for DelayIteration/2; -- wait

        tb_reset_signal <= '0'; -- reset

        wait for DelayIteration/5; -- wait

        tb_reset_signal <= '1'; -- reset

        -- loop tests
        for i in 0 to test_cases loop
            wait for DelayIteration/5;
            tb_iterate_and_run_test_case_signal <= '0';

            wait for DelayIteration/5;
            tb_iterate_and_run_test_case_signal <= '1';
            prob_sel_signal <= "00";

            wait for DelayIteration/5;
            prob_sel_signal <= "01";

            wait for DelayIteration/5;
            prob_sel_signal <= "10";

            wait for DelayIteration/5;
            prob_sel_signal <= "11";
        end loop;

        std.env.finish; -- end
    end process;

    -- Output Attribution
    tb_reset <= tb_reset_signal;
    clk_random_forest_1 <= clk_random_forest_1_signal;
    clk_random_forest_2 <= clk_random_forest_2_signal;
    clk_voting <= clk_voting_signal;
    clk_stimuli <= clk_stimuli_signal;
    prob_sel <= prob_sel_signal;
    tb_iterate_and_run_test_case <= tb_iterate_and_run_test_case_signal;

end architecture;