data Range = Range lo hi
             deriving (Eq, Show)

overlap :: Range -> Range -> Bool
overlap (Range l1 h1) (Range l2 h2) = l1 <= h2 && l2 <= h1

intersection :: Range -> Range -> Maybe Range
intersection r1@(Range l1 h1) r2@(Range l2 h2)
             | overlap r1 r2 = Just Range (max l1 l2) (min h1 h2)
	     | otherwise     = Nothing
