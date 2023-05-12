library ieee;
  use ieee.std_logic_1164.all;
  use ieee.std_logic_misc.all;
  use ieee.numeric_std.all;

  use work.Constants.all;
  use work.Types.all;
  package Arrays0 is

    constant initPredict : ty := to_ty(0);
    constant feature : intArray2DnNodes(0 to nTrees - 1) := ((1, 2, 1, -2, -2, 1, -2, -2, 1, 1, -2, -2, 1, -2, -2),
                (1, 0, 0, -2, -2, 2, -2, -2, 2, 0, -2, -2, 0, -2, -2),
                (0, 0, 0, -2, -2, 1, -2, -2, 0, 2, -2, -2, 1, -2, -2)
                );
    constant threshold_int : intArray2DnNodes(0 to nTrees - 1) := ((2194, 134, 1250, -256, -256, 1300, -256, -256, 2930, 2675, -256, -256, 2930, -256, -256),
                (2194, 13755, 3691, -256, -256, 134, -256, -256, 109, 62812, -256, -256, 39442, -256, -256),
                (35943, 12608, 3691, -256, -256, 2011, -256, -256, 60023, 134, -256, -256, 3271, -256, -256)
                );
    constant value_int : intArray2DnNodes(0 to nTrees - 1) := ((38, 41, 40, 42, 39, 41, 42, 40, 35, 36, 37, 35, 33, 0, 33),
                (38, 41, 16, 4, 21, 42, 42, 42, 35, 33, 6, 42, 36, 4, 42),
                (38, 18, 9, 3, 12, 24, 39, 4, 42, 35, 33, 40, 42, 43, 41)
                );
    constant children_left : intArray2DnNodes(0 to nTrees - 1) := ((1, 2, 3, -1, -1, 6, -1, -1, 9, 10, -1, -1, 13, -1, -1),
                (1, 2, 3, -1, -1, 6, -1, -1, 9, 10, -1, -1, 13, -1, -1),
                (1, 2, 3, -1, -1, 6, -1, -1, 9, 10, -1, -1, 13, -1, -1)
                );
    constant children_right : intArray2DnNodes(0 to nTrees - 1) := ((8, 5, 4, -1, -1, 7, -1, -1, 12, 11, -1, -1, 14, -1, -1),
                (8, 5, 4, -1, -1, 7, -1, -1, 12, 11, -1, -1, 14, -1, -1),
                (8, 5, 4, -1, -1, 7, -1, -1, 12, 11, -1, -1, 14, -1, -1)
                );
    constant parent : intArray2DnNodes(0 to nTrees - 1) := ((-1, 0, 1, 2, 2, 1, 5, 5, 0, 8, 9, 9, 8, 12, 12),
                (-1, 0, 1, 2, 2, 1, 5, 5, 0, 8, 9, 9, 8, 12, 12),
                (-1, 0, 1, 2, 2, 1, 5, 5, 0, 8, 9, 9, 8, 12, 12)
                );
    constant depth : intArray2DnNodes(0 to nTrees - 1) := ((0, 1, 2, 3, 3, 2, 3, 3, 1, 2, 3, 3, 2, 3, 3),
                (0, 1, 2, 3, 3, 2, 3, 3, 1, 2, 3, 3, 2, 3, 3),
                (0, 1, 2, 3, 3, 2, 3, 3, 1, 2, 3, 3, 2, 3, 3)
                );
    constant iLeaf : intArray2DnLeaves(0 to nTrees - 1) := ((3, 4, 6, 7, 10, 11, 13, 14),
                (3, 4, 6, 7, 10, 11, 13, 14),
                (3, 4, 6, 7, 10, 11, 13, 14)
                );
    constant value : tyArray2DnNodes(0 to nTrees - 1) := to_tyArray2D(value_int);
      constant threshold : txArray2DnNodes(0 to nTrees - 1) := to_txArray2D(threshold_int);
end Arrays0;