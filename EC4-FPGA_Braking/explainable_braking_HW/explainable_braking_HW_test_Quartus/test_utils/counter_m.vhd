------------------------------------------------------------------------------
-- File   : counter_m.vhd
------------------------------------------------------------------------------
-- Description: Binary counter with generic module 'M', including synchronous
--              and asynchronous clear interfaces (clear_s and clear_as, 
--              respectively), as well as outputs that indicate the middle
--              and the end of the count (mid and final, respectively) and
--              an active-high enable (enable).
-- 
--              Number of counter bits (N) based on M: 
--              N = natural(ceil(log2(real(M))))
--             
------------------------------------------------------------------------------
-- Revisions  :
--     Date        Rev.    Author            Description
--     09/09/2019  1.0     Edson Midorikawa  Creation
--     08/06/2020  1.1     Edson Midorikawa  Revision and improvements 
--     09/09/2020  1.2     Edson Midorikawa  Revision 
--     30/01/2022  2.0     Edson Midorikawa  Component revision.
--     29/01/2023  2.1     Edson Midorikawa  Component revision.
--     28/06/2023  2.2     Antonio V.S.Neto  Revision for EN.
------------------------------------------------------------------------------
--
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;

entity counter_m is
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
end entity counter_m;

architecture behavioral of counter_m is
    signal IQ: integer range 0 to M-1;
begin
  
    process (clock, clear_as, clear_s, enable, IQ)
    begin
        if clear_as = '1' then
            IQ <= 0;   
        elsif clock'event and clock = '1' then
            if clear_s = '1' then
                IQ <= 0;
            elsif enable = '1' then 
                if IQ = M - 1 then
                    IQ <= 0; 
                else
                    IQ <= IQ + 1; 
                end if;
            else
                IQ <= IQ;
            end if;
        end if;
    end process;

    -- 'final' output
    final <= '1' when IQ = M - 1 else
             '0';

    -- 'mid' output
    mid <= '1' when IQ = M/2 - 1 else
           '0';

    -- Q output
    Q <= std_logic_vector(to_unsigned(IQ, Q'length));

end behavioral;
