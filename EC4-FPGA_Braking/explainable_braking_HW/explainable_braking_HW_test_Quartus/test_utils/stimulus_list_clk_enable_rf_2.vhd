
    -------------------------------------------------------------------------
    -- File   : stimulus_list_clk_enable_rf_2
    -------------------------------------------------------------------------
    -- Description : Synchronous 128 x 1 ROM.
    -------------------------------------------------------------------------
    -- Revision:
    --     Date        Rev     Author             Description
    --     12/07/2023  1.0     Henrique L. Silva  Creation.
	--     20/07/2023  2.0     Antonio V. S. Neto Update on 'memory_struct'
	--                                            to std_logic_vector to
	--                                            force Quartus to infer ROM.
    -------------------------------------------------------------------------
    library ieee;
    use ieee.std_logic_1164.all;
    use ieee.numeric_std.all;

    entity stimulus_list_clk_enable_rf_2 is
    port (
            address   : in  std_logic_vector(6 downto 0);
            clk       : in  std_logic;
            out_rom   : out std_logic
        );
    end entity stimulus_list_clk_enable_rf_2;
    
    -- Initial data explicitly declared
    architecture stimulus_list_clk_enable_rf_2_arch of stimulus_list_clk_enable_rf_2 is
      type memory_struct is array(0 to 127) of std_logic_vector (0 downto 0);
    
    signal memory : memory_struct := ("0",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"1",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"1",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"1",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"1",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"1",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0",
 	 	 	 	"0");
  
    begin
    -- Reads ROM position at every rising edge of "clk".
    process (clk)
    begin
    if (clk'event and clk = '1') then
        out_rom <= memory(to_integer(unsigned(address)))(0);
      end if;
    end process;

  end architecture stimulus_list_clk_enable_rf_2_arch;  
  