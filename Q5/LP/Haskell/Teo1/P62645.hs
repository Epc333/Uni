main :: IO ()
main = do
    x <- getContents
    print $ f x

f :: String -> Int
f = sum . map s2i . words

-- f x = sum $ map (\x -> read x :: Int) (words x)

s2i :: String -> Int
s2i = read
    