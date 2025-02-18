    propDivisors :: Int -> [Int]
    propDivisors n = concatMap (\d -> if d == n `div` d then [d] else [d, n `div` d]) 
                 [d | d <- [1..(floor . sqrt . fromIntegral) n], n `mod` d == 0]

    -- Function to generate all subsequences of a list
    subsequences :: [a] -> [[a]]
    subsequences [] = [[]]
    subsequences (x:xs) = let rest = subsequences xs in rest ++ map (x:) rest

    -- Function to check if a number is pseudoperfect
    isPseudoperfect :: Int -> Bool
    isPseudoperfect n = any (\subset -> sum subset == n) (subsequences (propDivisors n))

    -- Main analyze function
    analyze :: Int -> Either Int Bool
    analyze n
        | length divisors < 13 = Right (length divisors - 1)
        | length divisors > 13 = Left (length divisors - 1)
        | otherwise = Right (isPseudoperfect n)
        where
            divisors = propDivisors n
