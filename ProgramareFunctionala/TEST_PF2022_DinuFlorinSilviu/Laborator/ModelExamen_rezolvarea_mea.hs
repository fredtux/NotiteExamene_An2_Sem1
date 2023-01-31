-- 1
data Point = Pt [Int]
    deriving Show

data Arb = Empty | Node Int Arb Arb
    deriving Show

class ToFromArb a where
    toArb :: a -> Arb
    fromArb :: Arb -> a

instance ToFromArb (Point) where
    toArb (Pt []) = Empty
    toArb (Pt (x:xs)) = Node x (toArb (Pt (filter (<x) xs))) (toArb (Pt (filter (>=x) xs)))
    fromArb Empty = (Pt [])
    fromArb (Node x ast adr) = let Pt left = fromArb ast; Pt right = fromArb adr in Pt(left ++ [x] ++ right)

-- 2
-- cu selectie
getFromInterval :: Int -> Int -> [Int] -> [Int]
getFromInterval a b l = [x | x<-l, x >=a && x <= b]
-- cu recursivitate
getFromInterval' :: Int -> Int -> [Int] -> [Int]
getFromInterval' a b [] = []
getFromInterval' a b (x:xs)
    | a <= x && b >= x = [x] ++ getFromInterval' a b xs
    | otherwise = getFromInterval' a b xs
-- cu monade
getFromInterval'' :: Int -> Int -> [Int] -> [Int]
getFromInterval'' a b l = do
    x <- l
    if (x >=a && x <= b)
        then return (x)
    else
        []
{--
getFromInterval 5 7 [1..10] == [5,6,7]
getFromInterval' 5 7 [1..10] == [5,6,7]
getFromInterval'' 5 7 [1..10] == [5,6,7]
--}
-- 3
newtype ReaderWriter env a = RW (getRW :: env -> (a, String))

instance Functor (ReaderWriter env) where
    fmap f ma = pure f <*> ma

instance Applicative (ReaderWriter env) where
    pure f = return f
    mf <*> ma = do
        f <- mf
        va <- ma
        return (f va)

-- instance Monad (ReaderWriter env) where
--     return va = (\x -> (va, ""))
--     ma >>= k = RW f
--         where
--             f env = let (va, s1) = getRW ma env
--                         (vb, s2) = getRW (k va) env
--                     in (vb, s1 ++ s2)

instance Monad (ReaderWriter env) where
  return x = RW (\_ -> (x, ""))
  (RW f) >>= g = RW (\e -> let (a, s1) = f e
                               (RW h) = g a
                               (b, s2) = h e
                           in (b, s1 ++ s2))
