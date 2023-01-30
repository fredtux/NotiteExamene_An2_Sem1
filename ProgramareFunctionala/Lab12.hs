import Data.Monoid


elem1 :: (Foldable t, Eq a) => a -> t a -> Bool
elem1 a l = foldr (\x xs -> (x == a) || xs) False l

elem2 :: (Foldable t, Eq a) => a -> t a -> Bool
elem2 a l = getAny(foldMap(\x -> Any(x == a)) l)

null1 :: (Foldable t) => t a -> Bool
null1 l = foldr (\x xs -> False && xs) True l

null2 :: (Foldable t) => t a -> Bool
null2 l = getAll(foldMap(\x -> All False) l)

length1 :: (Foldable t) => t a -> Int
length1 l = foldr (\x xs -> 1 + xs) 0 l

length2 :: (Foldable t) => t a -> Int
length2 l = getSum (foldMap(\x -> Sum 1) l)

toList1 :: (Foldable t) => t a -> [a]
toList1 l = foldr (\x xs -> [x] ++ xs) [] l

toList2 :: (Foldable t) => t a -> [a]
toList2 l = foldMap (\x -> [x]) l

fold1 :: (Foldable t, Monoid m) => t m -> m
fold1 m = foldMap (\x -> x) m -- Hint: folosiți foldMap

data Constant a b = Constant b

instance Foldable (Constant a) where
    foldMap f (Constant a) = f a

data Two a b = Two a b

instance Foldable (Two a) where
    foldMap f (Two a b) = f b

data Three a b c = Three a b c

instance Foldable (Three a b) where
    foldMap f (Three a b c) = f c

data Three' a b = Three' a b b

instance Foldable (Three' a) where
    foldMap f (Three' a b c) = f b <> f c

data Four' a b = Four' a b b b

instance Foldable (Four' a) where
    foldMap f (Four' a b c d) = f b <> f c <> f d

data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)

instance Foldable (GoatLord) where
    foldMap f NoGoat = mempty
    foldMap f (OneGoat a) = f a
    foldMap f (MoreGoats a b c) = foldMap f a <> foldMap f b <> foldMap f c