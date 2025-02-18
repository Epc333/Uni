main::IO()
main = do
    line <- getLine
    let (n : torres) = words line
    let output = hanoi (read n :: Integer) torres
    mapM_ (\(o, d) -> putStrLn (o ++ " -> " ++ d)) output

hanoi :: Integer -> [String] -> [(String, String)]
hanoi 0 _ = []
hanoi n (origen : desti : auxiliar : _) =
    hanoi (n - 1) [origen, auxiliar, desti] ++
    [(origen, desti)] ++
    hanoi (n - 1) [auxiliar, desti, origen]

