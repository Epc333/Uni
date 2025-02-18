
data Nat = Z | S Nat
    deriving Show


rec :: a -> (Nat -> a -> a) -> Nat -> a
rec base step Z = base 
rec base step (S n) = step n (rec base step n)


-- indica si un natural e ́s parell o no
isEven :: Nat -> Bool 
isEven = rec base step
    where 
        base = True
        step = \n b -> not b


-- retorna la suma de dos naturals
add :: Nat -> (Nat -> Nat)
add = rec base step 
    where 
        base = id
        step = \n f m -> S (f m)


-- retorna el producte de dos naturals
mul :: Nat -> (Nat -> Nat)
mul = rec base step 
    where 
        base = const Z
        step = \n f m -> add m (f m)


-- retorna el factorial d’un natural
fact :: Nat -> Nat 
fact = rec base step 
    where 
        base = S Z
        step = \n f -> mul (S n) f


