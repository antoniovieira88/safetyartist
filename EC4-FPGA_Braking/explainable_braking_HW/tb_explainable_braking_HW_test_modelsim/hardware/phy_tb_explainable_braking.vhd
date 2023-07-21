library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_misc.all;
use ieee.numeric_std.all;
use ieee.math_real.all;

library work;
use work.Constants.all;
use work.Types.all;
use work.mux_package;

entity phy_tb_explainable_braking is
   generic (
        wordSize : natural := 24;
	    decimalSize : natural := 12;
        loss_comm : natural := 200;
        test_cases : natural := 94;
        valid_cycles_per_test_case: natural := 11
   );
   port (
        -- Inputs
        -- 0) Global testbench reset and test case iterator
        tb_reset : in std_logic;

        -- 1) Clock signals
        clk_random_forest_1 : in std_logic; -- Random forest 1 clock
        clk_random_forest_2 : in std_logic; -- Random forest 2 clock
        clk_voting : in std_logic; -- Voting clock
        clk_stimuli : in std_logic; -- Clock to generate the stimuli for each test case

        -- 2) Control signal for multiplexing test results on HEX displays and integer LED
        prob_sel : in std_logic_vector(1 downto 0);

        -- 3) Test case trigger: iterates to next test case and runs it when enabled
        tb_iterate_and_run_test_case : in std_logic;

        -- Outputs
        -- 1) HEX display-coded BCD digits of output probability chosen through prob_sel
        hexa_prob_0 : out std_logic_vector(6 downto 0); -- probability unit digit
        hexa_prob_1 : out std_logic_vector(6 downto 0); -- probability ten digit
        hexa_prob_2 : out std_logic_vector(6 downto 0); -- probability hundred digit
        hexa_prob_3 : out std_logic_vector(6 downto 0); -- probability thousand digit

        -- 2) HEX display-coded BCD digits of test case identification
        hexa_tc_4 : out std_logic_vector(6 downto 0); -- test case unit digit
        hexa_tc_5 : out std_logic_vector(6 downto 0); -- test case ten digit

        -- 3) LED to indicate whether the probability on hexa_prob is valid (always lower than 1)
        prob_int : out std_logic;

        -- 4) explainable_braking outputs
        db_prob_valid_1 : out std_logic;
        db_prob_valid_2 : out std_logic;
        prob_valid_mean : out std_logic;
        prediction : out std_logic;

        -- 5) Indication of test end
        finished_test_case: out std_logic; -- Indicates that a test case has been finished
        finished_tests : out std_logic     -- Indicates that all test cases have been finished
   );
end phy_tb_explainable_braking;

architecture phy_tb of phy_tb_explainable_braking is

    -- Declaration of components
    -- 1) Input stimuli generator
    component phy_stimuli_explainable_braking is
        generic(
            wordSize : natural := 24; -- size of probabilities delivered by the input providers
            decimalSize : natural := 12; -- number of bits for the decimal part of the delivered probabilities
            test_cases : natural := 94; -- number of test cases exercised with the physical testbench
            valid_delay : natural := 26;  -- number of clk_stimuli cycles to wait until enabling valid inputs
            valid_hold : natural := 266;  -- number of clk_stimuli cycles during which inputs shall be valid
            valid_rest : natural := 26   -- number of clk_stimuli cycles after valid_hold during which inputs shall remain invalid
        );
        port(
            -- testbench reset
            tb_reset : in std_logic;  
            -- clock for generating stimuli
            clk_stimuli : in std_logic;
            -- test case trigger: iterates to next test case and runs it when enabled
            tb_iterate_and_run_test_case : in std_logic;
            -- identification of the current test case
            test_case_id : in std_logic_vector(natural(ceil(log2(real(test_cases))))-1 downto 0);
            -- clock enable: signals used to test loss of communication from each random forest
            clk_enable_random_forest_1 : out std_logic;  -- clock enable for random forest 1 (active-high)
            clk_enable_random_forest_2 : out std_logic;  -- clock enable for random forest 2 (active-high)
            -- features
            distance : out std_logic_vector(wordSize-1 downto 0); 
            speed : out std_logic_vector(wordSize-1 downto 0);
            deceleration : out std_logic_vector(wordSize-1 downto 0);
            -- valid inputs
            input_valid : out std_logic; -- input valid
            -- reset for valid counters
            tb_valid_counters_reset : out std_logic

        );
    end component;

    -- 2) Counter of Module 'M' for test case iteration and test case finishing detection
    component counter_m is
        generic (
            constant M: integer := 100 -- counter module
        );
        port (
            clock    : in  std_logic;
            clear_as : in  std_logic;
            clear_s  : in  std_logic;
            enable   : in  std_logic;
            Q        : out std_logic_vector(natural(ceil(log2(real(M))))-1 downto 0);
            final    : out std_logic;
            mid      : out std_logic
        );
    end component;

    -- 3) Multiplexer of 'n_inputs' inputs with 'n_bits_input' bits each.
    component mux_m is
        generic(
            n_bits_input : natural := 12;   -- Bits in each input
            n_inputs     : natural := 4     -- Number of inputs
        );  
        port(
            v_i   : in  mux_package.slv_array_t(n_inputs - 1 downto 0)(n_bits_input - 1 downto 0);
            sel_i : in  std_logic_vector(natural(ceil(log2(real(n_inputs))))-1 downto 0);
            z_o   : out std_logic_vector(n_bits_input - 1 downto 0)
        );
    end component;

    -- 4) 4096x16 ROM for 12-bit Binary to 16-bit BCD Converter 
    component rom_4096x16 is
        port (
            address   : in  std_logic_vector(11 downto 0);
            clk       : in  std_logic;
            out_rom   : out std_logic_vector(15 downto 0)
         );
  	end component;

    -- 5) 4-bit Hexadecimal to 7-Segment Display Decoder
    component hexa7seg is
        port (
            hexa : in  std_logic_vector(3 downto 0);
            sseg : out std_logic_vector(6 downto 0)
        );
    end component;

    -- 6) explainable_braking
    component explainable_braking is
        generic(
            wordSize : natural := 24;
            decimalSize : natural := 12;
            loss_comm : natural := 1000
        );
        port(
            --- clocks
            clk_random_forest_1 : in std_logic;  -- clock used in forest 1 
            clk_random_forest_2 : in std_logic;  -- clock used in forest 2 
            clk_voting : in std_logic; -- clock used for averaging and prediction 
            -- features
            distance : in std_logic_vector(wordSize-1 downto 0); 
            speed : in std_logic_vector(wordSize-1 downto 0);
            deceleration : in std_logic_vector(wordSize-1 downto 0);
            -- valid inputs
            input_valid : in std_logic := '0'; -- input valid
            -- outputs
            prob_mean : out std_logic_vector(wordSize-1 downto 0); -- output score
            prob_valid_mean : out std_logic; -- output valid
            prediction : out std_logic;
            -- debugging outputs of the random forests
            db_prob_1 : out std_logic_vector(wordSize-1 downto 0); -- random forest 1 output score
            db_prob_valid_1 : out std_logic; -- random forest 1 'valid' output
            db_prob_2 : out std_logic_vector(wordSize-1 downto 0); -- random forest 2 output score
            db_prob_valid_2 : out std_logic -- random forest 2 'valid' output
        );
    end component;

    -- Signals
    -- 1) Signals connected to the input ports of the entity
    signal tb_reset_signal : std_logic;
    signal tb_iterate_and_run_test_case_signal : std_logic;
    signal clk_random_forest_1_signal : std_logic;
    signal clk_random_forest_2_signal : std_logic;
    signal clk_voting_signal : std_logic;
    signal clk_stimuli_signal : std_logic;
    signal prob_sel_signal: std_logic_vector(1 downto 0);

    -- 2) Signals connected to the output ports of the entity
    -- A) HEX display-coded BCD digits of output probability chosen through prob_sel
    signal hexa_prob_0_signal : std_logic_vector(6 downto 0); -- unit digit
    signal hexa_prob_1_signal : std_logic_vector(6 downto 0); -- ten digit
    signal hexa_prob_2_signal : std_logic_vector(6 downto 0); -- hundred digit
    signal hexa_prob_3_signal : std_logic_vector(6 downto 0); -- thousand digit

    -- B) HEX display-coded BCD digits of test case identification
    signal hexa_tc_4_signal : std_logic_vector(6 downto 0); -- unit digit
    signal hexa_tc_5_signal : std_logic_vector(6 downto 0); -- ten digit

    -- C) LED to indicate whether the probability on hexa_prob is valid (always lower than 1)
    signal prob_int_signal : std_logic;

    -- D) explainable_braking outputs
    signal db_prob_valid_1_signal : std_logic;
    signal db_prob_valid_2_signal : std_logic;
    signal prob_valid_mean_signal : std_logic;
    signal prediction_signal : std_logic;

    -- 3) Intermediate signals for the 'phy_stimuli_explainable_braking' instance outputs
    -- A) explainable_braking inputs
    signal distance_signal : std_logic_vector(wordSize-1 downto 0); 
    signal speed_signal : std_logic_vector(wordSize-1 downto 0);
    signal deceleration_signal : std_logic_vector(wordSize-1 downto 0);

    -- B) clock enable signals to test loss of communication from each random forest
    signal clk_enable_random_forest_1_signal : std_logic;  -- clock enable for random forest 1 (active-high)
	signal clk_enable_random_forest_2_signal : std_logic;  -- clock enable for random forest 2 (active-high)

    -- C) indication that the stimuli are valid to be read by the random forests
    signal input_valid_signal : std_logic;

    -- D) reset signal for 'valid' counters
    signal tb_valid_counters_reset_signal : std_logic;

    -- 4) Intermediate signals for the 'counter_m' instance used to iterate through test cases
    signal tc_clock_signal : std_logic;
    signal tc_counter_clear_s_signal : std_logic;
    signal tc_enable_signal : std_logic;
    signal tc_count_signal : std_logic_vector(natural(ceil(log2(real(test_cases))))-1 downto 0);
    signal tc_final_signal : std_logic;
    signal tc_mid_signal : std_logic;

    -- 5) Intermediate signal for the 'mux_m' instance used to control the outputs of
    -- hexa_prob_0 to hexa_prob_3 and prob_int
    signal mux_input_signal : mux_package.slv_array_t(3 downto 0)(wordSize-1 downto 0);
    signal mux_output_signal : std_logic_vector(wordSize-1 downto 0);

    -- 6) Intermediate signals for the 'rom_4096x16' instance connected to
    -- hexa_prob_0 to hexa_prob_3
    signal bcd_prob_output_signal : std_logic_vector(15 downto 0);

    -- 7) Intermediate signals for the 'rom_4096x16' instance connected to hexa_tc_4 and hexa_tc_5
    signal bcd_tc_input_signal : std_logic_vector(decimalSize-1 downto 0);
    signal zero_left_padding_signal : std_logic_vector(12-natural(ceil(log2(real(test_cases))))-1 downto 0);
    signal bcd_tc_output_signal : std_logic_vector(15 downto 0);

    -- 8) Intermediate signals for 'explainable_braking'
    -- A) Gated clocks
    signal clk_random_forest_1_enable_gated_signal : std_logic;
    signal clk_random_forest_2_enable_gated_signal : std_logic;
    signal clk_voting_gated_signal : std_logic;

    -- B) probability outputs
    signal prob_mean_signal : std_logic_vector(wordSize-1 downto 0);
    signal db_prob_1_signal : std_logic_vector(wordSize-1 downto 0);
    signal db_prob_2_signal : std_logic_vector(wordSize-1 downto 0);

    -- 9) Intermediate signals for rf1_valid_count_clock, which counts clk_random_forest_1 cycles during
    --    which the output db_prob_valid_1 has been in valid ('1') state. If clk_enable_random_forest_1_signal
    --    is disabled due to a loss of communication test, rf1_valid_counter counts clk_random_forest_1
    --    regardless of db_prob_valid_1.
    signal rf1_valid_count_clock : std_logic;
    signal rf1_valid_count_clear_as_signal : std_logic;
    signal rf1_valid_count_clear_s_signal : std_logic;
    signal rf1_valid_count_enable_signal : std_logic;
    signal rf1_valid_count_count_signal : std_logic_vector(natural(ceil(log2(real(valid_cycles_per_test_case - 1))))-1 downto 0);
    signal rf1_valid_count_final_signal : std_logic;
    signal rf1_valid_count_mid_signal : std_logic;

    -- 10) Intermediate signals for rf2_valid_count_clock, which counts clk_random_forest_2 cycles during
    --     which the output db_prob_valid_2 has been in valid ('1') state. If clk_enable_random_forest_2_signal
    --     is disabled due to a loss of communication test, rf2_valid_counter counts clk_random_forest_2
    --     regardless of db_prob_valid_2.
    signal rf2_valid_count_clock : std_logic;
    signal rf2_valid_count_clear_as_signal : std_logic;
    signal rf2_valid_count_clear_s_signal : std_logic;
    signal rf2_valid_count_enable_signal : std_logic;
    signal rf2_valid_count_count_signal : std_logic_vector(natural(ceil(log2(real(valid_cycles_per_test_case - 1))))-1 downto 0);
    signal rf2_valid_count_final_signal : std_logic;
    signal rf2_valid_count_mid_signal : std_logic;

    -- 11) Intermediate signals for voting_valid_count_clock, which counts clk_voting cycles during
    --     which the output prob_valid_mean has been in valid ('1') state. 
    signal voting_valid_count_clock : std_logic;
    signal voting_valid_count_clear_as_signal : std_logic;
    signal voting_valid_count_clear_s_signal : std_logic;
    signal voting_valid_count_enable_signal : std_logic;
    signal voting_valid_count_count_signal : std_logic_vector(natural(ceil(log2(real(valid_cycles_per_test_case - 1))))-1 downto 0);
    signal voting_valid_count_final_signal : std_logic;
    signal voting_valid_count_mid_signal : std_logic; 

begin

    -- Instantiation of components
    -- 1) Stimuli generator
    stimuli_generator: phy_stimuli_explainable_braking 
    generic map(
        wordSize => wordSize,
        decimalSize => decimalSize,
        test_cases => test_cases,        
        valid_delay => 26,
        valid_hold => 266,
        valid_rest => 26
    )
    port map(
        clk_stimuli => clk_stimuli_signal,
        tb_reset => tb_reset_signal,
        tb_iterate_and_run_test_case => tb_iterate_and_run_test_case_signal,
        test_case_id => tc_count_signal,
        clk_enable_random_forest_1 => clk_enable_random_forest_1_signal,
        clk_enable_random_forest_2 => clk_enable_random_forest_2_signal,
        distance => distance_signal,
        speed => speed_signal,
        deceleration => deceleration_signal,
        input_valid => input_valid_signal,
        tb_valid_counters_reset => tb_valid_counters_reset_signal
    );

    -- 2) Test case counter
    tc_counter: counter_m
    generic map (
        M  => test_cases
    )
    port map (
        clock    => tc_clock_signal,
        clear_as => tb_reset_signal,
        clear_s  => tc_counter_clear_s_signal,  -- Unused input. Set to '0'.
        enable   => tc_enable_signal,          -- To be generated by the control unit. Always at '1' except while running a test
        Q        => tc_count_signal,
        final    => tc_final_signal,
        mid      => tc_mid_signal  -- Unused output.
    );

    -- 3) Probability multiplexer
    prob_mux: mux_m
    generic map (
        n_bits_input => wordSize,
        n_inputs     => 4
    )
    port map (
        v_i   => mux_input_signal,
        sel_i => prob_sel_signal,
        z_o   => mux_output_signal
    );

    -- 4) Hex to BCD converter for the decimal part of prob_mux output.
    hex_bcd_prob: entity work.rom_4096x16
    port map (
        address => mux_output_signal(decimalSize-1 downto 0),
        clk => clk_stimuli_signal,
        out_rom => bcd_prob_output_signal
    );

    -- 5) Hex to BCD converter for tc_counter
    hex_bcd_tc: entity work.rom_4096x16
    port map (
        address => bcd_tc_input_signal,  -- To be defined with left zero padding along with tc_count_signal.
        clk => clk_stimuli_signal,
        out_rom => bcd_tc_output_signal
    );

    -- 6) 7-Segment Display for the unit of hex_bcd_prob
    sseg_hex0_prob: entity work.hexa7seg(behavioral)
    port map (
        hexa => bcd_prob_output_signal(3 downto 0),
        sseg => hexa_prob_0_signal
    );

    -- 7) 7-Segment Display for the ten of hex_bcd_prob
    sseg_hex1_prob: entity work.hexa7seg(behavioral)
    port map (
        hexa => bcd_prob_output_signal(7 downto 4),
        sseg => hexa_prob_1_signal
    );

    -- 8) 7-Segment Display for the hundred of hex_bcd_prob with burnt 4th segment
    sseg_hex2_prob: entity work.hexa7seg(behavioral_burntseg4)
    port map (
        hexa => bcd_prob_output_signal(11 downto 8),
        sseg => hexa_prob_2_signal
    );

    -- 9) 7-Segment Display for the thousand of hex_bcd_prob
    sseg_hex3_prob: entity work.hexa7seg(behavioral)
    port map (
        hexa => bcd_prob_output_signal(15 downto 12),
        sseg => hexa_prob_3_signal
    );

    -- 10) 7-Segment Display for the unit of hex_bcd_tc
    sseg_hex4_tc: entity work.hexa7seg(behavioral)
    port map (
        hexa => bcd_tc_output_signal(3 downto 0),
        sseg => hexa_tc_4_signal
    );

    -- 11) 7-Segment Display for the ten of hex_bcd_tc
    sseg_hex5_tc: entity work.hexa7seg(behavioral)
    port map (
        hexa => bcd_tc_output_signal(7 downto 4),
        sseg => hexa_tc_5_signal
    );

    -- 12) explainable_braking
    exp_braking: explainable_braking
    generic map (
        wordSize => wordSize,
        decimalSize => decimalSize,
        loss_comm => loss_comm        
    )
    port map (        
        clk_random_forest_1 => clk_random_forest_1_enable_gated_signal,
        clk_random_forest_2 => clk_random_forest_2_enable_gated_signal,
        clk_voting => clk_voting_gated_signal,
        distance => distance_signal,
        speed => speed_signal,
        deceleration => deceleration_signal,
        input_valid => input_valid_signal,
        prob_mean => prob_mean_signal,
        prob_valid_mean => prob_valid_mean_signal,
        prediction => prediction_signal,
        db_prob_1 => db_prob_1_signal,
        db_prob_valid_1 => db_prob_valid_1_signal,
        db_prob_2 => db_prob_2_signal,
        db_prob_valid_2 => db_prob_valid_2_signal
    );

    -- 13) Counter of clk_random_forest_1 cycles in which db_prob_valid_1 has been valid since
    --     beginning of a test case.
    rf1_valid_count: counter_m
    generic map (
        -- The counter module is set to valid_cycles_per_test_case - 1 in order to take into account
        -- a delay of one clock cycle in disabling db_prob_1_valid after the random forest 1 processing is finished
        M  => valid_cycles_per_test_case - 1
    )
    port map (
        clock    => rf1_valid_count_clock,
        clear_as => rf1_valid_count_clear_as_signal,
        clear_s  => rf1_valid_count_clear_s_signal,  -- Unused input. Set to '0'.
        enable   => rf1_valid_count_enable_signal,
        Q        => rf1_valid_count_count_signal,  -- Unused output.
        final    => rf1_valid_count_final_signal,
        mid      => rf1_valid_count_mid_signal  -- Unused output.
    );

    -- 14) Counter of clk_random_forest_2 cycles in which db_prob_valid_2 has been valid since
    --     beginning of a test case.
    rf2_valid_count: counter_m
    generic map (
        -- The counter module is set to valid_cycles_per_test_case - 1 in order to take into account
        -- a delay of one clock cycle in disabling db_prob_2_valid after the random forest 2 processing is finished
        M  => valid_cycles_per_test_case - 1
    )
    port map (
        clock    => rf2_valid_count_clock,
        clear_as => rf2_valid_count_clear_as_signal,
        clear_s  => rf2_valid_count_clear_s_signal,  -- Unused input. Set to '0'.
        enable   => rf2_valid_count_enable_signal,
        Q        => rf2_valid_count_count_signal,  -- Unused output.
        final    => rf2_valid_count_final_signal,
        mid      => rf2_valid_count_mid_signal  -- Unused output.
    );

    -- 15) Counter of clk_voting cycles in which prob_valid_mean has been valid since
    --     beginning of a test case.
    voting_valid_count: counter_m
    generic map (
        -- Counter module is set valid_cycles_per_test_case - 1 in order to take into account
        -- the delays refered to in the instanciation of rf1_valid_count and rf2_valid_count
        M  => valid_cycles_per_test_case - 1 
    )
    port map (
        clock    => voting_valid_count_clock,
        clear_as => voting_valid_count_clear_as_signal,
        clear_s  => voting_valid_count_clear_s_signal,  -- Unused input. Set to '0'.
        enable   => voting_valid_count_enable_signal,
        Q        => voting_valid_count_count_signal,  -- Unused output.
        final    => voting_valid_count_final_signal,
        mid      => voting_valid_count_mid_signal  -- Unused output.
    );

    -- Signal connections and logic relationships
    -- 1) Internal connections
    -- A) Gated clocks for the random forests and the voting component
    clk_random_forest_1_enable_gated_signal <= clk_enable_random_forest_1_signal and clk_random_forest_1_signal;
    clk_random_forest_2_enable_gated_signal <= clk_enable_random_forest_2_signal and clk_random_forest_2_signal;
    -- Note: Voting clock gating avoids voting loss of communication at the end of each test case
    clk_voting_gated_signal <= clk_voting_signal and not(tc_enable_signal); 

    -- B) tc_counter disabled synchronous reset of tc_counter and enable logic
    tc_counter_clear_s_signal <= '0';
    tc_enable_signal <= rf1_valid_count_final_signal and rf2_valid_count_final_signal and voting_valid_count_final_signal;

    -- C) Input of hex_bcd_tc
    zero_left_padding_signal <= (others => '0');
    bcd_tc_input_signal <= zero_left_padding_signal & tc_count_signal;

    -- D) Generation of prob_int_signal: OR combination of integer bits of the mux_output_signal
    prob_int_signal <=  mux_output_signal(23) or mux_output_signal(22) or mux_output_signal(21) or
                        mux_output_signal(20) or mux_output_signal(19) or mux_output_signal(18) or
                        mux_output_signal(17) or mux_output_signal(16) or mux_output_signal(15) or
                        mux_output_signal(14) or mux_output_signal(13) or mux_output_signal(12);

    -- E) prob_mux inputs
    mux_input_signal(0) <= prob_mean_signal; -- Positions 0 and 3 connected to prob_mean_signal
    mux_input_signal(1) <= db_prob_1_signal; -- Position 1 connected to db_prob_1_signal
    mux_input_signal(2) <= db_prob_2_signal; -- Position 2 connected to db_prob_2_signal
    mux_input_signal(3) <= prob_mean_signal; -- Positions 0 and 3 connected to prob_mean_signal

    -- F) rf1_valid_count signals
    rf1_valid_count_clock <= clk_random_forest_1_signal;
    rf1_valid_count_clear_as_signal <= tb_valid_counters_reset_signal; -- resets counter at the beginning of each test case
    rf1_valid_count_clear_s_signal <= '0'; -- disables synchronous clock
    rf1_valid_count_enable_signal <= (db_prob_valid_1_signal or not (clk_enable_random_forest_1_signal)) and not (rf1_valid_count_final_signal);

    -- G) rf2_valid_count signals
    rf2_valid_count_clock <= clk_random_forest_2_signal;
    rf2_valid_count_clear_as_signal <= tb_valid_counters_reset_signal; -- resets counter at the beginning of each test case
    rf2_valid_count_clear_s_signal <= '0'; -- disables synchronous clock
    rf2_valid_count_enable_signal <= (db_prob_valid_2_signal or not (clk_enable_random_forest_2_signal)) and not (rf2_valid_count_final_signal);

    -- H) voting_valid_count signals
    voting_valid_count_clock <= clk_voting_signal;
    voting_valid_count_clear_as_signal <= tb_valid_counters_reset_signal; -- resets counter at the beginning of each test case
    voting_valid_count_clear_s_signal <= '0'; -- disables synchronous clock
    voting_valid_count_enable_signal <= prob_valid_mean_signal and not (voting_valid_count_final_signal);
    
    -- 2) External connections to phy_tb_explainable_braking ports
    -- A) Signals connected to inputs
    tb_reset_signal <= not(tb_reset); -- Inverted logic because DE0-CV utilizes active-low buttons
    tb_iterate_and_run_test_case_signal <= not(tb_iterate_and_run_test_case); -- Inverted logic because DE0-CV utilizes active-low buttons
    clk_random_forest_1_signal <= clk_random_forest_1;
    clk_random_forest_2_signal <= clk_random_forest_2;
    clk_voting_signal <= clk_voting;
    clk_stimuli_signal <= clk_stimuli;
    tc_clock_signal <= tb_iterate_and_run_test_case_signal;
    prob_sel_signal <= prob_sel;
    -- B) Outputs connected to signals
    hexa_prob_0 <= hexa_prob_0_signal;
    hexa_prob_1 <= hexa_prob_1_signal;
    hexa_prob_2 <= hexa_prob_2_signal;
    hexa_prob_3 <= hexa_prob_3_signal;
    hexa_tc_4 <= hexa_tc_4_signal;
    hexa_tc_5 <= hexa_tc_5_signal;
    prob_int <= prob_int_signal;    
    db_prob_valid_1 <= db_prob_valid_1_signal;
    db_prob_valid_2 <= db_prob_valid_2_signal;
    prob_valid_mean <= prob_valid_mean_signal;
    prediction <= prediction_signal;
    finished_test_case <= tc_enable_signal;
    finished_tests <= tc_final_signal;
end phy_tb;