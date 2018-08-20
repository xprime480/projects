
mj :: (Show a, Show b) => a -> b -> [Char]
mj x [] = (show x)
mj x y  = (show x) ++ ", " ++ (show y)

