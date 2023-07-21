library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_misc.all;
use ieee.numeric_std.all;

library work;
use work.Constants_2.all;
use work.Types_2.all;
use work.Arrays_2;

entity BDTTop_2 is
  port(
    clk : in std_logic;  -- clock
    X : in txArray(0 to nFeatures-1) := (others => to_tx(0));           -- input features
    X_vld : in boolean := false; -- input valid
    y : out tyArray(0 to nClasses-1) := (others => to_ty(0));            -- output score
    y_vld : out boolArray(0 to nClasses-1) := (others => false) -- output valid
  );
end BDTTop_2;

architecture rtl of BDTTop_2 is
begin

  BDT0 : entity work.BDT_2
  generic map(
    iFeature => Arrays_2.feature,
    iChildLeft => Arrays_2.children_left,
    iChildRight => Arrays_2.children_right,
    iParent => Arrays_2.parent,
    iLeaf => Arrays_2.iLeaf,
    depth => Arrays_2.depth,
    threshold => Arrays_2.threshold,
    value => Arrays_2.value,
    initPredict => Arrays_2.initPredict
  )
  port map(
    clk => clk,
    X => X,
    X_vld => X_vld,
    y => y(0),
    y_vld => y_vld(0)
  );

  
end rtl;
