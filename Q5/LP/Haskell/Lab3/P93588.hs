myMap :: (a -> b) -> [a] -> [b] 
myMap op b = [op x | x <- b ]

myFilter :: (a -> Bool) -> [a] -> [a] 
myFilter op y = [x | x <- y, op x]

myZipWith :: (a -> b -> c) -> [a] -> [b] -> [c]
myZipWith op bs cs = [op b c | (b, c) <- zip bs cs]

thingify :: [Int] -> [Int] -> [(Int, Int)] 
thingify xs ys = [(x, y) | x <- xs, y <-ys, x `mod` y == 0]

factors :: Int -> [Int]
factors a = [x | x <- [1..a], mod a x == 0]