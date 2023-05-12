library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity decision is
	generic(
		wordSize : natural := 24;     -- size of probabilities delivered by the input providers
		decimalSize : natural := 12   -- number of bits for the decimal part of the delivered probabilities
	);
	port(
		a: in std_logic_vector(wordSize-1 downto 0); -- probability of not braking thevehicle
		a_vld : in std_logic;                        -- flag indicating the validity of 'a'
		b: out std_logic 						     -- decision on whether braking ('1') or not ('0')
	);
end decision;

architecture rtl of decision is

	-- Constant indicating a probability of 0.5 with 'wordSize' bits and 'decimalSize' decimal bits.
	constant half : std_logic_vector(decimalSize-1 downto 0) := '1' & (decimalSize-2 downto 0 => '0');

	begin 
        
		-- Brakes are applied (b <= '1') if the probability of not braking is smaller than half
		-- Brakes are not applied (b <= '0') otherwise
		b <= '0' when (a(decimalSize-1 downto 0) > half) else '1'; 

end rtl;