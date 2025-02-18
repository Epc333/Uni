data Tree a = Empty | Node a (Tree a ) (Tree a)
newtype Forest a = Forest [Tree a] deriving (Show)


instance Show a => Show (Tree a) where
    show Empty = "()"
    show (Node n fe fd) = "(" ++ show fe ++ "," ++ show n ++ "," ++ show fd ++ ")"

instance Functor Tree where
    fmap f Empty = Empty
    fmap f (Node n fe fd) = Node (f n) (fmap f fe) (fmap f fd) 

--doubleT :: Num a -> Tree a -> Tree a

instance Functor Forest where
    --fmap f (Forest l:ls ) = Forest (f l ++ fmap f (Forest ls))
    fmap f (Forest l) = Forest (fmap (fmap f) l)
