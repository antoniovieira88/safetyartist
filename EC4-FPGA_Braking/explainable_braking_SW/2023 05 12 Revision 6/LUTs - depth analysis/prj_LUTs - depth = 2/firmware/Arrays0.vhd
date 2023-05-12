library ieee;
  use ieee.std_logic_1164.all;
  use ieee.std_logic_misc.all;
  use ieee.numeric_std.all;

  use work.Constants.all;
  use work.Types.all;
  package Arrays0 is

    constant initPredict : ty := to_ty(0);
    constant feature : intArray2DnNodes(0 to nTrees - 1) := ((2, 0, -2, -2, 0, -2, -2),
                (1, 1, -2, -2, 1, -2, -2),
                (2, 0, -2, -2, 0, -2, -2)
                );
    constant threshold_int : intArray2DnNodes(0 to nTrees - 1) := ((134, 42171, -256, -256, 34478, -256, -256),
                (2049, 1252, -256, -256, 3071, -256, -256),
                (134, 42281, -256, -256, 25759, -256, -256)
                );
    constant value_int : intArray2DnNodes(0 to nTrees - 1) := ((38, 38, 19, 42, 39, 20, 42),
                (38, 41, 42, 40, 35, 36, 33),
                (38, 38, 19, 42, 39, 16, 42)
                );
    constant children_left : intArray2DnNodes(0 to nTrees - 1) := ((1, 2, -1, -1, 5, -1, -1),
                (1, 2, -1, -1, 5, -1, -1),
                (1, 2, -1, -1, 5, -1, -1)
                );
    constant children_right : intArray2DnNodes(0 to nTrees - 1) := ((4, 3, -1, -1, 6, -1, -1),
                (4, 3, -1, -1, 6, -1, -1),
                (4, 3, -1, -1, 6, -1, -1)
                );
    constant parent : intArray2DnNodes(0 to nTrees - 1) := ((-1, 0, 1, 1, 0, 4, 4),
                (-1, 0, 1, 1, 0, 4, 4),
                (-1, 0, 1, 1, 0, 4, 4)
                );
    constant depth : intArray2DnNodes(0 to nTrees - 1) := ((0, 1, 2, 2, 1, 2, 2),
                (0, 1, 2, 2, 1, 2, 2),
                (0, 1, 2, 2, 1, 2, 2)
                );
    constant iLeaf : intArray2DnLeaves(0 to nTrees - 1) := ((2, 3, 5, 6),
                (2, 3, 5, 6),
                (2, 3, 5, 6)
                );
    constant value : tyArray2DnNodes(0 to nTrees - 1) := to_tyArray2D(value_int);
      constant threshold : txArray2DnNodes(0 to nTrees - 1) := to_txArray2D(threshold_int);
end Arrays0;