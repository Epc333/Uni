data Racional = Racional Integer Integer
    deriving (Eq)

racional :: Integer -> Integer -> Racional
--racional = Racional
racional a b = Racional (div a g) (div b g) 
  where g = gcd a b

numerador :: Racional -> Integer
numerador (Racional n _) = n

denominador :: Racional -> Integer
denominador (Racional _ d) = d

instance Show Racional where
    show (Racional n d) = (show n) ++ "/" ++ (show d)

    
