import Data.List

lcAlpha = ['a'..'z']
ucAlpha = ['A'..'Z']
digits  = ['0'..'9']
ws      = [' ', '\t', '\n', '\r']
ident   = lcAlpha ++ ucAlpha ++ digits
signs   = "+-"
ops     = ["++", "--", "+", "-", "*", "/"]

data Token = End
           | StrVal String
           | NumVal Double
           | Ident  String
           | Oper   String
           | Error  String String
             deriving (Eq,Show)

dropWs = snd . (span (`elem` ws))
scanDigits = span (`elem` digits)

scanEnd :: String -> Maybe (Token, String)
scanEnd str = if "" == (dropWs str) then Just (End, "") else Nothing

scanDelimitedContents :: String -> String -> String -> Maybe (String, String)
scanDelimitedContents _ acc ""         = Nothing
scanDelimitedContents e acc str@(c:cs) = case m of
                                              True -> Just (acc, (drop (length e) str)
                                              False -> scanDelimitedContents e (acc ++ [c]) cs
    where m = e `isPrefixOf` str					      

scanDelimited :: String -> String -> String -> Maybe (Token, String)
scanDelimited s e str = case s `isPrefixOf` str of
                             True  -> scanDelimitedContents e "" (drop (length s) str
                             False -> Nothing

scanQuoted = scanDelimited "\"" "\""

scanFrac ('.':rest) whole = case ds of
                                 ""        ->  Just (NumVal whole, rest)
                                 otherwise ->  Just (NumVal (whole + (read ("0." ++ ds) :: Double)), rest2)
    where (ds, rest2) = scanDigits rest
scanFrac rest whole = Just (NumVal whole, rest)

scanNumVal ""  = Nothing
scanNumVal str = case ds of
                      ""        -> Nothing
                      otherwise -> scanFrac rest (read ds :: Double)
    where (ds,rest) = scanDigits str

scanIdent str = case ds of
                     ""         -> Nothing
                     otherwise  -> Just ((Ident ds), rest)
    where (ds,rest) = span (`elem` ident) str

scanOper str = case ms of
                    []       -> Nothing
                    (op:ops) -> Just ((Oper op), (drop (length op) str))
    where ms = filter (`isPrefixOf` str) ops

defaultScanner str = Just ((Error "Could not scan" str), "")

lexers = [scanEnd, scanQuoted, scanOper, scanNumVal, scanIdent, defaultScanner]

matchFirstIn :: [String -> Maybe (Token, String)] -> String -> (Token, String)
matchFirstIn [] input     = ((Error "No scanners remain for" input), "")
matchFirstIn (f:fs) input = case m of
                                 Nothing -> matchFirstIn fs input
                                 Just x  -> x
    where m = f input

tryAllScanners :: String -> (Token, String)
tryAllScanners = matchFirstIn lexers

scan :: String -> [Token]	
scan ""      = [End]
scan input   = case first of
                    End       -> [first]
                    Error _ _ -> [first]
                    otherwise -> [first] ++ (scan rest)
    where (first, rest) = (tryAllScanners . dropWs) input
