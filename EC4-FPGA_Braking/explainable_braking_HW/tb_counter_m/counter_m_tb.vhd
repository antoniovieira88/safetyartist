------------------------------------------------------------------------------
-- File   : counter_m.vhd
------------------------------------------------------------------------------
-- Description: Testbench for 'counter_m' with M = 1000 and 100Hz clock.
------------------------------------------------------------------------------
-- Revision:
--     Date        Rev     Author            Description
--     31/01/2020  1.0     Edson Midorikawa  Creation
--     31/08/2022  2.0     Edson Midorikawa  Code review.
--     27/01/2023  2.1     Edson Midorikawa  Code review.
--     28/06/2023  3.0     Antonio V.S.Neto  Code review.
--------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;
use std.textio.all;

-- entidade do testbench
entity counter_m_tb is
end entity;

architecture tb of counter_m_tb is

  -- Componente a ser testado (Device Under Test -- DUT)
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
  
  ---- DUT Input signals
  signal clock_in    : std_logic := '0';
  signal clear_as_in : std_logic := '0';
  signal clear_s_in  : std_logic := '0';
  signal enable_in   : std_logic := '0';

  ---- DUT output signals
  signal q_out      : std_logic_vector(9 downto 0) := (others => '0'); -- log2(1000)=9,97
  signal final_out  : std_logic := '0';
  signal mid_out    : std_logic := '0';

  -- Configurações do clock
  signal keep_simulating : std_logic := '0'; -- flag to finish the  o tempo de geração do clock
  constant clockPeriod   : time := 10 ms;    -- frequencia 1KHz
  
  -- Test case
  signal test_case       : integer := 0;

begin
  -- Clock generator: Generates clock while 'keep_simulating = 1' with 'clockPeriod' duration. 
  -- When keep_simulating = 0, no clock is generated and the simulation is interrupted.
  clock_in <= (not clock_in) and keep_simulating after clockPeriod/2;
  
  ---- DUT instantiation
  dut: counter_m
       generic map
       (
            M => 1000
       )
       port map
       (
            clock    =>  clock_in,
            clear_as =>  clear_as_in,
            clear_s  =>  clear_s_in,
            enable   =>  enable_in,
            Q        =>  q_out,
            final    =>  final_out,
            mid      =>  mid_out
       );
 
  ---- Stimuli generation
  stimulus: process is
  begin

    -- Simulation start
    assert false report "Simulation start" severity note;
    keep_simulating <= '1';  -- inicia geracao do sinal de clock

    -- Case 1: Generates asynchronous clear (one clock cycle)
    test_case <= 1;
    clear_as_in <= '1';
    wait for clockPeriod;
    clear_as_in <= '0';

    -- Case 2: Waits for 10 clock periods without enabling the counter.
    test_case <= 2;
    wait for 10*clockPeriod;
    wait until falling_edge(clock_in);

    -- Case 3: Enables counts for 20 clock periods.
    test_case <= 3;
    enable_in <= '1';
    wait for 20*clockPeriod;
    enable_in <= '0';
    wait until falling_edge(clock_in);

    -- Case 4: New asynchronous clear.     
    test_case <= 4;
    clear_as_in <= '1';
    wait for clockPeriod;
    clear_as_in <= '0';
    wait until falling_edge(clock_in);

    -- Case 5: Enables the counting of 100 clock periods with 10 idle clock periods
    -- between the first 40 and the last 60.
    test_case <= 5;
    enable_in <= '1';
    wait for 40*clockPeriod;
    enable_in <= '0';
    wait for 10*clockPeriod;
    enable_in <= '1';
    wait for 60*clockPeriod;
    enable_in <= '0';
    wait until falling_edge(clock_in);

    -- Case 6: Synchronous clear    
    test_case <= 6;
    clear_s_in <= '1';
    wait for 3*clockPeriod;
    clear_s_in <= '0';
    wait until falling_edge(clock_in);

    -- Case 7: Enable full count for 1007 clock periods and then disables the count for 5 cycles
    test_case <= 7;
    enable_in <= '1';
    wait for 1007*clockPeriod;
    wait until falling_edge(clock_in);
    enable_in <= '0';
    wait for 5*clockPeriod;  
 
    ---- Simulation finished
    assert false report "Simulation finished" severity note;
    keep_simulating <= '0';
    
    wait; -- End of simulation: process hold
  end process;


end architecture;
