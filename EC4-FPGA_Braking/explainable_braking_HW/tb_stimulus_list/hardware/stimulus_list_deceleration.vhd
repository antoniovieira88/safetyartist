
    -------------------------------------------------------------------
    -- File   : stimulus_list_deceleration
    -------------------------------------------------------------------
    -- Description : Synchronous 128 x 24 ROM.
    -------------------------------------------------------------------
    -- Revision:
    --     Date        Rev     Author                      Description
    --     12/07/2023  1.0     Henrique Lefundes da Silva  Creation.
    -------------------------------------------------------------------
    library ieee;
    use ieee.std_logic_1164.all;
    use ieee.numeric_std.all;

    entity stimulus_list_deceleration is
    port (
            address   : in  std_logic_vector(6 downto 0);
            clk       : in  std_logic;
            out_rom   : out std_logic_vector(23 downto 0)
        );
    end entity stimulus_list_deceleration;
    
    -- Initial data explicitly declared
    architecture stimulus_list_deceleration_arch of stimulus_list_deceleration is
      type memory_struct is array(0 to 127) of std_logic_vector(23 downto 0);
    
    signal memory : memory_struct := ("000000000000111011100001",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000001011001010001",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000000110001111010",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000000110001111010",
 	 	 	 	"000000000000110001111010",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000001011001010001",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000001011001010001",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000001011001010001",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000001011001010001",
 	 	 	 	"000000000001011001010001",
 	 	 	 	"000000000000110001111010",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000001011001010001",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000000110001111010",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000000110001111010",
 	 	 	 	"000000000000110001111010",
 	 	 	 	"000000000001011001010001",
 	 	 	 	"000000000000110001111010",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000001011001010001",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000000110001111010",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000001011001010001",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000000110001111010",
 	 	 	 	"000000000000110001111010",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000000110001111010",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000000110001111010",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000000110001111010",
 	 	 	 	"000000000000110001111010",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000000110001111010",
 	 	 	 	"000000000000110001111010",
 	 	 	 	"000000000001001010011001",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000000111011100001",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000000101001100110",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000",
 	 	 	 	"000000000000000000000000");
  
    begin
    -- Reads ROM position at every rising edge of 'clk'.
    process (clk)
    begin
    if (clk'event and clk = '1') then
        out_rom <= memory(to_integer(unsigned(address)));
      end if;
    end process;

  end architecture stimulus_list_deceleration_arch;  
  