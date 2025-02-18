flatten :: [[Int]] -> [Int] 

flatten = foldl (++) []

myLength :: String -> Int

myLength [] = 0
myLength x = last $ zipWith cola x (iterate (+1) 1)
    where cola a b = b

myReverse :: [Int] -> [Int] 

myReverse = foldr reverse []
    where reverse a b = (++) b [a]

countIn :: [[Int]] -> Int -> [Int] 

countIn llista x = map(length . filter (== x)) llista

firstWord :: String -> String

firstWord x = takeWhile (/= ' ') $ dropWhile (== ' ') x
--firstWord = head . words 

