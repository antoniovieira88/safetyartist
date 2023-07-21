------------------------------------------------------------------------------------------
-- Adapted from "DoubleDabberTest.vhd" from https://github.com/joulsen/16BitDoubleDabbler 
------------------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
 
entity double_dabble_tb is
end double_dabble_tb;
 
architecture tb of double_dabble_tb is 
 
    -- Component in test (DUT)
 
    component double_dabble_12bit is
		port(
         		binary : in std_logic_vector (11 downto 0);
            	bcd    : out std_logic_vector (15 downto 0)
           	);
  	end component ;
    
   --Inputs
   signal binary : std_logic_vector(11 downto 0) := x"0F3";

 	--Outputs
   signal bcd : std_logic_vector(15 downto 0);
 
begin
 
   -- Instantiate the DUT
   dut: double_dabble_12bit
   port map (
        	binary => binary,
        	bcd => bcd
       		);

end tb;
