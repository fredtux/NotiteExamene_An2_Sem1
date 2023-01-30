patrat :: Integer -> Integer -> Integer
patrat x y =
    x^2 + y^2

paritate :: Integer -> String
paritate x
    | mod x 2 == 0 = "Par"
    | otherwise = "Impar"

factorial :: Integer -> Integer
factorial 0 = 1
factorial x = x * factorial (x - 1)

greaterThan :: Integer -> Integer -> Bool
greaterThan x y =
    if(x > 2 * y)
        then True
        else False