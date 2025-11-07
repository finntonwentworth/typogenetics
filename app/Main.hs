module Main where 

import Types 
import Instructions
import Utils

import Data.Maybe (fromJust, fromMaybe)

main :: IO () 
main = undefined

-- Creates a test start game state so I can check printing
createInitialGameState :: Int -> IO ()
createInitialGameState num = do 
  initialStrand <- randStrand num
  -- just for test printing 
  dummyComplement <- randStrand num 
  let insts = strandToInstructions initialStrand
  let fds = map instructionToFoldingDirection insts
  let g = Game { mainStrand = initialStrand
               , complementaryStrand = dummyComplement
               , instructions = map fromJust insts 
               , foldingPattern = map fromJust fds 
               -- Exception thrown with Pun - fromJust errors 
               , boundPosition = fromJust $ selectFirstMatching (startingBase insts) initialStrand
               , currentlyBoundStrand = Lower
               }
  displayGameStrands g

-- anyway to incorporate randStrand into this?
testGame :: Game
testGame = 
  let 
    s = [A,G,T,C] 
    insts = strandToInstructions s
    fds = map instructionToFoldingDirection insts
  in 
  Game { mainStrand = s
       , complementaryStrand = s
       , instructions = map fromJust insts 
       , foldingPattern = map fromJust fds 
       , boundPosition = 2
       , currentlyBoundStrand = Lower 
       }
  
