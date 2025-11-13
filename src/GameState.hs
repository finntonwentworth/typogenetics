module GameState where 

import Types
import Utils 
import Instructions

import Control.Monad.State
import Data.Maybe (fromJust)

-- a data type to represent the game state: 
data Game = Game { strands :: (Strand, Strand) -- fst is Main, snd is complement 
                 , enzymes :: [[Instruction]]  -- each element 
                 , foldingPatterns :: [[FoldingDirection]]
                 , numberOfEnzymes :: Int
                 , boundPosition :: BoundPosition
                 , currentlyBoundStrand :: BoundStrand
                 } deriving (Show) 

-- Creates a test start game state so I can check printing
createInitialGameState :: Int -> IO ()
createInitialGameState num = do 
  initialStrand <- randStrand num
  let insts = strandToEnzymes initialStrand
  let fds = map (map instructionToFoldingDirection) insts
  let g = Game { strands = (initialStrand, [Blank])
               , enzymes = map (map fromJust) insts 
               , foldingPatterns = map (map fromJust) fds 
               , numberOfEnzymes = length $ enzymes g
               -- Exception thrown with Pun - fromJust errors 
               , boundPosition = fromJust $ selectFirstMatching (startingBase $ insts !! 0) initialStrand
               , currentlyBoundStrand = Lower
               }
  displayGameStrands g

displayGameStrands :: Game -> IO ()
displayGameStrands g = do 
  showBoundPosition Upper (boundPosition g) (currentlyBoundStrand g)
  showStrandAsComplement $ snd $ strands g
  showStrand $ fst $ strands g
  showBoundPosition Lower (boundPosition g) (currentlyBoundStrand g)