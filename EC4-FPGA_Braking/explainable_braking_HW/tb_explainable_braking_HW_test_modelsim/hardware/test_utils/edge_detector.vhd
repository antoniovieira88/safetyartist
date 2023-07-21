--------------------------------------------------------------------------
-- File   : edge_detector.vhd
--------------------------------------------------------------------------
-- Description : Edge detector that generates a one clock-period pulse 
--               after detecting a rising edge on its 'sensed_sig' input.
--               It also has an active-high reset.
--
--             > Adapted from VHDL code in
--               https://surf-vhdl.com/how-to-design-a-good-edge-detector/
--------------------------------------------------------------------------
-- Revision  :
--     Date        Rev.    Author            Description
--     29/01/2020  1.0     Edson Midorikawa  Creation.
--     27/01/2021  1.1     Edson Midorikawa  Revision.
--     29/01/2023  1.2     Edson Midorikawa  Revision.
--     20/07/2023  1.3     Edson Midorikawa  Revision for EN.
--------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity edge_detector is
    port (
        clock          : in  std_logic;
        reset          : in  std_logic;
        sensed_signal  : in  std_logic;
        out_pulse      : out std_logic
    );
end entity edge_detector;

architecture rtl of edge_detector is

    signal reg0   : std_logic;
    signal reg1   : std_logic;

begin

    detector : process (clock, reset)
    begin
        if (reset='1') then
            reg0 <= '0';
            reg1 <= '0';
        elsif (clock'event and clock = '1') then
            reg0 <= sensed_signal;
            reg1 <= reg0;
        end if;
    end process;
    
    out_pulse <= not reg1 and reg0;

end architecture rtl;