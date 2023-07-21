library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_misc.all;
use ieee.numeric_std.all;

library work;
use work.Constants.all;
use work.Types.all;
use work.casting.all;

entity tb_casting is
   generic (
            wordSize : natural := 24;
	    decimalSize : natural := 12;
            loss_comm : natural := 1000 --absurd value, just for tests
   ); 
end tb_casting;

architecture behavioral of tb_casting is

-- Declaration of signals

-- Part 1 - boolean and std_logic casting
signal in_bool_array : boolArray (29 downto 0);
signal out1_bool : boolean;
signal out0_bool : boolean;
signal out1_std_logic : std_logic;
signal out0_std_logic : std_logic;
signal out_std_logic_vector : std_logic_vector(29 downto 0);

-- Part 2 - tx, ty, txArray, and std_logic_vector casting
signal in_tx : tx;
signal in_ty : ty;
signal in_txArray : txArray (7 downto 0);
signal in_tyArray : tyArray (4 downto 0);
signal out_std_logic_vector_tx : std_logic_vector(wordSize-1 downto 0);
signal out_std_logic_vector_ty : std_logic_vector(wordSize-1 downto 0);
signal out_std_logic_vector_txArray : std_logic_vector((wordSize*8)-1 downto 0);
signal out_std_logic_vector_tyArray : std_logic_vector((wordSize*5)-1 downto 0);

begin

    -- Test 1: bool to std_logic
    out1_std_logic <= work.casting.bool_to_std(true);
    out0_std_logic <= work.casting.bool_to_std(false);

    -- Test 2: std_logic to bool
    out1_bool <= work.casting.std_to_bool('1');
    out0_bool <= work.casting.std_to_bool('0');

    -- Test 3: boolArray to std_logic_vector
    in_bool_array (29 downto 15) <= (others => true);
    in_bool_array (14 downto 0) <= (others => false);
    out_std_logic_vector <= work.casting.boolArray_to_std(in_bool_array);

    -- Test 4: tx to std_logic_vector
    in_tx <= work.Constants.to_tx(2047);
    out_std_logic_vector_tx <= work.casting.tx_to_std(in_tx);

    -- Test 5: ty to std_logic_vector
    in_ty <= work.Constants.to_ty(65535);
    out_std_logic_vector_ty <= work.casting.ty_to_std(in_ty);

    -- Test 6: txArray to std_logic_vector
    in_txArray(0) <= work.Constants.to_tx(9);
    in_txArray(1) <= work.Constants.to_tx(15);
    in_txArray(2) <= work.Constants.to_tx(0);
    in_txArray(3) <= work.Constants.to_tx(63);
    in_txArray(4) <= work.Constants.to_tx(4);
    in_txArray(5) <= work.Constants.to_tx(7);
    in_txArray(6) <= work.Constants.to_tx(2);
    in_txArray(7) <= work.Constants.to_tx(170);
    out_std_logic_vector_txArray <= work.casting.txArray_to_std(in_txArray);

    -- Test 7: tyArray to std_logic_vector
    in_tyArray(4) <= work.Constants.to_ty(15);
    in_tyArray(3) <= work.Constants.to_ty(4);
    in_tyArray(2) <= work.Constants.to_ty(7);
    in_tyArray(1) <= work.Constants.to_ty(2);
    in_tyArray(0) <= work.Constants.to_ty(170);
    out_std_logic_vector_tyArray <= work.casting.tyArray_to_std(in_tyArray);    

end behavioral;