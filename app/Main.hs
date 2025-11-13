module Main where 

import GameState
import Instructions 
import Types 
import Utils

main :: IO () 
main = undefined


{-
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