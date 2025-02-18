mult' _ [] p = p
mult' a (bx:bxs) p = px : mult' a bxs (pxs++[0.0])
  where (px:pxs) = zipWith (+) p (map (*bx) a)


mult :: [Double] -> [Double] -> [Double]
mult [] [] = []
mult a b = pxs ++ [px]
  where (px:pxs) = reverse $ mult' (reverse a) (reverse b) $ take (length a) $ repeat 0.0
