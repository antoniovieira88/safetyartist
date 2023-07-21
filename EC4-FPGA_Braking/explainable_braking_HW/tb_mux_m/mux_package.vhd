------------------------------------------------------------------------------------------------
-- File   : mux_package.vhd
------------------------------------------------------------------------------------------------
-- Description : Utils for 'mux_m'
-- Reference: https://stackoverflow.com/questions/34590157/generic-mux-and-demux-using-generics
------------------------------------------------------------------------------------------------
-- Revisions:
--     Date        Rev     Author            Description
--     28/06/2023  1.0     Antonio V.S.Neto  Creation.
------------------------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

package mux_package is
  type slv_array_t is array (natural range <>) of std_logic_vector;
end package;

package body mux_package is
end package body;