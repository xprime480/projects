
collatz :: Integer -> [Integer]
collatz 1 = [1]
collatz n
    | odd n     = n : (collatz (3*n+1))
    | otherwise = n : (collatz (n `div` 2))

firstToValue :: Ord a => (a,b) -> [(a,b)] -> [(a,b)]
firstToValue p []               =  [p]
firstToValue n@(a,_) (p@(pa,_):ps)
    | a < pa    = n : p : ps
    | a > pa    = p : (firstToValue n ps)
    | otherwise = p : ps

newMaxima :: Ord a => (a,b) -> [(a,b)] -> [(a,b)]
newMaxima p [] = [p]
newMaxima n@(a,_) ps
    | (fst $ last ps) < a  = ps ++ [n]
    | otherwise            = ps

minargs :: Ord b => (a -> b) -> [a] -> [(b, a)]
minargs f xs = minargsHelper f xs []
    where minargsHelper f []     acc = acc
          minargsHelper f (x:xs) acc = minargsHelper f xs (firstToValue ((f x),x) acc)
