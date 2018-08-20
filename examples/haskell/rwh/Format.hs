toList :: (Show a) => [Char] -> [a] -> [Char]
toList _ []       = ""
toList _ (x:[])   = show x
toList sep (x:xs) = (show x) ++ sep ++ (toList sep xs)

enclose :: [Char] -> [Char] -> [Char] -> [Char]
enclose l r txt = l ++ txt ++ r

parens = enclose "(" ")"

braces = enclose "{" "}"

ccomment = enclose "/*" "*/"

cppcomment = enclose "//" ""
