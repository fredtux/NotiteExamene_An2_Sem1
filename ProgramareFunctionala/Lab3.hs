import Data.Char (isDigit)
import Data.Char (digitToInt)

palindrom :: String -> Bool
palindrom x = (reverse x) == x

nrVocaleCuvant :: String -> Int
nrVocaleCuvant cuv = length(filter(\x -> elem x "aeiouAEIOU") cuv)

nrVocale :: [String] -> Int
nrVocale [] = 0
nrVocale (h:t) = nrVocaleCuvant h + nrVocale t

divizori :: Int -> [Int]
divizori n = [x|x <- [1..n], mod n x == 0]

listadiv :: [Int] -> [[Int]]
listadiv [] = []
listadiv (h:t) = [divizori h] ++ listadiv t

inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec a b [] = []
inIntervalRec a b (x : xs)
    | x >= a && x <= b = [x] ++ xs'
    | otherwise = xs'
    where xs' = inIntervalRec a b xs

inIntervalComp :: Int -> Int -> [Int] -> [Int]
inIntervalComp a b [] = []
inIntervalComp a b l = [x | x <- [a..b], elem x l]

pozitiveRec :: [Int] -> Int
pozitiveRec [] = 0
pozitiveRec (x : xs)
    | x > 0 = 1 + pozitiveRec xs
    | otherwise = pozitiveRec xs

pozitiveComp :: [Int] -> Int
pozitiveComp l = length [x | x <- l, x > 0]

pozitiiImpareRecAj :: Int -> [Int] -> [Int]
pozitiiImpareRecAj a [] = []
pozitiiImpareRecAj a (x : xs)
    | odd x = [a] ++ pozitiiImpareRecAj (a + 1) xs
    | otherwise = pozitiiImpareRecAj (a+1) xs

pozitiiImpareRec :: [Int] -> [Int]
pozitiiImpareRec l = pozitiiImpareRecAj 0 l

poiztiiImpareComp :: [Int] -> [Int]
poiztiiImpareComp l = [x | (x,y) <- zip [0..(length l)] l, odd y]

multiDigitsRec :: String -> Int
multiDigitsRec "" = 1
multiDigitsRec (x : xs)
    | isDigit x = digitToInt x * multiDigitsRec xs
    | otherwise = 1 * multiDigitsRec xs

multiDigitsComp :: String -> Int
multiDigitsComp str = product [digitToInt x | x <- str, isDigit x]