patratimpar :: [Int] -> Int
patratimpar l = foldr (+) 0 (map (\x -> x^2) (filter (\x -> odd x) l))

alltrue :: [Bool] -> Bool
alltrue l = foldr (&&) True l

allVerifies :: (Int -> Bool) -> [Int] -> Bool
allVerifies f l = foldr (&&) True (map f l)

anyVerifies :: (Int -> Bool) -> [Int] -> Bool
anyVerifies f l = foldr (||) False (map f l)

mapFoldr :: (a -> b) -> [a] -> [b]
mapFoldr f [] = []
mapFoldr f l = foldr (\y ys -> (f y) : ys) [] l

mapFoldrTest :: [Int] -> [Int]
mapFoldrTest l = mapFoldr (\x -> x^2) l

filterFoldr :: (a->Bool) -> [a] -> [a]
filterFoldr f l = foldr (\x xs -> if (f x) then x:xs else xs) [] l

myfiltertest :: [Int] -> [Int]
myfiltertest l = filterFoldr odd l

listToInt :: [Integer] -> Integer
listToInt l = foldl (\x xs -> 10 * x + xs) 0 l

rmChar :: Char -> String -> String
rmChar c l = foldr (\x xs -> if(x == c) then xs else x:xs) [] l

rmCharsRec :: String -> String -> String
rmCharsRec s1 [] = []
rmCharsRec [] s2 = s2
rmCharsRec (x1:xs1) s2 = rmCharsRec xs1 (rmChar x1 s2)

rmCharsFold :: String -> String -> String
rmCharsFold s1 s2 = foldr (\x xs -> if(elem x s1) then xs else x:xs) [] s2