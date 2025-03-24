
insert :: [Int] -> Int -> [Int]

insert [] x = [x]
insert (x: xs) n
    | x < n = x : insert xs n
    | otherwise = n : x : xs

isort :: [Int] -> [Int]

isort [] = []
isort (x : xs) = insert cua x
    where
        cua = isort xs

remove :: [Int] -> Int -> [Int] 
remove [] _ = []
remove (x:xs) n
    | x == n = xr 
    | otherwise = x : xr 
    where 
        xr = remove xs n

ssort::[Int] -> [Int]

ssort [] = []   --Si esta buida
ssort (x : xs)
    | null xs = [x]     -- Si nomès hi ha un element
    | min < x =  min : ssort cua    -- Ja hem trobat l'element minim
    | otherwise = x : ssort xs      -- Anar recorrent llista
        where
            cua = remove xs min ++ [x]
            min = minimum xs

merge :: [Int] -> [Int] -> [Int] 

merge [] l2 = l2
merge l1[] = l1
merge (x : xs) (y: ys)
    |x > y = y : merge (x:xs) ys
    |otherwise = x : merge xs (y : ys)

msort :: [Int] -> [Int] 

msort [] = []
msort [x] = [x]
msort xs = merge (msort left) (msort right)
    where
        n = length xs `div` 2
        left = take n xs
        right = drop n xs

qsort :: [Int] -> [Int]

qsort [] = []
qsort (x : xs) = qsort menor ++ [x] ++qsort major
    where
        menor = [a | a <- xs, a <= x]
        major = [a | a <- xs, a > x]

genQsort :: Ord a => [a] -> [a] 
genQsort [] = []
genQsort (x : xs) = genQsort menor ++ [x] ++genQsort major
    where
        menor = [a | a <- xs, a <= x]
        major = [a | a <- xs, a > x]