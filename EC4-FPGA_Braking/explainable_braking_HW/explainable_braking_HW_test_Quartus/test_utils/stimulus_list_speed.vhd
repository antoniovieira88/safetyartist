
    -------------------------------------------------------------------
    -- File   : stimulus_list_speed
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

    entity stimulus_list_speed is
    port (
            address   : in  std_logic_vector(6 downto 0);
            clk       : in  std_logic;
            out_rom   : out std_logic_vector(23 downto 0)
        );
    end entity stimulus_list_speed;
    
    -- Initial data explicitly declared
    architecture stimulus_list_speed_arch of stimulus_list_speed is
      type memory_struct is array(0 to 127) of std_logic_vector(23 downto 0);
    
    signal memory : memory_struct := ("000000000101000001110001",
 	 	 	 	"000000000110111111010110",
 	 	 	 	"000000000101011000010011",
 	 	 	 	"000000000110011110110101",
 	 	 	 	"000000000001000001000001",
 	 	 	 	"000000000110111010000110",
 	 	 	 	"000000000001000000001000",
 	 	 	 	"000000000100101100100011",
 	 	 	 	"000000000110111111010110",
 	 	 	 	"000000000110111010000110",
 	 	 	 	"000000000010011001110000",
 	 	 	 	"000000000100001100100010",
 	 	 	 	"000000000111111000011010",
 	 	 	 	"000000000010100010000000",
 	 	 	 	"000000000100111010110010",
 	 	 	 	"000000000011011011011101",
 	 	 	 	"000000000010111000111010",
 	 	 	 	"000000000000111110010001",
 	 	 	 	"000000000001011110011101",
 	 	 	 	"000000000011011001101010",
 	 	 	 	"000000000010000001000110",
 	 	 	 	"000000000100111010001011",
 	 	 	 	"000000000010110111101100",
 	 	 	 	"000000000110111010000110",
 	 	 	 	"000000000000111110000001",
 	 	 	 	"000000000100101100100011",
 	 	 	 	"000000000010111110111001",
 	 	 	 	"000000000001000001000001",
 	 	 	 	"000000000100101100100011",
 	 	 	 	"000000000010000111101011",
 	 	 	 	"000000000001000001000001",
 	 	 	 	"000000000100101100110011",
 	 	 	 	"000000000111101001000111",
 	 	 	 	"000000000010111110111001",
 	 	 	 	"000000000111011111010100",
 	 	 	 	"000000000011100010010101",
 	 	 	 	"000000000010100011010010",
 	 	 	 	"000000000011111000111000",
 	 	 	 	"000000000110001111100111",
 	 	 	 	"000000000110110011000001",
 	 	 	 	"000000000110111010000110",
 	 	 	 	"000000000000111110010001",
 	 	 	 	"000000000001100001000011",
 	 	 	 	"000000000010011110001011",
 	 	 	 	"000000000010011001110000",
 	 	 	 	"000000000100011011101000",
 	 	 	 	"000000000101011011001010",
 	 	 	 	"000000000101100011111100",
 	 	 	 	"000000000110000000100110",
 	 	 	 	"000000000110001111100111",
 	 	 	 	"000000000000111110000001",
 	 	 	 	"000000000100000110111100",
 	 	 	 	"000000000111010111111111",
 	 	 	 	"000000000111101100000110",
 	 	 	 	"000000000111101100000110",
 	 	 	 	"000000000100111010001011",
 	 	 	 	"000000000100000110111100",
 	 	 	 	"000000000110110011000001",
 	 	 	 	"000000000011100101101110",
 	 	 	 	"000000000101011000010011",
 	 	 	 	"000000000011111000111000",
 	 	 	 	"000000000001011110011101",
 	 	 	 	"000000000001100001000011",
 	 	 	 	"000000000110001111100111",
 	 	 	 	"000000000101000001110001",
 	 	 	 	"000000000001011100110101",
 	 	 	 	"000000000111010111111111",
 	 	 	 	"000000000100011101011010",
 	 	 	 	"000000000011111110011000",
 	 	 	 	"000000000101011000010011",
 	 	 	 	"000000000010000011000111",
 	 	 	 	"000000000110101100101100",
 	 	 	 	"000000000011111000111000",
 	 	 	 	"000000000101011011001010",
 	 	 	 	"000000000110001100010101",
 	 	 	 	"000000000011110000101000",
 	 	 	 	"000000010100010110010111",
 	 	 	 	"000000011000110001101101",
 	 	 	 	"000000011001001101011100",
 	 	 	 	"000000010101101110101110",
 	 	 	 	"000000011001000011111011",
 	 	 	 	"000000011000010101110101",
 	 	 	 	"000000011011111010100001",
 	 	 	 	"000000010100000000101101",
 	 	 	 	"000000010010010110101011",
 	 	 	 	"000000001110011010001111",
 	 	 	 	"000000001010101100110001",
 	 	 	 	"000000010101011001000000",
 	 	 	 	"000000010111110110011001",
 	 	 	 	"000000011101000011101010",
 	 	 	 	"000000010001011111010111",
 	 	 	 	"000000010001011111010111",
 	 	 	 	"000000010001011111010111",
 	 	 	 	"000000010001011111010111",
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

  end architecture stimulus_list_speed_arch;  
  