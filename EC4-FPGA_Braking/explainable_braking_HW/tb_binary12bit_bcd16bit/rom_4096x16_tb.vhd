--------------------------------------------------------------------
-- Arquivo   : rom_4096x16_tb.vhd
--------------------------------------------------------------------
-- Descricao : Testbench for rom_4096x16. Based on 'ram16x4_tb.vhd'
--             by E. T. Midorikawa.
--------------------------------------------------------------------
-- Revision:
--     Date        Rev     Author               Description
--     05/07/2023  1.0     Antonio V. S. Neto   Initial version.
--------------------------------------------------------------------
--
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity rom_4096x16_tb is
end entity;

architecture tb of rom_4096x16_tb is
  
  -- Device Under Test -- DUT
  component rom_4096x16
      port (
          address   : in  std_logic_vector(11 downto 0);
          out_rom   : out std_logic_vector(15 downto 0)
      );
  end component;
  
  -- DUT input signals and simulation clock
  signal clk_rom_signal      : std_logic := '0';
  signal clk_simulation      : std_logic := '0';
  signal address_signal      : std_logic_vector (11 downto 0) := "000000000000";
  signal out_signal          : std_logic_vector (15 downto 0) := "0000000000000000";


  -- Timing settings
  signal keep_simulating : std_logic := '0'; -- Limits the clock generation
  constant clockSimulationPeriod   : time := 2 ms;
  constant clockRomPeriod          : time := 1 ms;

begin
  -- Clock generation: Clock is enabled until 'keep_simulating' goes back to '0'.
  clk_simulation <= (not clk_simulation) and keep_simulating after clockSimulationPeriod/2;
  clk_rom_signal <= (not clk_rom_signal) and keep_simulating after clockRomPeriod/2;

  -- DUT connections
  dut: entity work.rom_4096x16
       port map ( 
           address  => address_signal,
           clk      => clk_rom_signal,
           out_rom  => out_signal
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