module GameState where 

import Types
import Utils 

import Control.Monad.State

-- a data type to represent the game state: 
data Game = Game { strands :: (Strand, Strand) -- fst is Main, snd is complement 
                 , enzymes :: [[Instruction]]  -- each element 
                 , foldingPatterns :: [[FoldingDirection]]
                 , numberOfEnzymes :: Int
                 , boundPosition :: BoundPosition
                 , currentlyBoundStrand :: BoundStrand
                 } deriving (Show) 

displayGameStrands :: Game -> IO ()
displayGameStrands g = do 
  showBoundPosition Upper (boundPosition g) (currentlyBoundStrand g)
  showStrandAsComplement $ snd $ strands g
  showStrand $ fst $ strands g
  showBoundPosition Lower (boundPosition g) (currentlyBoundStrand g)

generateRandomStrand :: Int -> State Game Strand
generateRandomStrand i = do
  game <- get 
  randy <- randStrand i 
  return $ fst $ strands game
