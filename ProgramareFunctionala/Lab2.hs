poly :: Double -> Double -> Double -> Double -> Double
poly a b c x = a * x + x^2 + b * x + c

eeny :: Integer -> String
eeny x
    | even(x) = "eeny"
    | otherwise = "meeny"

fizzbuzz :: Integer -> String
fizzbuzz x
    | mod x 3 == 0 && mod x 5 == 0 = "FizzBuzz"
    | mod x 3 == 0 = "Fizz"
    | mod x 5 == 0 = "Buzz"

tribonacci :: Integer -> Integer
tribonacci n
    | n <= 2 = 1
    | n == 3 = 2
    | otherwise = tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3)

tribonacci2 :: Integer -> Integer
tribonacci2 1 = 1
tribonacci2 2 = 1
tribonacci2 3 = 2
tribonacci2 n = tribonacci2(n - 1) + tribonacci2(n - 2) + tribonacci2(n - 3)

verifL :: [Int] -> Bool
verifL l
    | mod (length l) 2 == 0 = True
    | otherwise = False

takefinal :: [Int] -> Int -> [Int]
takefinal l n
    | (length l) < n = l
    | otherwise = drop (length l - n) l

remove :: [Int] -> Int -> [Int]
remove l n
    | (length l) < n = l
    | otherwise = (take n l) ++ (drop (n + 1) l)

myreplicate :: Int -> Int -> [Int]
myreplicate 0 v = []
myreplicate n v = [v] ++ myreplicate (n - 1) v

sumImp :: [Int] -> Int
sumImp [] = 0
sumImp (h:t)
    | mod h 2 == 1 = h + t'
    | otherwise = t'
    where t' = sumImp t

totalLen :: [String] -> Int
totalLen [] = 0
totalLen (h:t)
    | (head h) == 'A' = length h + t'
    | otherwise = t'
    where t' = totalLen t