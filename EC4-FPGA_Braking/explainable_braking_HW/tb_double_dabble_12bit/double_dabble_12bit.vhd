------------------------------------------------------------------------------------
-- File   : double_dabble_12bit.vhd
------------------------------------------------------------------------------------
-- Description: 

-- This module takes an 12-bit std_logic_vector, treats it as unsigned and produces
-- a 16-bit std_logic_vector with the corresponding BCD representation by using the
-- double-dabble algorithm. 
-- https://en.wikipedia.org/wiki/Double_dabble
--
-- Input: binary: 12-bit binary number within [0; 4095]
-- Output: bcd: 16-bit BCD-coded version of binary (4 decimal orders)
------------------------------------------------------------------------------------
-- Revisions  :
--     Date        Rev.    Author            Description
--     28/06/2023  1.0     Antonio V.S.Neto  Creation.
------------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity double_dabble_12bit is
    port (
		   binary : in std_logic_vector (11 downto 0);
           bcd    : out std_logic_vector (15 downto 0)
         );
end double_dabble_12bit;

architecture behavioral of double_dabble_12bit is
begin

bcd_proc: process(binary)
	variable scratch : unsigned(27 downto 0) := (others => '0');
begin
	scratch(11 downto 0) := unsigned(binary);
	for i in 0 to 11 loop
		if scratch(27 downto 24) > 4 then
			scratch(27 downto 24) := scratch(27 downto 24) + 3;
		else
			null;
		end if;
		if scratch(23 downto 20) > 4 then
			scratch(23 downto 20) := scratch(23 downto 20) + 3;
		else
			null;
		end if;
		if scratch(19 downto 16) > 4 then
			scratch(19 downto 16) := scratch(19 downto 16) + 3;
		else
			null;
		end if;
		if scratch(15 downto 12) > 4 then
			scratch(15 downto 12) := scratch(15 downto 12) + 3;
		else
			null;
		end if;		
		scratch(27 downto 1) := scratch (26 downto 0);
		scratch(0) := '0';
	end loop;
	bcd <= std_logic_vector(scratch(27 downto 12));
end process;


end behavioral;

