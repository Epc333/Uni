data STree a = Nil | Node Int a (STree a) (STree a) deriving Show

isOk :: STree a -> Bool 
isOk Nil = True;
isOk (Node a x fe fd)  = a == ()