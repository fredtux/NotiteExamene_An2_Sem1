-- Cu recursie
alternativ :: [Int] -> [Int] -> [Int]
alternativ l1 l2 = alt2 (zip [1,3..] l1) (zip [2,4..] l2)

alt2 :: [(Int, Int)] -> [(Int, Int)] -> [Int]    
alt2 a [] = map (\(x,y) -> y) a
alt2 [] b = map (\(x,y) -> y) b
alt2 (a:as) (b:bs)
    | fst a < fst b = [snd a] ++ alt2 (as) (b:bs)
    | otherwise = [snd b] ++ alt2 (a:as) bs

-- Cu foldr
alternativ' :: [Int] -> [Int] -> [Int]
alternativ' l1 l2 = foldr (\(x,y) acc -> x:y:acc) [] (zip l1 l2)