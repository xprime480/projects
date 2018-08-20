
minmax :: Ord t => [t] -> [t]
minmax [] = []
minmax (x:[]) = [x,x]
minmax (x:xs) = mmhelper x x xs
    where mmhelper x y [] = [x,y]
          mmhelper x y (z:zs)
             | z < x     = mmhelper z y zs
             | z > y     = mmhelper x z zs
             | otherwise = mmhelper x y zs
