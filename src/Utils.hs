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

-- it's hard to chain this all together for printing
showBaseAsComplement :: Base -> IO ()
showBaseAsComplement  b = 
  case b of 
    A -> putStr "ꓯ"
    G -> putStr "⅁"
    T -> putStr "ꓕ"
    C -> putStr "ꓛ"
