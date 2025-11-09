module Instructions where 


import Types

import Prelude hiding (Right, Left)
import Data.List        (findIndex)
import Data.List.Split  (split, keepDelimsR, oneOf)
import Data.Maybe       (fromJust)

strandToEnzymes :: Strand -> [[Maybe Instruction]]
strandToEnzymes strand =
  split (keepDelimsR $ oneOf [Just Pun]) $ map basePairToInstruction $ strandToBasePairs strand


startingBase :: [Maybe Instruction] -> Base
startingBase insts = 
  let 
    fds = map instructionToFoldingDirection insts 
  in
  case angle fds of 
    0      -> A   
    90     -> C
    180    -> T
    270    -> G
    (-90)  -> G
    (-180) -> T
    (-270) -> C
  where 
    angle fds = sum (map rotation fds)  
    rotation fd = 
      case fd of
        Just Straight -> 0
        Just Right    -> (-90)
        Just Left     -> 90
          -- this is an issue, what do I do with a Nothing
          -- leave undefined for now - implementation will change with splitting pun 
        _             -> undefined

selectFirstMatching :: Base -> Strand -> Maybe BoundPosition
selectFirstMatching base strand = findIndex (==base) strand 


strandToBasePairs :: Strand -> [[Base]]
strandToBasePairs [] = []
strandToBasePairs [a] = [[a]]
strandToBasePairs (a:b:as) = [a,b] : strandToBasePairs as

basePairToInstruction :: [Base] -> Maybe Instruction
basePairToInstruction bp =
  case bp of 
    [A,A] -> Just Pun 
    [A,C] -> Just Cut
    [A,G] -> Just Del
    [A,T] -> Just Swi
    [C,A] -> Just Mvr
    [C,C] -> Just Mvl
    [C,G] -> Just Cop
    [C,T] -> Just Off 
    [G,A] -> Just Ina 
    [G,C] -> Just Inc
    [G,G] -> Just Ing
    [G,T] -> Just Int
    [T,A] -> Just Rpy
    [T,C] -> Just Rpu
    [T,G] -> Just Lpy 
    [T,T] -> Just Lpu
    _    -> Nothing

instructionToFoldingDirection :: Maybe Instruction -> Maybe FoldingDirection
instructionToFoldingDirection inst = 
  case inst of 
    Nothing  -> Nothing
    Just Pun -> Nothing 
    Just Cut -> Just Straight
    Just Del -> Just Straight
    Just Swi -> Just Right  
    Just Mvr -> Just Straight
    Just Mvl -> Just Straight
    Just Cop -> Just Right
    Just Off -> Just Left  
    Just Ina -> Just Straight
    Just Inc -> Just Right
    Just Ing -> Just Right
    Just Int -> Just Left 
    Just Rpy -> Just Right
    Just Rpu -> Just Left 
    Just Lpy -> Just Left 
    Just Lpu -> Just Left 

