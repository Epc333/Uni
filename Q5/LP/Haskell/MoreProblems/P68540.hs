diffSqrs :: Integer -> Integer
diffSqrs n = a * a - s
    where
        s = sum (map(\x -> x * x) [1 .. n])
        a = (sum [1..n])

pythagoreanTriplets :: Int -> [(Int, Int, Int)]
pythagoreanTriplets n = [(x, y, z) | x <- [1..n],
                                     y <- [x..n],
                                     let z = floor $ sqrt $ fromIntegral $ x*x + y*y,
                                     x + y + z == n,
                                     x*x + y*y == z*z]

tartaglia :: [[Integer]]
tartaglia = iterate seguent [1]
    where
        seguent fila = zipWith (+) ([0] ++ fila) (fila ++ [0])

sumDigits :: Integer -> Integer
--sumDigits n = sum . map (\x -> fromIntegral (fromEnum x - fromEnum '0')) $ show n;
sumDigits n = sum [read [c] | c <- show n]

digitalRoot :: Integer -> Integer
digitalRoot = until (<10) sumDigits
