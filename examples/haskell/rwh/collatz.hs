
collatz 1 = []
collatz n = n
    | odd n     = n : collatz 3*n+1
    | otherwise = n : collatz n/2
