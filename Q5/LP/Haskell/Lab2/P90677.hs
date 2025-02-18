
myFoldl :: (a -> b -> a) -> a -> [b] -> a

myFoldl _ a [] = a
myFoldl op a (b : bs) = myFoldl op (op a b) bs

myFoldr :: (a -> b -> b) -> b -> [a] -> b

myFoldr _ a [] = a
myFoldr op a (b : bs) = op b (myFoldr op a bs)

myIterate :: (a -> a) -> a -> [a]

myIterate f x = x : myIterate f (f x)

myUntil :: (a -> Bool) -> (a -> a) -> a -> a

myUntil cond f valor 
    | cond valor    = valor
    | otherwise = myUntil cond f (f valor)

myMap :: (a -> b) -> [a] -> [b]

myMap f = myFoldr (\x acumulador -> f x : acumulador) []

myFilter :: (a -> Bool) -> [a] -> [a]

myFilter f = myFoldr (\x acumulador -> if f x then x : acumulador else acumulador) []

myAll :: (a -> Bool) -> [a] -> Bool

myAll f = myFoldr (\x acumulador -> f x && acumulador) True

myAny :: (a -> Bool) -> [a] -> Bool

myAny f = myFoldr (\x acumulador -> f x || acumulador) False

myZip :: [a] -> [b] -> [(a, b)]

myZip [] _ = []
myZip _ [] = []
myZip (x : xs) (y : ys) = (x, y) : myZip xs ys

myZipWith :: (a -> b -> c) -> [a] -> [b] -> [c]

myZipWith f xs ys = myFoldr (\(x, y) a -> (f x y):a) [] (myZip xs ys)