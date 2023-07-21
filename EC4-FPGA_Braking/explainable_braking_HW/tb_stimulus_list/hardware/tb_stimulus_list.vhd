-------------------------------------------------------------------------
-- Arquivo   : tb_stimulus_list.vhd
-------------------------------------------------------------------------
-- Descricao : Testbench for all stimulus_list Python generated VHDLs
--             by E. T. Midorikawa.
-------------------------------------------------------------------------
-- Revision:
--     Date        Rev     Author                       Description
--     14/07/2023  1.0     Henrique Lefundes da Silva   Initial version.
-------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity tb_stimulus_list is
end entity;

architecture tb of tb_stimulus_list is  
  -- DUT input signals and simulation clock
  signal clk_rom_signal      : std_logic := '0';
  signal clk_simulation      : std_logic := '0';
  signal address_signal      : std_logic_vector (6 downto 0) := "0000000";

  signal out_signal_distance     : std_logic_vector (23 downto 0) := "000000000000000000000000";
  signal out_signal_speed        : std_logic_vector (23 downto 0) := "000000000000000000000000";
  signal out_signal_deceleration : std_logic_vector (23 downto 0) := "000000000000000000000000";
  
  signal out_signal_enable_rf_1 : std_logic;
  signal out_signal_enable_rf_2 : std_logic;

  -- Timing settings
  signal keep_simulating : std_logic := '0'; -- Limits the clock generation
  constant clockSimulationPeriod   : time := 2 ms;
  constant clockRomPeriod          : time := 1 ms;

begin
  -- Clock generation: Clock is enabled until 'keep_simulating' goes back to '0'.
  clk_simulation <= (not clk_simulation) and keep_simulating after clockSimulationPeriod/2;
  clk_rom_signal <= (not clk_rom_signal) and keep_simulating after clockRomPeriod/2;

  -- DUT connections
  dut_distance: entity work.stimulus_list_distance
       port map ( 
           address  => address_signal,
           clk      => clk_rom_signal,
           out_rom  => out_signal_distance
       );

  -- DUT connections
  dut_speed: entity work.stimulus_list_speed
       port map ( 
           address  => address_signal,
           clk      => clk_rom_signal,
           out_rom  => out_signal_speed
       );

  -- DUT connections
  dut_deceleration: entity work.stimulus_list_deceleration
       port map ( 
           address  => address_signal,
           clk      => clk_rom_signal,
           out_rom  => out_signal_deceleration
       );

  -- DUT connections
  dut_clk_enable_rf_1: entity work.stimulus_list_clk_enable_rf_1
       port map ( 
           address  => address_signal,
           clk      => clk_rom_signal,
           out_rom  => out_signal_enable_rf_1
       );

  -- DUT connections
  dut_clk_enable_rf_2: entity work.stimulus_list_clk_enable_rf_2
       port map ( 
           address  => address_signal,
           clk      => clk_rom_signal,
           out_rom  => out_signal_enable_rf_2
       );

  -- Stimuli generation
  stimulus: process is
  begin
  
    assert false report "Simulation start" severity note;
    keep_simulating <= '1';  -- inicia geracao do sinal de clock

    
    -- Reads all memory positions (one every clock period)
    assert false report "Reading all memory positions" severity note;
       for addr_it in 0 to 4095 loop
        address_signal <= std_logic_vector(to_unsigned(addr_it, address_signal'length));
        wait for clockSimulationPeriod;
    end loop;

    ---- End of simulation
    assert false report "Simulation end" severity note;
    keep_simulating <= '0';    
    wait;

  end process;

end architecture;