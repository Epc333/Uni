absValue :: Int -> Int 

absValue n
    | n >= 0 = n
    | otherwise = -n

power :: Int -> Int -> Int

power _ 0 = 1
power n e
    | even e = y * y
    | otherwise = y * y * n
    where
        y = power n e_meitat
        e_meitat = div e 2


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

slowFib :: Int -> Int

slowFib n
    | n == 0 = 0
    | n == 1 = 1
    |otherwise = slowFib (n - 1) + slowFib (n-2);

quickFib :: Int -> Int

quickFib = quickFib2 0 1

quickFib2 :: Int -> Int -> Int -> Int

quickFib2 x y repe
    | repe /= 0 = quickFib2 y (x+y) (repe - 1)
    | otherwise = x