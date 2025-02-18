main::IO()
main = do
    line <- getContents
    mapM_ (print . evalExpr) (lines line)

eval :: [String] -> [Int] -> Either String Int
eval [] [r] = Right r
eval ("+":ws) (x:y:s) = eval ws ((x+y):s)
eval ("-": ws) (x:y:s) = if (x > y) then Left "neg" else eval ws ((y-x):s)
eval ("*": ws) (x:y:s) = eval ws ((x*y):s)
eval ("/": ws) (0:y:s) = Left "div0"
eval ("/": ws) (x:y:s) = if (y `mod` x == 0) then eval ws ((y `div` x):s) else Left "divE"
eval (n : ws) s = eval ws ((read n):s)

evalExpr :: String -> Either String Int
evalExpr s = eval (words s) []
