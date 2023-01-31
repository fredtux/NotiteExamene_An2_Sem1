data Punct = Pt [Int]

instance Show Punct where
    show (Pt []) = "()"
    show (Pt (x:xs)) = "(" ++  afisare x xs ++ ")"
        where
            afisare x [] = show x
            afisare x (y:ys) = show x ++ "," ++ afisare y ys

data Arb = Vid | F Int | N Arb Arb
    deriving Show

class ToFromArb a where
    toArb :: a -> Arb
    fromArb :: Arb -> a

instance ToFromArb Punct where
    toArb p = catre p
        where
            catre (Pt []) = Vid
            catre (Pt (x:xs)) = N (F x) (catre (Pt xs))
    fromArb t = dela t
        where
            dela Vid = (Pt [])
            dela (N (F x) a) = Pt ([x] ++ (tolist (dela a)))
                where
                    tolist (Pt l) = l
            dela (N a (F x)) = Pt((tolist (dela a)) ++ [x])
                where
                    tolist (Pt l) = l
            dela (N a b) = Pt((tolist(dela a)) ++ (tolist(dela b)))
                where
                    tolist (Pt l) = l
-- Pt [1,2,3]
-- (1, 2, 3)

-- Pt []
-- ()

-- toArb (Pt [1,2,3])
-- N (F 1) (N (F 2) (N (F 3) Vid))
-- fromArb $ N (F 1) (N (F 2) (N (F 3) Vid)) :: Punct
--  (1,2,3)
data Geo a = Square a | Rectangle a a | Circle a
    deriving Show

class GeoOps g where
  perimeter :: (Floating a) => g a -> a
  area :: (Floating a) =>  g a -> a

instance GeoOps Geo where
    perimeter (Square x) = 4 * x
    perimeter (Rectangle x y) = 2 * (x + y)
    perimeter (Circle x) = 2 * pi * x
    area (Square x) = x^2
    area (Rectangle x y) = x * y
    area (Circle x) = pi * (x ^ 2)

instance (Floating a, Eq a) => Eq (Geo a) where
    g1 == g2 = perimeter g1 == perimeter g2

-- ghci> pi
-- 3.141592653589793
