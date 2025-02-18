
myLength :: [Int] -> Int 

myLength [] = 0
myLength (_ : xs) = 1 + myLength xs

myMaximum :: [Int] -> Int

myMaximum [last] = last
myMaximum (head : tail) = max head (myMaximum tail)

average :: [Int] -> Float

average x = fromIntegral s / fromIntegral m
    where 
        s = sum x
        m = myLength x

buildPalindrome :: [Int] -> [Int] 

buildPalindrome x = reverse x ++ x

remove :: [Int] -> [Int] -> [Int] 

remove [] _ = []
remove (x:xs) y
    | x `elem` y = remove xs y
    | otherwise = x : remove xs y

flatten :: [[Int]] -> [Int]

flatten = concat

oddsNevens :: [Int] -> ([Int],[Int])

oddsNevens [] = ([], [])
oddsNevens (x:xs)
    | odd x = (x : o, e)
    | otherwise = (o, x : e)
    where 
        (o, e) = oddsNevens xs

primeDivisors :: Int -> [Int] 

primeDivisors r = [x | x <- [2..r], mod r x == 0 && isPrime x]



isPrime :: Int -> Bool

isPrime n
    | n < 2 =   False
    | n == 2 =   True
    | even n = False
    | otherwise = isPrimeAux n 3

isPrimeAux :: Int -> Int -> Bool

isPrimeAux n d
    | d * d > n =  True
    | mod n d == 0 = False
    | otherwise = isPrimeAux n (d + 2)