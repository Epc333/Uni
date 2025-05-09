myUnfoldr :: (b -> Maybe (a, b)) -> b -> [a] 
myUnfoldr f b = case f b of
    Nothing -> []
    Just (a, b') -> a : myUnfoldr f b'

myReplicate :: a -> Int -> [a]
myReplicate x n = myUnfoldr x' n
    where x' n = if n == 0 then Nothing else Just (x, n-1) 

myIterate :: (a -> a) -> a -> [a]
myIterate f  = myUnfoldr (\x -> Just (x, f x))

myMap :: (a -> b) -> [a] -> [b]
myMap f xs = myUnfoldr g xs
    where
        g []     = Nothing
        g (y:ys) = Just (f y, ys)

data Bst a = Empty | Node a (Bst a) (Bst a)

instance Show a => Show (Bst a) where
    show Empty = "."
    show (Node a fe fd) = "(" ++ show a ++ " " ++ show fe ++ " " ++ show fd ++ ")"


add :: Ord a => a -> (Bst a) -> (Bst a)
add x Empty = Node x Empty Empty
add x (Node y l r)
    | x < y          = Node y (add x l) r
    | x > y          = Node y l (add x r)
    | otherwise = Node y l r

adder :: Ord a => (Bst a, [a]) -> Maybe (Bst a, (Bst a, [a])) 
adder (t, []) = Nothing
adder (t, x:xs) = Just (t', (t', xs))
    where t' = add x t