factori :: Int -> [Int]
factori n = [x | x <-[1.. (abs n)], mod n x == 0]

prim :: Int -> Bool
prim n
    | length (factori n) == 2 = True
    | otherwise = False


numerePrime :: Int -> [Int]
numerePrime n = [x | x <-[2..n], prim x]

firstEl :: [(Char, Int)] -> [Char]
firstEl l = map (\(x,y) -> x) l

sumList :: [[Int]] -> [Int]
sumList l = map (\x -> sum x) l

prel2 :: [Int] -> [Int]
prel2 l = map (\x -> if(even x) then div x 2 else x*2) l

charsir :: Char -> [String] -> [String]
charsir c l = filter (\x -> elem c x) l

patratimpar :: [Int] -> [Int]
patratimpar l = map (\x -> x^2) (filter odd l)

patratpozimpar :: [Int] -> [Int]
patratpozimpar l = map (\(x,y) -> y^2) (filter (\(x,y) -> odd x) (zip [1..(length l)] l))

numaiVocale :: [String] -> [String]
numaiVocale l = map (\x -> filter (\y -> elem y "aeiouAEIOU") x) l

mymap :: (a -> b) -> [a] -> [b]
mymap f [] = []
mymap f (x:xs) = [f x] ++ mymap f xs

mymaptest :: [Int] -> [Int]
mymaptest l = mymap (\x -> x^2) l

myfilter :: (a -> Bool) -> [a] -> [a]
myfilter f [] = []
myfilter f (x : xs)
    | f x = [x] ++ myfilter f xs
    | otherwise = myfilter f xs

myfiltertest :: [Int] -> [Int]
myfiltertest l = myfilter odd l