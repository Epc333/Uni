insertionSort :: [Int] -> [Int]
insertionSort [] = []
insertionSort (x:xs) = insert x (insertionSort xs)
  where
    insert y [] = [y]
    insert y (z:zs)
      | y <= z    = y : z : zs
      | otherwise = z : insert y zs


minProd :: [Int] -> [Int] -> Int
minProd x y = sum $ zipWith (*) (insertionSort x) (reverse (insertionSort y))
