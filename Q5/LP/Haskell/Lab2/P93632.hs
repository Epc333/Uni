eql :: [Int] -> [Int] -> Bool 

eql x y = x == y

prod :: [Int] -> Int 

prod x = foldr (*) 1 x

prodOfEvens :: [Int] -> Int 

prodOfEvens x = prod $ filter even x

powersOf2 :: [Int]

powersOf2  = iterate (*2) 1

scalarProduct :: [Float] -> [Float] -> Float 

scalarProduct x y = sum $ zipWith (*) x y