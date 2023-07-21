--------------------------------------------------------------------
-- File   : hexa7seg.vhd
--------------------------------------------------------------------
-- Description : Hexadecimal to 7-Segment Display Decoder
-- 
-- Input:  hexa - 4-bit hexadecimal number
-- Output: sseg - 7-bit coded version of 'hexa' to 7-segment display
--
-- Hint: All bits of sseg are ordered according to DE0-CV HEX bits.
--       E.g.: sseg(6) --> HEXn[6]
--------------------------------------------------------------------
-- Revisions  :
--     Date        Rev     Author            Description
--     29/12/2020  1.0     Edson Midorikawa  Creation
--     07/01/2023  1.1     Edson Midorikawa  Revision
--     28/06/2023  1.2     Antonio V.S.Neto  Revision for EN.
--     20/07/2023  1.3     Antonio V.S.Neto  Added architecture to
--                                           avoid confusion between
--                                           '5' and '6' and '9' and
--                                           'A' if the 4th segment
--                                           is permanently off.
--------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity hexa7seg is
    port (
        hexa : in  std_logic_vector(3 downto 0);
        sseg : out std_logic_vector(6 downto 0)
    );
end entity hexa7seg;

architecture behavioral of hexa7seg is
begin

  sseg <= "1000000" when hexa="0000" else
          "1111001" when hexa="0001" else
          "0100100" when hexa="0010" else
          "0110000" when hexa="0011" else
          "0011001" when hexa="0100" else
          "0010010" when hexa="0101" else
          "0000010" when hexa="0110" else
          "1111000" when hexa="0111" else
          "0000000" when hexa="1000" else
          "0011000" when hexa="1001" else
          "0001000" when hexa="1010" else
          "0000011" when hexa="1011" else
          "1000110" when hexa="1100" else
          "0100001" when hexa="1101" else
          "0000110" when hexa="1110" else
          "0001110" when hexa="1111" else
          "1111111";

end behavioral;

-- Architecture for display with burnt 4th segment.
-- It avoids confusions between (5, 6) and (9, A) by using invalid characters for 6 and A
architecture behavioral_burntseg4 of hexa7seg is
begin

  sseg <= "1000000" when hexa="0000" else
          "1111001" when hexa="0001" else
          "0100100" when hexa="0010" else
          "0110000" when hexa="0011" else
          "0011001" when hexa="0100" else
          "0010010" when hexa="0101" else
          "0001010" when hexa="0110" else -- exhibits invalid yet unique character to avoid confusion with '5'
          "1111000" when hexa="0111" else
          "0000000" when hexa="1000" else
          "0011000" when hexa="1001" else
          "1011100" when hexa="1010" else -- exhibits invalid yet unique character to avoid confusion with '9'
          "0000011" when hexa="1011" else
          "1000110" when hexa="1100" else
          "0100001" when hexa="1101" else
          "0000110" when hexa="1110" else
          "0001110" when hexa="1111" else
          "1111111";

end behavioral_burntseg4;
