module Utils where 

import Control.Monad (replicateM)
import System.Random 

import Types 

instance Random Base where 
  randomR (low, high) g = 
    let (i , g') = randomR (fromEnum low, fromEnum high) g
    in (toEnum i, g')
  random g = 
    let (i, g') = randomR (fromEnum (minBound :: Base), fromEnum (maxBound :: Base ) - 1) g
    in (toEnum i, g')


randStrand :: Int -> IO Strand
randStrand len = replicateM len (randomIO :: IO Base)

-- Pretty printing for strand - does not account for blanks?
showStrand :: Strand -> IO ()
showStrand [] = putStrLn ""
showStrand (b:bs) = 
  case b of 
    A -> do  
      putStr "A"
      showStrandAsComplement bs
    G -> do 
      putStr "G"
      showStrandAsComplement bs
    T -> do
      putStr "T"
      showStrandAsComplement bs
    C -> do
      putStr "C"
      showStrandAsComplement bs
    Blank -> do
      putStr " "
      showStrandAsComplement bs
{-
showStrand s = do 
  mapM_ putStr (map show s)
  putStrLn ""
-}

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
    Blank -> do
      putStr " "
      showStrandAsComplement bs


showBoundPosition :: BoundStrand -> BoundPosition -> BoundStrand -> IO ()
showBoundPosition print pos bound = 
  if print == Upper
    then showBoundPositionUpper pos bound 
    else showBoundPositionLower pos bound 
  where 
    showBoundPositionUpper pos bound = 
      case bound of 
        Lower -> putStrLn "" 
        Upper -> putStrLn (replicate pos ' ' ++ "↓")
    showBoundPositionLower pos bound = 
      case bound of 
        Lower  -> putStrLn (replicate pos ' ' ++ "↑")
        Upper -> putStrLn ""
