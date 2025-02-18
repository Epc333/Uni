ones :: [Integer]
ones = iterate id 1

nats :: [Integer]
--nats = iterate (+1) 0
nats = scanl (+) 0 (repeat 1)

ints :: [Integer]
ints = iterate valor 0
    where 
        valor x 
            | x > 0 = (-1) * x
            | otherwise = (-1) * x + 1

triangulars :: [Integer]
triangulars = map fst (iterate (\(x, n) -> (x + n, n + 1)) (0, 1))

factorials :: [Integer]
factorials = map fst (iterate (\(x, y) -> (x * y, y+1)) (1, 1))

fibs :: [Integer]
fibs = map fst (iterate (\(f1, f2) -> (f1 + f2, f1)) (0, 1))

primes :: [Integer]
primes = garbell (iterate (+1) 2)
    where
        garbell (p : xs) = p : garbell [x | x <- xs, mod x p /= 0]

hammings :: [Integer]
hammings = 1 : merge (map (*2) hammings) (merge (map (*3) hammings) (map (*5) hammings))
    where
        merge (x : xs) (y : ys)
            | x < y = x : merge xs (y:ys)
            | x > y = y : merge (x:xs) ys
            | otherwise  = x : merge xs ys

lookNsay :: [String]
lookNsay = iterate seguent "1"
    where
        seguent [] = []
        seguent (x:xs) = let (igual, altres) = span (== x) xs
                         in show (1 + length igual) ++ [x] ++ seguent altres

tartaglia :: [[Integer]]
tartaglia = iterate seguent [1]
    where
        seguent fila = zipWith (+) ([0] ++ fila) (fila ++ [0])