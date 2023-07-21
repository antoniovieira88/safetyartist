library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_misc.all;
use ieee.numeric_std.all;

library work;
use work.Constants.all;
use work.Types.all;
use work.Arrays0;
use work.casting.all; 

use work.Constants_2.all;
use work.Types_2.all;
use work.Arrays_2;
use work.casting_2.all;

entity explainable_braking is
	generic(
		wordSize : natural := 24;
		decimalSize : natural := 12;
		loss_comm : natural := 1000 -- absurd value, just for tests
	);
	port(
		--- clocks
		clk_random_forest_1 : in std_logic;  -- clock used in florest 1 
		clk_random_forest_2 : in std_logic;  -- clock used in florest 1 
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
end explainable_braking;
  
architecture rtl of explainable_braking is 

-- necessary signals to proper connect the components --
signal prob_1_signal : work.Types.tyArray(0 to work.Constants.nClasses-1);
signal prob_2_signal : work.Types_2.tyArray(0 to work.Constants_2.nClasses-1);

signal prob_valid_1_signal : work.Types.boolArray(0 to work.Constants.nClasses-1);
signal prob_valid_2_signal : work.Types_2.boolArray(0 to work.Constants_2.nClasses-1);

signal prob_valid_1_signal_voter : std_logic;
signal prob_valid_2_signal_voter : std_logic;
--------------------------------------------------------

signal X_1 : work.Types.txArray(work.Constants.nFeatures-1 downto 0); -- array of txs (inputs) for random forest 1
signal X_2 : work.Types_2.txArray(work.Constants_2.nFeatures-1 downto 0); -- array of txs (inputs) for random forest 2

begin
    random_forest_1 : entity work.BDTTop
    port map (
			clk => clk_random_forest_1,
			X => X_1,
			X_vld => work.casting.std_to_bool(input_valid), -- cast std_logic to boolean
			y => prob_1_signal,
			y_vld => prob_valid_1_signal
    );

    random_forest_2 : entity work.BDTTop_2
    port map (
			clk => clk_random_forest_2,
			X => X_2,
			X_vld => work.casting.std_to_bool(input_valid), -- cast std_logic to boolean
			y => prob_2_signal,
			y_vld => prob_valid_2_signal
    );

    voting0 : entity work.voting
	 generic map (
			wordSize => wordSize,
			decimalSize => decimalSize,
			loss_comm => loss_comm
	 )
    port map (
			prob_1 => work.casting.tyArray_to_std(prob_1_signal), -- cast tyArray to std_logic_vector
			prob_2 => work.casting_2.tyArray_to_std(prob_2_signal), -- cast tyArray to std_logic_vector
			prob_valid_1 => prob_valid_1_signal_voter,
			prob_valid_2 => prob_valid_2_signal_voter,
			clk_voting => clk_voting, 
			prob_mean => prob_mean,
			prediction => prediction,
			prob_valid_mean => prob_valid_mean
    );

	 -- Inputs for random forest 1
	 -- to_tx only accepts integers, then we must cast the std_logic_vector to integer
	 -- order as per the random forest design: X(2) => distance, X(1) => speed, X(0) => deceleration
	 X_1(2) <= work.Constants.to_tx(to_integer(unsigned(distance)));
	 X_1(1) <= work.Constants.to_tx(to_integer(unsigned(speed)));
	 X_1(0) <= work.Constants.to_tx(to_integer(unsigned(deceleration)));
	 
	 -- Inputs for random forest 2
	 -- to_tx only accepts integers, then we must cast the std_logic_vector to integer	 
	 -- order as per the random forest design: X(2) => distance, X(1) => speed, X(0) => deceleration
	 X_2(2) <= work.Constants_2.to_tx(to_integer(unsigned(distance)));
	 X_2(1) <= work.Constants_2.to_tx(to_integer(unsigned(speed)));
	 X_2(0) <= work.Constants_2.to_tx(to_integer(unsigned(deceleration)));

	 -- prob_valid Inputs for voting
	 prob_valid_1_signal_voter <= work.casting.boolArray_to_std(prob_valid_1_signal)(0); -- cast boolArray to std_logic_vector and gets the first and only element
	 prob_valid_2_signal_voter <= work.casting_2.boolArray_to_std(prob_valid_2_signal)(0); -- cast boolArray to std_logic_vector and gets the first and only element

	 -- Debugging outputs for random forest 1
	 db_prob_1 <= work.casting.tyArray_to_std(prob_1_signal);
	 db_prob_valid_1 <= prob_valid_1_signal_voter;

	 -- Debugging outputs for random forest 2
	 db_prob_2 <= work.casting_2.tyArray_to_std(prob_2_signal);
	 db_prob_valid_2 <= prob_valid_2_signal_voter;

	 
end architecture;