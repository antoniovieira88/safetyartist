------------------------------------------------------------------------------------------------
-- File   : tb_mux_m.vhd
------------------------------------------------------------------------------------------------
-- Description : Testbench of 'mux_m' with 4 inputs of 12 bits each.
--
------------------------------------------------------------------------------------------------
-- Revisions:
--     Date        Rev     Author            Description
--     28/06/2023  1.0     Antonio V.S.Neto  Creation.
------------------------------------------------------------------------------------------------

library ieee;
library work;

use ieee.std_logic_1164.all;
use work.mux_package;

entity mux_m_tb is
end entity;

architecture tb of mux_m_tb is

  -- Component to be tested (Device Under Test -- DUT)
  component mux_m is
    generic (
      n_bits_input : natural;   -- Bits in each input
      n_inputs : natural);  -- Number of inputs
    port(
      v_i   : mux_package.slv_array_t(n_inputs - 1 downto 0)(n_bits_input - 1 downto 0);
      sel_i : in  std_logic_vector(n_inputs - 1 downto 0);
      z_o   : out std_logic_vector(n_bits_input - 1 downto 0)
    );
  end component;

  -- Testbench clock signal and settings
  signal clock : std_logic := '0';
  signal keep_simulating : std_logic := '1'; -- flag to finish the simulation
  constant clockPeriod   : time := 1 ms;    -- frequencia 1KHz

  -- DUT inputs
  signal in0 : std_logic_vector (11 downto 0) := (others => '0');
  signal in1 : std_logic_vector (11 downto 0) := (others => '0');
  signal in2 : std_logic_vector (11 downto 0) := (others => '0');
  signal in3 : std_logic_vector (11 downto 0) := (others => '0');
  signal sel : std_logic_vector (1 downto 0) := (others => '0');

  -- DUT output
  signal mux_out : std_logic_vector (11 downto 0) := (others => '0');  
  
  -- Test case
  signal test_case       : integer := 0;

begin

	-- Clock generator: Generates clock while 'keep_simulating = 1' with 'clockPeriod' duration. 
  	-- When keep_simulating = 0, no clock is generated and the simulation is interrupted.
  	clock <= (not clock) and keep_simulating after clockPeriod/2;

  	-- DUT Instantiation
  	mux_4_12 : component mux_m
    	generic map(
			n_bits_input => 12,
			n_inputs => 4)
    	port map(
      	v_i(0) => in0,
      	v_i(1) => in1,
      	v_i(2) => in2,
	  	v_i(3) => in3,
      	sel_i  => sel,
      	z_o    => mux_out);

	-- Stimuli generation
 	stimulus: process(clock) is
  	begin

		-- Exercises one test case per clock cycle
		if clock'event and clock = '1' then
			
			case test_case is

				when 0 =>
    			-- Case 0: simulation start
    			assert false report "Simulation start" severity note;

				when 1 =>
				-- Case 1: first input setting and selection of input 0
				in0 <= x"AAA";
				in1 <= x"555";
				in2 <= x"FFF";
				in3 <= x"000";
				sel <= "00";

				when 2 =>
				-- Case 2: first input setting and selection of input 1				
				sel <= "01";

				when 3 =>
				-- Case 3: first input setting and selection of input 2				
				sel <= "10";

				when 4 =>
				-- Case 3: first input setting and selection of input 3			
				sel <= "11";

				when 5 =>
				-- Case 5: second input setting and selection of input 0
				in0 <= x"301";
				in1 <= x"7D0";
				in2 <= x"492";
				in3 <= x"E6C";
				sel <= "00";

				when 6 =>
				-- Case 6: second input setting and selection of input 1				
				sel <= "01";

				when 7 =>
				-- Case 7: second input setting and selection of input 2				
				sel <= "10";

				when 8 =>
				-- Case 8: second input setting and selection of input 3			
				sel <= "11";

				when others =>
				---- Simulation finished
				assert false report "Simulation finished" severity note;
				keep_simulating <= '0';
				
			end case;

			-- Increments test case at the end of each clock cycle
			test_case <= test_case + 1;

		end if;

	end process;

end architecture;