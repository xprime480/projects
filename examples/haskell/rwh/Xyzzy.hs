
import Data.List

data Xyzzy = Xyzzy Integer Double
             deriving (Ord, Eq, Show)

---------------------------------------------
-- root element
---------------------------------------------

gen0 = [Xyzzy 1 1.0]

---------------------------------------------
-- utilities
---------------------------------------------

getValue :: Xyzzy -> Integer
getValue (Xyzzy v _) = v

getChance :: Xyzzy -> Double
getChance (Xyzzy _ p) = p

applyN :: Integer -> (a->a) -> a -> a 
applyN 0 _ x = x
applyN k f x = applyN (k-1) f (f x)

check :: [Xyzzy] -> Double
check xs = sum (map getChance xs)

ev :: [Xyzzy] -> Double
ev xs = sum (map ev' xs)
    where ev' x = (fromIntegral (getValue x)) * (getChance x)

mode :: [Xyzzy] -> Integer
mode xs = getValue (foldr moreLikely (Xyzzy (-1) (-1.0)) xs)
    where moreLikely x1 x2
              | getChance x1 > getChance x2 = x1
              | otherwise                   = x2

---------------------------------------------
-- memory intensive generator
---------------------------------------------

next :: Xyzzy -> [Xyzzy]
next x = map next1 [1 .. value]
     where value = getValue x
           prob  = getChance x
           next1 v = Xyzzy (value+v) (prob/(fromIntegral value))

generation :: [Xyzzy] -> [Xyzzy]
generation [] = []
generation (x:xs) = (next x) ++ (generation xs)

merge :: [Xyzzy] -> [Xyzzy]
merge ((Xyzzy v1 p1):(Xyzzy v2 p2):xs)
         | v1 == v2 = merge ((Xyzzy v1 (p1+p2)) : xs)
merge (x1:x2:xs) = [x1] ++ (merge (x2:xs))
merge xs = xs

simplify :: [Xyzzy] -> [Xyzzy]
simplify xs = merge (Data.List.sort xs)

genN :: Integer -> [Xyzzy]
genN n = applyN n f gen0
    where f = simplify . generation

---------------------------------------------
-- less memory intensive version -- maybe??
---------------------------------------------

reduceVals :: (Integer -> Integer -> Integer) -> Integer -> [Xyzzy] -> Integer
reduceVals f init xs = foldr f' init xs
    where f' x y = f (getValue x) y

minVal :: [Xyzzy] -> Integer
minVal = reduceVals min 999999 

maxVal :: [Xyzzy] -> Integer
maxVal = reduceVals max 0

old2new :: [Xyzzy] -> Integer -> Xyzzy
old2new xs n = helper xs (Xyzzy n 0.0)
    where helper [] acc = acc
          helper (x:xs) acc
              | n <= xv      = helper xs acc
              | n > (2 * xv) = helper xs acc
              | otherwise    = helper xs (Xyzzy n ((xp + (getChance acc))))
                      where xv = (getValue x)
                            xp = (getChance x)
    
generation' :: [Xyzzy] -> [Xyzzy]
generation' xs = map (old2new xs) newVals
    where newVals = [(1 + (minVal xs)) .. (2 * (maxVal xs))]

genN' :: Integer -> [Xyzzy]
genN' n = applyN n generation' gen0
