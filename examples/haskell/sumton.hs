sumton_ :: Integer -> Integer -> Integer
sumton_ s 0 = s
sumton_ s n = sumton_ (s+n) (n-1)

sumton__ :: Integer -> Integer
sumton__ n = (n*(n+1)) `div` 2

sumton :: Integer -> Integer
sumton 0 = 0
sumton n = sumton__ n

hs :: Integer -> Integer
hs n 
   | n `mod` 2 == 0 = n `div` 2
   | otherwise      = 3*n + 1

hsseq :: Integer -> [Integer]
hsseq 1 = [1]
hsseq n = n : hsseq (hs n)
