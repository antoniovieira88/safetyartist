------------------------------------------------------------------------------------------------
-- File   : mux_m.vhd
------------------------------------------------------------------------------------------------
-- Description : Multiplexer of 'm' inputs.
-- Reference: https://stackoverflow.com/questions/34590157/generic-mux-and-demux-using-generics
--
-- Generic Parameters:
-- n_bits_input: number of bits per multiplexer input
-- n_inputs: number of multiplexer inputs (each with n_bits_input size)
-- 
-- Inputs: v_i - array of 'n_inputs' std_logic_vector elements, each sized 'n_bits_input'
--         sel_i - output selector
-- Output: z_o - one of the v_i inputs corresponding to the position selected by sel_i
--
------------------------------------------------------------------------------------------------
-- Revisions:
--     Date        Rev     Author            Description
--     28/06/2023  1.0     Antonio V.S.Neto  Creation.
------------------------------------------------------------------------------------------------

library ieee;
library work;

use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;

use work.mux_package;

entity mux_m is
  generic(
    n_bits_input : natural := 12;   -- Bits in each input
    n_inputs     : natural := 4);  -- Number of inputs
  port(
    v_i   : in  mux_package.slv_array_t(n_inputs - 1 downto 0)(n_bits_input - 1 downto 0);
    sel_i : in  std_logic_vector(natural(ceil(log2(real(n_inputs))))-1 downto 0);
    z_o   : out std_logic_vector(n_bits_input - 1 downto 0)
    );
end entity;

architecture syn of mux_m is
begin
  z_o <= v_i(to_integer(unsigned(sel_i)));
end architecture;