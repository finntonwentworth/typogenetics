module Utils where 

import System.Random 
import Control.Monad (replicateM)

import Types 

instance Random Base where 
  randomR (low, high) g = 
    let (i , g') = randomR (fromEnum low, fromEnum high) g
    in (toEnum i, g')
  random g = 
    let (i, g') = randomR (fromEnum (minBound :: Base), fromEnum (maxBound :: Base )) g
    in (toEnum i, g')
  

randStrand :: Int -> IO Strand
randStrand len = replicateM len (randomIO :: IO Base)

-- Pretty printing for strand 
showStrand :: Strand -> IO ()
showStrand s = do 
  mapM_ putStr (map show s)
  putStrLn ""

showStrandAsComplement :: Strand -> IO ()
showStrandAsComplement  [] = putStrLn ""
showStrandAsComplement (b:bs) = 
  case b of 
    A -> do  
      putStr "ꓯ"
      showStrandAsComplement bs
    G -> do 
      putStr "⅁"
      showStrandAsComplement bs
    T -> do
      putStr "ꓕ"
      showStrandAsComplement bs
    C -> do
      putStr "ꓛ"
      showStrandAsComplement bs

showBoundPositionUpper :: Integer -> BoundStrand -> IO ()  
showBoundPositionUpper pos bound = 
  case bound of 
    Lower -> putStrLn "" 
    Upper -> putStrLn "↓"

showBoundPositionLower :: Integer -> BoundStrand -> IO ()  
showBoundPositionLower pos bound = 
  case bound of 
    Lower -> putStrLn "↑" 
    Upper -> putStrLn ""

showBoundPosition :: BoundStrand -> Game -> IO ()
showBoundPosition b g = 
  if b == Upper
    then showBoundPositionUpper 0 (currentlyBoundStrand g) 
    else showBoundPositionLower 0 (currentlyBoundStrand g)

displayGameStrands :: Game -> IO ()
displayGameStrands g = do 
  showBoundPosition Upper g
  showStrandAsComplement $ complementaryStrand g
  showStrand $ mainStrand g
  showBoundPosition Lower g