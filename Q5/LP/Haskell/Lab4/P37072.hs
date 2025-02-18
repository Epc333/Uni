data Tree a = Node a (Tree a) (Tree a) | Empty deriving (Show)

t7 = Node 7 Empty Empty
t6 = Node 6 Empty Empty
t5 = Node 5 Empty Empty
t4 = Node 4 Empty Empty
t3 = Node 3 t6 t7
t2 = Node 2 t4 t5
t1 = Node 1 t2 t3
t1' = Node 1 t3 t2

size :: Tree a -> Int 
size Empty = 0
size (Node a ne nd) = 1 + size ne + size nd

height :: Tree a -> Int
height Empty = 0
height (Node a fe fd) = 1 + max (height fe) (height fd)

equal :: Eq a => Tree a -> Tree a -> Bool
equal Empty Empty = True
equal _ Empty = False
equal Empty _ = False
equal (Node a fea fda) (Node b feb fdb) = a == b && equal fea feb && equal fda fdb

isomorphic :: Eq a => Tree a -> Tree a -> Bool
isomorphic Empty Empty = True
isomorphic _ Empty = False
isomorphic Empty _ = False
isomorphic (Node a fea fda) (Node b feb fdb) = a == b && equal fea fdb && equal fda feb


preOrder :: Tree a -> [a]
preOrder Empty = []
preOrder (Node a fe fd) = [a] ++ preOrder fe ++ preOrder fd

postOrder :: Tree a -> [a]
postOrder Empty = []
postOrder (Node a fe fd) = postOrder fe ++ postOrder fd ++ [a]

inOrder :: Tree a -> [a]
inOrder Empty = []
inOrder (Node a fe fd) = inOrder fe ++ [a] ++ inOrder fd

breadthFirst' :: [Tree a] -> [a]
breadthFirst' [] = []
breadthFirst' (Empty : as) = breadthFirst' as
breadthFirst' ((Node a fe fd) : as) = a : breadthFirst' (as ++ [fe] ++ [fd])

breadthFirst :: Tree a -> [a]
breadthFirst Empty = []
breadthFirst a = breadthFirst' [a]

build :: Eq a => [a] -> [a] -> Tree a
build [ ] [ ]              = Empty
build (x:preorder) inorder = Node x
                                 (build leftPreorder  leftInorder )
                                 (build rightPreorder rightInorder)
    where  
        leftInorder   = takeWhile (/= x) inorder
        leftPreorder  = take (length leftInorder) preorder
        rightPreorder = drop (length leftInorder) preorder
        rightInorder  = tail (dropWhile (/= x) inorder)

overlap :: (a -> a -> a) -> Tree a -> Tree a -> Tree a
overlap _ Empty t2 = t2
overlap _ t1 Empty = t1
overlap op (Node a fe fd) (Node b fe' fd') = Node (op a b) (overlap op fe fe') (overlap op fd fd')