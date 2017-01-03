Create a function that takes a fractional value v and a tolerance t
and returns the integer pair (n, d) where d is the smallest integer
such that abs(n/d) < t.

> closestFracHelper :: Double -> Double -> Integer -> (Integer,Integer)
> closestFracHelper v t d
>    | d < 1           =  (0,0)
>    | v < 0           =  (0,0)
>    | t <= 0.0        =  (0,0)
>    | abs(v - v') < t =  (n,d)
>    | otherwise       =  closestFracHelper v t (1+d)
>      where 
>          d' = fromInteger d
>          n  = round (v*d')
>          n' = fromInteger n
>          v' = n' / d'

> closestFrac :: Double -> Double -> (Integer, Integer)
> closestFrac v t = closestFracHelper v t (round 1)
