library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_misc.all;
use ieee.numeric_std.all;

library work;
use work.Constants.all;
use work.Types.all;

entity tb_explainable_braking is
   generic (
        FileNameInput : string := "SimulationInput.txt";   -- file with the simulation inputs
        FilePath : string := "./../";  -- path for the files: at the root of the project directory

        wordSize : natural := 24;
	    decimalSize : natural := 12;
        loss_comm : natural := 1000 --absurd value, just for tests
   );
end tb_explainable_braking;

architecture behavioral of tb_explainable_braking is

    -- Declaration of signals

    -- Signals from Stimuli (INPUTS)
    --- clocks
    signal clk_random_forest_1_signal : std_logic;  -- clock used in florest 1 
    signal clk_random_forest_2_signal : std_logic;  -- clock used in florest 1 
    signal clk_voting_signal : std_logic; -- clock used for averaging and prediction 
    -- features
    signal distance_signal : std_logic_vector(wordSize-1 downto 0); 
    signal speed_signal : std_logic_vector(wordSize-1 downto 0);
    signal deceleration_signal : std_logic_vector(wordSize-1 downto 0);
    -- valid inputs
    signal input_valid_signal : std_logic := '0'; -- input valid

    -- Signals from DUT (OUTPUTS)
    signal prob_mean : std_logic_vector(wordSize-1 downto 0); -- output score
    signal prob_valid_mean : std_logic; -- output valid
    signal prediction : std_logic;
    -- debugging outputs of the random forests
	signal db_prob_1 : std_logic_vector(wordSize-1 downto 0); -- random forest 1 output score
	signal db_prob_valid_1 : std_logic; -- random forest 1 'valid' output
	signal db_prob_2 : std_logic_vector(wordSize-1 downto 0); -- random forest 2 output score
	signal db_prob_valid_2 : std_logic; -- random forest 2 'valid' output

begin

    -- Detailed description
    DUT: entity work.explainable_braking
    generic map(
        wordSize => wordSize,
        decimalSize => decimalSize,
        loss_comm => loss_comm
        
    )
    port map (
        -- clocks
        clk_random_forest_1 => clk_random_forest_1_signal,
        clk_random_forest_2 => clk_random_forest_2_signal,
        clk_voting => clk_voting_signal,
        -- features
        distance => distance_signal,
        speed => speed_signal,
        deceleration => deceleration_signal,
        -- valid inputs
        input_valid => input_valid_signal,
        -- outputs
        prob_mean => prob_mean,
        prob_valid_mean => prob_valid_mean,
        prediction => prediction,
        -- random forest debugging outputs
        db_prob_1 => db_prob_1,
        db_prob_valid_1 => db_prob_valid_1,
        db_prob_2 => db_prob_2,
        db_prob_valid_2 => db_prob_valid_2

    );

    Stimuli: entity work.stimuli_explainable_braking
    generic map (
		FileNameInput => FileNameInput,   -- file with the simulation inputs
		FilePath => FilePath,  -- path for the files: at the root of the project directory

		wordSize => wordSize, -- size of probabilities delivered by the input providers
		decimalSize => decimalSize -- number of bits for the decimal part of the delivered probabilities
    )
    port map (
        -- clocks
        clk_random_forest_1 => clk_random_forest_1_signal,
        clk_random_forest_2 => clk_random_forest_2_signal,
        clk_voting => clk_voting_signal,
        -- features 
        distance => distance_signal,
        speed => speed_signal,
        deceleration => deceleration_signal,
        -- valid inputs
        input_valid => input_valid_signal
    );

end behavioral;