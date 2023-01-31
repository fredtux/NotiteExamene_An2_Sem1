{- 
class Functor f where 
     fmap :: (a -> b) -> f a -> f b 
class Functor f => Applicative f where
    pure :: a -> f a
    (<*>) :: f (a -> b) -> f a -> f b

Just length <*> Just "world"

Just (++" world") <*> Just "hello,"
pure (+) <*> Just 3 <*> Just 5
pure (+) <*> Just 3 <*> Nothing
(++) <$> ["ha","heh"] <*> ["?","!"]
-}
data List a = Nil
            | Cons a (List a)
        deriving (Eq, Show)

instance Functor List where
    fmap f Nil = Nil
    fmap f (Cons a list) = Cons (f a) (f <$> list)
instance Applicative List where
    pure x = Cons x Nil
    Nil <*> listElem = Nil
    Cons f listf <*> listElem = adaugare (f <$> listElem) (listf <*> listElem)
        where
            adaugare Nil l = l
            adaugare (Cons a l1) l2 = Cons a (adaugare l1 l2)

f = Cons (+1) (Cons (*2) Nil)
v = Cons 1 (Cons 2 Nil)
test1 = (f <*> v) == Cons 2 (Cons 3 (Cons 2 (Cons 4 Nil)))

data Cow = Cow {
        name :: String
        , age :: Int
        , weight :: Int
        } deriving (Eq, Show)

noEmpty :: String -> Maybe String
noEmpty [] = Nothing
noEmpty str = Just str

noNegative :: Int -> Maybe Int
noNegative x = if(x < 0) then Nothing else Just x

test21 = noEmpty "abc" == Just "abc"
test22 = noNegative (-5) == Nothing 
test23 = noNegative 5 == Just 5 

cowFromString :: String -> Int -> Int -> Maybe Cow
cowFromString a b c =  if (noEmpty a) /= Nothing && (noNegative b)  /= Nothing && (noNegative c)  /= Nothing then Just (Cow a b c) else Nothing

test24 = cowFromString "Milka" 5 100 == Just (Cow {name = "Milka", age = 5, weight = 100})

cowFromString' :: String -> Int -> Int -> Maybe Cow
cowFromString' a b c = Cow <$> noEmpty a <*> noNegative b <*> noNegative c

newtype Name = Name String deriving (Eq, Show)
newtype Address = Address String deriving (Eq, Show)

data Person = Person Name Address
    deriving (Eq, Show)

validateLength :: Int -> String -> Maybe String
validateLength n [] = Nothing
validateLength n str = if length str < n then Just str else Nothing

test31 = validateLength 5 "abc" == Just "abc"
mkName :: String -> Maybe Name
mkName str = if (validateLength 25 str) /= Nothing then Just (Name (str)) else Nothing

mkAddress :: String -> Maybe Address
mkAddress str = if (validateLength 100 str) /= Nothing then Just (Address (str)) else Nothing 

test32 = mkName "Gigel" ==  Just (Name "Gigel")
test33 = mkAddress "Str Academiei" ==  Just (Address "Str Academiei")

mkPerson :: String -> String -> Maybe Person
mkPerson name addr = Person <$> mkName name <*> mkAddress addr

test34 = mkPerson "Gigel" "Str Academiei" == Just (Person (Name "Gigel") (Address "Str Academiei"))