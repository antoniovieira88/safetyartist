library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_misc.all;
use ieee.numeric_std.all;
use ieee.math_real.all;

entity phy_stimuli_explainable_braking is
    generic(
		wordSize : natural := 24; -- size of probabilities delivered by the input providers
		decimalSize : natural := 12; -- number of bits for the decimal part of the delivered probabilities
        test_cases : natural := 100; -- number of test cases exercised with the physical testbench
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
end phy_stimuli_explainable_braking;

architecture stimuli_generation of phy_stimuli_explainable_braking is

    -- Declaration of components
    -- 1) Counter of Module 'M' for quantifying delay, hold, and rest cycles for input_valid generation
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

    -- 2) ROM values for distance
    component stimulus_list_distance is
    port (
            address   : in  std_logic_vector(6 downto 0);
            clk       : in  std_logic;
            out_rom   : out std_logic_vector(23 downto 0)
        );
    end component;

    -- 3) ROM values for speed
    component stimulus_list_speed is
    port (
            address   : in  std_logic_vector(6 downto 0);
            clk       : in  std_logic;
            out_rom   : out std_logic_vector(23 downto 0)
        );
    end component;
    
    -- 4) ROM values for deceleration
    component stimulus_list_deceleration is
    port (
            address   : in  std_logic_vector(6 downto 0);
            clk       : in  std_logic;
            out_rom   : out std_logic_vector(23 downto 0)
        );
    end component;
    
    -- 5) ROM values for clk enable random forest 1
    component stimulus_list_clk_enable_rf_1 is
    port (
            address   : in  std_logic_vector(6 downto 0);
            clk       : in  std_logic;
            out_rom   : out std_logic
        );
    end component;
    
    -- 6) ROM values for clk enable random forest 2
    component stimulus_list_clk_enable_rf_2 is
    port (
            address   : in  std_logic_vector(6 downto 0);
            clk       : in  std_logic;
            out_rom   : out std_logic
        );
    end component;

    -- 7) Edge detector for generating short reset signals for hold, delay and reset counters.
    --    Also used for reset signals of phy_tb_explainable_braking 'valid' counters.
    component edge_detector is
    port (
         clock          : in  std_logic;
         reset          : in  std_logic;
         sensed_signal  : in  std_logic;
         out_pulse      : out std_logic
        );
    end component;

    -- Declaration of types and signals

    -- Signals connected to the output ports of the entity: Declaration and initialization with safe states
    signal clk_enable_random_forest_1_signal : std_logic := '0';
    signal clk_enable_random_forest_2_signal : std_logic := '0';
    signal distance_signal : std_logic_vector(wordSize-1 downto 0) := (others => '0');
    signal speed_signal : std_logic_vector(wordSize-1 downto 0) := (others => '1');
    signal deceleration_signal : std_logic_vector(wordSize-1 downto 0) := (others => '0');
    signal input_valid_signal : std_logic := '0';
    signal tb_valid_counters_reset_signal : std_logic := '0';

    -- Signals connected to the input ports of the entity:
    signal tb_reset_signal : std_logic;
    signal tb_iterate_and_run_test_case_signal : std_logic;
    
    -- Intermediate signals for ROMs
    signal address_signal : std_logic_vector(6 downto 0);
    signal clk_rom_signal : std_logic;

    -- Intermediate signals for delay_count.
    signal delay_count_clock : std_logic;
    signal delay_count_clear_as_signal : std_logic;
    signal delay_count_clear_s_signal : std_logic;
    signal delay_count_enable_signal : std_logic;
    signal delay_count_count_signal : std_logic_vector(natural(ceil(log2(real(valid_delay))))-1 downto 0);
    signal delay_count_final_signal : std_logic;
    signal delay_count_mid_signal : std_logic;

    -- Intermediate signals for hold_count.
    signal hold_count_clock : std_logic;
    signal hold_count_clear_as_signal : std_logic;
    signal hold_count_clear_s_signal : std_logic;
    signal hold_count_enable_signal : std_logic;
    signal hold_count_count_signal : std_logic_vector(natural(ceil(log2(real(valid_hold))))-1 downto 0);
    signal hold_count_final_signal : std_logic;
    signal hold_count_mid_signal : std_logic;

    -- Intermediate signals for rest_count.
    signal rest_count_clock : std_logic;
    signal rest_count_clear_as_signal : std_logic;
    signal rest_count_clear_s_signal : std_logic;
    signal rest_count_enable_signal : std_logic;
    signal rest_count_count_signal : std_logic_vector(natural(ceil(log2(real(valid_rest))))-1 downto 0);
    signal rest_count_final_signal : std_logic;
    signal rest_count_mid_signal : std_logic;

begin
    -- Generation of input_valid with counters and combinational logic
    -- 1) delay_count to wait for clk_stimuli cycles before enabling 'input_valid'
    delay_count: counter_m
    generic map (
        M  => valid_delay
    )
    port map (
        clock    => delay_count_clock,
        clear_as => delay_count_clear_as_signal,
        clear_s  => delay_count_clear_s_signal,  -- Unused input. Set to '0'.
        enable   => delay_count_enable_signal,
        Q        => delay_count_count_signal,  -- Unused output.
        final    => delay_count_final_signal,
        mid      => delay_count_mid_signal  -- Unused output.
    );

    -- 2) hold_count to keep 'input_valid' enabled for clk_stimuli cycles before disabling it
    hold_count: counter_m
    generic map (
        M  => valid_hold
    )
    port map (
        clock    => hold_count_clock,
        clear_as => hold_count_clear_as_signal,
        clear_s  => hold_count_clear_s_signal,  -- Unused input. Set to '0'.
        enable   => hold_count_enable_signal,
        Q        => hold_count_count_signal,  -- Unused output.
        final    => hold_count_final_signal,
        mid      => hold_count_mid_signal  -- Unused output.
    );

    -- 3) rest_count to keep 'input_valid' disabled after hold_count finished its count and until the next test case begins
    rest_count: counter_m
    generic map (
        M  => valid_rest
    )
    port map (
        clock    => rest_count_clock,
        clear_as => rest_count_clear_as_signal,
        clear_s  => rest_count_clear_s_signal,  -- Unused input. Set to '0'.
        enable   => rest_count_enable_signal,
        Q        => rest_count_count_signal,  -- Unused output.
        final    => rest_count_final_signal,
        mid      => rest_count_mid_signal  -- Unused output.
    );
    
    -- 4) ROM component instantiation for distance
    rom_distance: entity work.stimulus_list_distance
        port map ( 
            address  => address_signal,
            clk      => clk_rom_signal,
            out_rom  => distance_signal
        );
    
    -- 5) ROM component instantiation for speed
    rom_speed: entity work.stimulus_list_speed
        port map ( 
            address  => address_signal,
            clk      => clk_rom_signal,
            out_rom  => speed_signal
        );
    
    -- 6) ROM component instantiation for deceleration
    rom_deceleration: entity work.stimulus_list_deceleration
        port map ( 
            address  => address_signal,
            clk      => clk_rom_signal,
            out_rom  => deceleration_signal
        );
    
    -- 7) ROM component instantiation for clock enable random forest 1 
    rom_clk_enable_rf_1: entity work.stimulus_list_clk_enable_rf_1
        port map ( 
            address  => address_signal,
            clk      => clk_rom_signal,
            out_rom  => clk_enable_random_forest_1_signal
        );
    
    -- 8) ROM component instantiation for clock enable random forest 2
    rom_clk_enable_rf_2: entity work.stimulus_list_clk_enable_rf_2
        port map ( 
            address  => address_signal,
            clk      => clk_rom_signal,
            out_rom  => clk_enable_random_forest_2_signal
        );

    edge_reset: edge_detector
        port map (
            clock => clk_stimuli,
            reset => tb_reset_signal,
            sensed_signal => tb_iterate_and_run_test_case_signal,
            out_pulse => tb_valid_counters_reset_signal
        );

    -- 9) Connection of signals to generate input_valid
    -- A) delay_count signals
    delay_count_clock <= clk_stimuli;
    delay_count_clear_as_signal <= tb_valid_counters_reset_signal; -- resets counter at the beginning of each test case
    delay_count_clear_s_signal <= '0'; -- disables synchronous clock
    delay_count_enable_signal <= not(delay_count_final_signal); -- delay_count remains enabled until it reaches its final count

    -- B) hold_count signals
    hold_count_clock <= clk_stimuli;
    hold_count_clear_as_signal <= tb_valid_counters_reset_signal; -- resets counter at the beginning of each test case
    hold_count_clear_s_signal <= '0'; -- disables synchronous clock
    hold_count_enable_signal <= delay_count_final_signal and not(hold_count_final_signal); -- hold_count is enabled once delay_count finishes its count
                                                                                           -- and until hold_count finishes its count
    -- C) rest_count signals
    rest_count_clock <= clk_stimuli;
    rest_count_clear_as_signal <= tb_valid_counters_reset_signal; -- resets counter at the beginning of each test case
    rest_count_clear_s_signal <= '0'; -- disables synchronous clock
    rest_count_enable_signal <= hold_count_final_signal and not(rest_count_final_signal); -- rest_count is enabled once hold_count finishes its count
                                                                                          -- and until rest_count finishes its count

    -- D) Generation of input_valid_signal: it corresponds to hold_count_enable_signal
    input_valid_signal <= hold_count_enable_signal;
    
    -- 10) Connection of ROM signals to input ports
    address_signal <= test_case_id;
    clk_rom_signal <= clk_stimuli;
    
    -- Connection of intermediate signals to input and output ports
    tb_reset_signal <= tb_reset;
    tb_iterate_and_run_test_case_signal <= tb_iterate_and_run_test_case;
    clk_enable_random_forest_1 <= clk_enable_random_forest_1_signal;
    clk_enable_random_forest_2 <= clk_enable_random_forest_2_signal;
    distance <= distance_signal;
    speed <= speed_signal;
    deceleration <= deceleration_signal;
    input_valid <= input_valid_signal;
    tb_valid_counters_reset <= tb_valid_counters_reset_signal;

end architecture;