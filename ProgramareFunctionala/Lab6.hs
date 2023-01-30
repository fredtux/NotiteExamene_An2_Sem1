data Fruct
  = Mar String Bool
  | Portocala String Int

ionatanFaraVierme = Mar "Ionatan" False
goldenCuVierme = Mar "Golden Delicious" True
portocalaSicilia10 = Portocala "Sanguinello" 10
listaFructe = [Mar "Ionatan" False,
                Portocala "Sanguinello" 10,
                Portocala "Valencia" 22,
                Mar "Golden Delicious" True,
                Portocala "Sanguinello" 15,
                Portocala "Moro" 12,
                Portocala "Tarocco" 3,
                Portocala "Moro" 12,
                Portocala "Valencia" 2,
                Mar "Golden Delicious" False,
                Mar "Golden" False,
                Mar "Golden" True]

ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Portocala soi _) = if(elem soi ["Tarocco", "Moro", "Sanguinello"]) then True else False
ePortocalaDeSicilia (Mar _ _) = False
test_ePortocalaDeSicilia1 =
    ePortocalaDeSicilia (Portocala "Moro" 12) == True
test_ePortocalaDeSicilia2 =
    ePortocalaDeSicilia (Mar "Ionatan" True) == False

nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia l = foldr (\(Portocala _ felii) xs -> felii + xs) 0 (filter ePortocalaDeSicilia l)

test_nrFeliiSicilia = nrFeliiSicilia listaFructe == 52

isMarVierme :: Fruct -> Bool
isMarVierme (Mar _ vierme) = vierme
isMarVierme _ = False

nrMereViermi :: [Fruct] -> Int
nrMereViermi l = foldr (\x xs -> if (isMarVierme x) then 1 + xs else xs) 0 l

test_nrMereViermi = nrMereViermi listaFructe == 2

type NumeA = String
type Rasa = String
data Animal = Pisica NumeA | Caine NumeA Rasa
    deriving Show

vorbeste :: Animal -> String
vorbeste (Pisica _) = "Meow!"
vorbeste (Caine _ _) = "Woof!"

rasa :: Animal -> Maybe String
rasa (Pisica _) = Nothing
rasa (Caine _ rasa) = Just rasa

data Linie = L [Int]
   deriving Show
data Matrice = M [Linie]
   deriving Show

verifica :: Matrice -> Int -> Bool
m = M [L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]
verifica (M m) n =  foldr (&&) True (map (\x -> x == n) (foldr(\(L l) ms -> [sum l] ++ ms) [] m))
test_verif1 = verifica (M[L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) 10 == False
test_verif2 = verifica (M[L[2,20,3], L[4,21], L[2,3,6,8,6], L[8,5,3,9]]) 25 == True
doarPozN :: Matrice -> Int -> Bool
doarPozN (M m) n = foldr (&&) True (foldr (\(L l) xs -> [(foldr (\y ys -> y > 0 && ys) True l)] ++ xs) [] (filter (\(L l) -> length l == n) m))

testPoz1 = doarPozN (M [L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3 == True

testPoz2 = doarPozN (M [L[1,2,-3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3 == False
corect :: Matrice -> Bool
corect (M m) = foldr (\x xs -> x == lh && xs) (True) (foldr (\(L l) xs -> [(length l)] ++ xs) [] m)
    where
        lh = foldr (\(poz,(L l)) xs -> if(poz == 0) then (length l) + xs else xs) 0 (zip [0.. (length m)] m)

testcorect1 = corect (M[L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) == False
testcorect2 = corect (M[L[1,2,3], L[4,5,8], L[3,6,8], L[8,5,3]]) == True