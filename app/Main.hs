module Main where 

import Types 
import Instructions
import Utils

import Data.Maybe (fromJust)

main :: IO () 
main = undefined

test = do 
  strand <- randStrand 10 
  putStrLn ("Strand: " ++ show strand) 
  putStrLn ("Instructions: " ++ show (strandToInstructions strand)) 
  putStrLn ("Starting Base: " ++ show (startingBase $ strandToInstructions strand)) 


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
               , boundPosition = 1
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
       , boundPosition = 0
       , currentlyBoundStrand = Upper 
       }
  
