library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity voting is
	generic(
		wordSize : natural := 24;     -- size of probabilities delivered by the input providers
		decimalSize : natural := 12;  -- number of bits for the decimal part of the delivered probabilities
		loss_comm : natural := 30     -- number of clock cycles for a loss of comunication with any input provider.
	);
	port(
		prob_1, prob_2 : in std_logic_vector(wordSize-1 downto 0); -- vectors related to the non-braking probabilities delivered by the input providers
		prob_valid_1, prob_valid_2 : in std_logic;   -- flags related to the validity of the non-braking probabilities delivered by the input providers
		clk_voting : in std_logic;                   -- clock input
		prob_mean : out std_logic_vector(wordSize-1 downto 0); -- resulting non-braking probability after combining both input providers and considering loss of sync
		prediction: out std_logic                    -- decision on whether braking ('1') or not ('0')
	);
end voting;

architecture rtl of voting is

	-- Declaration of components 'mean and 'decision', which are used on the voting processing.
	-- Please refer to their entities' spcification for details on their interfaces
	component mean is
	generic(
		wordSize : natural;
    	loss_comm : natural
	);
	port(
		a, b : in std_logic_vector(wordSize-1 downto 0);
		a_vld, b_vld, clk_mean : in std_logic;
		c: out std_logic_vector(wordSize-1 downto 0);
		c_vld : out std_logic
	);
	end component;
	
	component decision is
		generic(
			wordSize : natural; 
			decimalSize : natural
		);
		port(
			a: in std_logic_vector(wordSize-1 downto 0);
			a_vld : in std_logic;
			b: out std_logic
		);
	end component;
	
	-- Additional registers for intermediate signals exchanged between the instances of 'mean' and 'decision'

	-- Resulting non-braking probability after combining both input providers and considering loss of sync
	signal prob_mean_signal : std_logic_vector(wordSize-1 downto 0);

	-- Resulting validity of the combined non-braking probability from both input providers and considering loss of sync
	signal prob_valid_mean : std_logic;
	
	begin
	
	-- Instantiation of 'mean'
	mean0: mean generic map(wordSize => wordSize, loss_comm => loss_comm)
	port map(a => prob_1, b => prob_2, a_vld => prob_valid_1, b_vld => prob_valid_2,
			   clk_mean => clk_voting, c => prob_mean_signal, c_vld => prob_valid_mean);
	
	-- Instantiation of 'decision'
	decision0: decision generic map(wordSize => wordSize, decimalSize => decimalSize)
	port map(a => prob_mean_signal, a_vld => prob_valid_mean, b => prediction);

	-- Defition of the output 'prob_mean' as the output of the register 'prob_mean_signal'
	prob_mean <= prob_mean_signal;
	
end rtl;