library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_misc.all;
use ieee.numeric_std.all;

library work;
use work.Constants_2.all;

package Types_2 is

  type intArray is array(natural range <>) of integer;
  subtype intArraynLeaves is intArray(0 to nLeaves - 1); -- nLeaves defined in Constants_2
  subtype intArraynNodes is intArray(0 to nNodes - 1); -- nLeaves defined in Constants_2
  type boolArray is array(natural range <>) of boolean;
  subtype boolArraynNodes is boolArray(0 to nNodes - 1); -- nNodes defined in Constants_2
  type txArray is array(natural range <>) of tx; -- tx defined in Constants_2
  subtype txArraynNodes is txArray(0 to nNodes - 1); -- nNodes defined in Constants_2
  type tyArray is array(natural range <>) of ty; -- ty defined in Constants_2
  subtype tyArraynNodes is tyArray(0 to nNodes - 1); -- nNodes defined in Constants_2

  type intArray2DnNodes is array(natural range <>) of intArraynNodes;
  type intArray2DnLeaves is array(natural range <>) of intArraynLeaves;
  type boolArray2DnNodes is array(natural range <>) of boolArraynNodes;
  type txArray2DnNodes is array(natural range <>) of txArraynNodes;
  type tyArray2DnNodes is array(natural range <>) of tyArraynNodes;

  function addReduce(y : in tyArray) return ty;
  function to_tyArray(yArray : intArray) return tyArray;
  function to_tyArray2D(yArray2D : intArray2DnNodes) return tyArray2DnNodes;
  function to_txArray(xArray : intArray) return txArray;
  function to_txArray2D(xArray2D : intArray2DnNodes) return txArray2DnNodes;

end Types_2;

package body Types_2 is
  
  function addReduce(y : in tyArray) return ty is
    -- Sum an array using tree reduce
    -- Recursively build trees of decreasing size
    -- When the size is 2, sum them
    variable ySum : ty := to_ty(0);
    variable lTree, rTree : ty := to_ty(0);
    variable nMid : natural;
  begin
    if y'length = 1 then
      ySum := y(y'low);
    elsif y'length = 2 then
      ySum := y(y'low) + y(y'high);
    else
      -- Find the halfway point
      nMid := (y'length + 1) / 2 + y'high;
      -- Sum each half separately with this function
      rTree := addReduce(y(y'low downto nMid));
      lTree := addReduce(y(nMid-1 downto y'high));
      ySum := ltree + rtree;
    end if;
    return ySum;
  end addReduce;
  
  function to_tyArray(yArray : intArray) return tyArray is
    variable yArrayCast : tyArray(yArray'low to yArray'high);
  begin
    for i in yArray'low to yArray'high loop
        yArrayCast(i) := to_ty(yArray(i));
    end loop;
    return yArrayCast;
  end to_tyArray;
  
    function to_tyArray2D(yArray2D : intArray2DnNodes) return tyArray2DnNodes is
    variable yArray2DCast : tyArray2DnNodes(yArray2D'low to yArray2D'high);
  begin
    for i in yArray2D'low to yArray2D'high loop
        yArray2DCast(i) := to_tyArray(yArray2D(i));
    end loop;
    return yArray2DCast;
  end to_tyArray2D;
  
    function to_txArray(xArray : intArray) return txArray is
    variable xArrayCast : txArray(xArray'low to xArray'high);
  begin
    for i in xArray'low to xArray'high loop
        xArrayCast(i) := to_tx(xArray(i));
    end loop;
    return xArrayCast;
  end to_txArray;
  
    function to_txArray2D(xArray2D : intArray2DnNodes) return txArray2DnNodes is
    variable xArray2DCast : txArray2DnNodes(xArray2D'low to xArray2D'high);
  begin
    for i in xArray2D'low to xArray2D'high loop
        xArray2DCast(i) := to_txArray(xArray2D(i));
    end loop;
    return xArray2DCast;
  end to_txArray2D;
  
end Types_2;
