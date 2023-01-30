{-
class Functor f where
fmap : : ( a -> b ) -> f a -> f b
-}
newtype Identity a = Identity a
    deriving Show

instance Functor Identity where
    fmap f (Identity x) = Identity (f x)

data Pair a = Pair a a
    deriving Show

instance Functor Pair where
    fmap f (Pair a1 a2) = Pair (f a1) (f a2)

data Constant a b = Constant b
    deriving Show

instance Functor (Constant a) where
    fmap f (Constant b) = Constant (f b)

data Two a b = Two a b
    deriving Show

instance Functor (Two a) where
    fmap f (Two a b) = Two a (f b)

data Three a b c = Three a b c
    deriving Show

instance Functor (Three a b) where
    fmap f (Three a b c) = Three a b (f c)

data Three' a b = Three' a b b
    deriving Show

instance Functor (Three' a) where
    fmap f (Three' a b1 b2) = Three' a (f b1) (f b2)


data Four a b c d = Four a b c d
    deriving Show

instance Functor (Four a b c) where
    fmap f (Four a b c d) = Four a b c (f d)

data Four'' a b = Four'' a a a b
    deriving Show

instance Functor (Four'' a) where
    fmap f (Four'' a1 a2 a3 b) = Four'' a1 a2 a3 (f b)

data Quant a b = Finance | Desk a | Bloor b
    deriving Show

instance Functor (Quant a) where
    fmap _ Finance = Finance
    fmap _ (Desk a) = Desk a
    fmap f (Bloor b) = Bloor (f b)


data LiftItOut f a = LiftItOut (f a)
    deriving Show

instance Functor f => Functor (LiftItOut f) where
    fmap f (LiftItOut fa) = LiftItOut(fmap f fa)

data Parappa f g a = DaWrappa (f a) (g a)
    deriving Show

instance (Functor f, Functor g) => Functor(Parappa f g) where
    fmap f (DaWrappa fa ga) = DaWrappa(fmap f fa)(fmap f ga)

data IgnoreOne f g a b = IgnoringSomething (f a) (g b)
    deriving Show

instance (Functor f, Functor g) => Functor(IgnoreOne f g a) where
    fmap f (IgnoringSomething fa gb) = IgnoringSomething fa (fmap f gb)

data Notorious g o a t = Notorious (g o) (g a) (g t)
    deriving Show

instance Functor g => Functor(Notorious g o a) where
    fmap f (Notorious ga gb gt) = Notorious ga gb (fmap f gt)

data GoatLord a = NoGoat | OneGoat a | MoreGoats (GoatLord a) (GoatLord a) (GoatLord a)
    deriving Show

instance Functor GoatLord where
    fmap f = go
        where
            go NoGoat = NoGoat
            go (OneGoat x) = OneGoat (f x)
            go (MoreGoats g1 g2 g3) = MoreGoats (go g1) (go g2) (go g3)

data TalkToMe a = Halt | Print String a | Read (String -> a)

getHalt (Halt) = "Halt"
getPrint (Print s x) = show s ++ " " ++ show x
getVal (Read f) str = f str

instance Functor TalkToMe where
    fmap _ Halt = Halt
    fmap f (Print s a) = Print s (f a)
    fmap f (Read fa) = Read (f . fa)