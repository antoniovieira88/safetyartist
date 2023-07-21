library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_misc.all;
use ieee.numeric_std.all;

library work;
use work.Constants.all;
use work.Types.all;

package casting is
    -- bool casting
    function std_to_bool(x : std_logic) return boolean;
    function bool_to_std(bool : boolean) return std_logic;
    function boolArray_to_std(arrBool : boolArray) return std_logic_vector;
    -- tx, ty, txArray, and tyArray casting
    function tx_to_std(x : tx) return std_logic_vector;
    function ty_to_std(y : ty) return std_logic_vector;
    function txArray_to_std(arr : txArray) return std_logic_vector;
    function tyArray_to_std(arr : tyArray) return std_logic_vector;
end package;

package body casting is
    -------------------------------------------------------------------------------
    -- This function casts a std_logic value (1 or 0) into a boolean (true or false)
    function std_to_bool(x : std_logic) return boolean is
        
    begin
        if x = '1' then
            return true;
        else
            return false;
        end if;  
    end std_to_bool;

    -------------------------------------------------------------------------------

    function bool_to_std(bool : boolean) return std_logic is
    -- This function casts a boolean (true or false) into a std_logic value (1 or 0)
    begin
        if bool then
            return '1';
        else
            return '0';
        end if;  
    end bool_to_std;

    -----------------------------------------------------------------------------
    function boolArray_to_std(arrBool : boolArray) return std_logic_vector is
    -- Cast a array of booleans into a std_Logic_vector using the bool_to_std cast function
    variable bool_std_vector : std_logic_vector(arrBool'high downto arrBool'low);

    begin
        for i in arrBool'range loop
            bool_std_vector(i) := bool_to_std(arrBool(i)); 
        end loop;

        return bool_std_vector;    
    end boolArray_to_std;

    ------------------------------------------------------------------------------
    function tx_to_std(x : tx) return std_logic_vector is
    -- Cast a tx type (see Constants.vhd for more details) into a std_logic_vector
    begin
        return std_logic_vector(x);
    end tx_to_std;

	------------------------------------------------------------------------------
    function ty_to_std(y : ty) return std_logic_vector is
    -- Cast a ty type (see Constants.vhd for more details) into a std_logic_vector
    begin
        return std_logic_vector(y);
    end ty_to_std;

    ------------------------------------------------------------------------------
    function txArray_to_std(arr : txArray) return std_logic_vector is
    -- Cast a txArray (arrays of tx) into a std_logic_vector, note that it flattens the array
    variable castVector : std_logic_vector(tx'length*arr'length-1 downto 0);

    begin
        for i in arr'range loop
            castVector(tx'length*(i+1)-1 downto tx'length*i) := tx_to_std(arr(i));
        end loop;
        return castVector;
    end txArray_to_std;

    ------------------------------------------------------------------------------
    function tyArray_to_std(arr : tyArray) return std_logic_vector is
    -- Cast a tyArray (arrays of ty) into a std_logic_vector, note that it flattens the array
    variable castVector : std_logic_vector(ty'length*arr'length-1 downto 0);

    begin
        for i in arr'range loop
            castVector(ty'length*(i+1)-1 downto ty'length*i) := ty_to_std(arr(i));
        end loop;
        return castVector;
    end tyArray_to_std;

end package body;