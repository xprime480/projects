
data Foo = Foo Int Int
           deriving (Eq, Show)

quux :: Foo -> Int
quux (Foo 0 _) = 0
quux (Foo a b) = a + 2 * b
