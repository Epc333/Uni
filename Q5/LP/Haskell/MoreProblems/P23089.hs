myUnfoldr :: (b -> Maybe (a, b)) -> b -> [a]
myUnfoldr f b = case f b of
    Nothing     -> []
    Just (a, b') -> a : myUnfoldr f b'

myReplicate :: a -> Int -> [a]
myReplicate x n = myUnfoldr (\m -> if m <= 0 then Nothing else Just (x, m - 1)) n

myIterate :: (a -> a) -> a -> [a]
myIterate f n = myUnfoldr (\b -> Just (b, f b)) n

myMap :: (a -> b) -> [a] -> [b]
myMap f xs = myUnfoldr (\ys -> case ys of
                                    []  -> Nothing
                                    (z:zs) -> Just (f z, zs)) xs


instance Show a => Show (Bst a) where
    show Empty = "."
    show (Node x l r) = "(" ++ show l ++ " <- " ++ show x ++ " -> " ++ show r ++ ")"

data Bst a = Empty | Node a (Bst a) (Bst a)

add :: Ord a => a -> (Bst a) -> (Bst a)

add x Empty = Node x Empty Empty
add x (Node y l r)
    | x < y          = Node y (add x l) r
    | x > y          = Node y l (add x r)
    | otherwise = Node y l r

