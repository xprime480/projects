
data Ternary = Yes
             | No
             | Unsure
               deriving (Eq, Show)

boolish :: Bool -> Ternary
boolish True = Yes
boolish False = No

andish :: Ternary -> Ternary -> Ternary
andish Yes Yes = Yes
andish Unsure _ = Unsure
andish _ Unsure = Unsure
andish _ _ = No

orish :: Ternary -> Ternary -> Ternary
orish No No = No
orish Yes _ = Yes
orish _ Yes = Yes
orish _ _ = Unsure

toBool :: Ternary -> Bool
toBool Yes = True
toBool No = False
toBool _ = error "Uncertain Ternary Clause converting to Bool"
