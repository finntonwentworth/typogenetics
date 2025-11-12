module Main where 

import Types 
import Instructions
import Utils
import GameState

import Data.Maybe (fromJust, fromMaybe)

main :: IO () 
main = undefined



















{-
-- Creates a test start game state so I can check printing
createInitialGameState :: Int -> IO ()
createInitialGameState num = do 
  initialStrand <- randStrand num
  -- just for test printing 
  dummyComplement <- randStrand num 
  let insts = strandToEnzymes initialStrand
  let fds = map (map instructionToFoldingDirection) insts
  let g = Game { mainStrand = initialStrand
               , complementaryStrand = dummyComplement
               , enzymes = map (map fromJust) insts 
               , foldingPatterns = map (map fromJust) fds 
               , numberOfEnzymes = length $ enzymes g
               -- Exception thrown with Pun - fromJust errors 
               , boundPosition = fromJust $ selectFirstMatching (startingBase $ insts !! 0) initialStrand
               , currentlyBoundStrand = Lower
               }
  displayGameStrands g

-- anyway to incorporate randStrand into this?
testGame :: Game
testGame = 
  let 
    s = [A,G,T,C] 
    insts = strandToEnzymes s
    fds = map (map instructionToFoldingDirection) insts
  in 
  Game { mainStrand = s
       , complementaryStrand = s
       , enzymes = map (map fromJust) insts 
       , foldingPatterns = map (map fromJust) fds 
       , numberOfEnzymes = length $ enzymes testGame 
       , boundPosition = 2
       , currentlyBoundStrand = Lower 
       }
  
-}