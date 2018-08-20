factorial 0 = 1
factorial n = n * (factorial (n - 1))

removeNth n []     = []
removeNth 0 xs     = tail xs
removeNth n (x:xs) = x : (removeNth (n-1) xs)

perm n xs = permHelper (rem n (factorial (length xs))) [] xs
   where
     permHelper  0 xs ys  = xs ++ ys
     permHelper  _ xs []  = xs
     permHelper  n xs ys  = permHelper fl (xs ++ [ys !! ix]) (removeNth ix ys)
          where
              fl = div n (length ys)
              ix = (rem n (length ys))


factoradic n = fh n 1 []
   where
      fh 0 _ xs = xs
      fh n i xs = fh (div n (factorial i)) (i + 1) ((rem n (factorial i)) : xs )

