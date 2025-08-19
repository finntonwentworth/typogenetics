module Decoding 
  (
    getUserInputStrand 
   ,generateFoldingList
   ,generateInstructionList
  )
  where

import Prelude hiding (Right, Left)

import Strands
import Instructions

-- FUNCTION 
-- Poll user input, and confirm that it is valid before returning it
getUserInputStrand :: IO Strand 
getUserInputStrand = do
    putStrLn "Enter a strand consisting only of A, G, T, or C."
    inputStrand <- getLine
    if not (getValidStrand inputStrand) 
      then do 
        putStrLn "Strands can only consist of A, G, T, or C." 
        getUserInputStrand
      else 
        return inputStrand

-- FUNCTION 
-- Check that an element of a strand is a valid element
isValidStrandElement :: Char -> Bool 
isValidStrandElement strandElement  
  | strandElement == 'A' = True 
  | strandElement == 'G' = True 
  | strandElement == 'T' = True 
  | strandElement == 'C' = True 
  | otherwise            = False

-- FUNCTION 
-- Check that each element of a strand is a valid element and that it is not the empty string
getValidStrand :: Strand -> Bool
getValidStrand strand = not (null strand) && all isValidStrandElement strand

-- FUNCTION 
-- Split the strand into a list of base pairs 
splitBasePairs :: Strand -> [[Base]]
splitBasePairs []  = []
-- this is the case when the strand has an odd number of bases
splitBasePairs [a] = [[a]]
splitBasePairs (a:b:as) = [a,b] : splitBasePairs as


-- FUNCTION 
-- Generates a list containing the decoded instructions from the inputted strand
generateInstructionList :: Strand -> [Maybe Instruction]
generateInstructionList strand = map decodeInstruction $ splitBasePairs strand   

-- FUNCTION 
-- Generates a list containing the decoded folding directions from the inputted strand
generateFoldingList :: [Maybe Instruction] -> [Maybe FoldingDirection]
generateFoldingList = map decodeFoldingDirection 

-- FUNCTION 
-- Takes a base pair and returns the corresponding Instruction
decodeInstruction :: [Base] -> Maybe Instruction
decodeInstruction basePair = 
  case basePair of 
    "AA" -> Just Pun 
    "AC" -> Just Cut
    "AG" -> Just Del
    "AT" -> Just Swi
    "CA" -> Just Mvr
    "CC" -> Just Mvl
    "CG" -> Just Cop
    "CT" -> Just Off 
    "GA" -> Just Ina 
    "GC" -> Just Inc
    "GG" -> Just Ing
    "GT" -> Just Int
    "TA" -> Just Rpy
    "TC" -> Just Rpu
    "TG" -> Just Lpy 
    "TT" -> Just Lpy
    _    -> Nothing

-- FUNCTION 
-- Takes a base pair and returns the corresponding folding direction
-- I may find defining a direction for Pun works better than Nothing
decodeFoldingDirection :: Maybe Instruction -> Maybe FoldingDirection
decodeFoldingDirection instruction = 
  case instruction of 
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
    _    -> Nothing

startingBase :: [Maybe FoldingDirection] -> Maybe Base
startingBase fp =
   case angle fp 0  of 
    0      -> Just 'A'   
    90     -> Just 'C'
    180    -> Just 'T'
    270    -> Just 'G'
    (-90)  -> Just 'G'
    (-180) -> Just 'T'
    (-270) -> Just 'C'
    _     -> Nothing 


angle :: [Maybe FoldingDirection] -> Integer -> Integer 
angle [] acc = 0 
angle (fp:fps) acc = 
  case fp of 
    _ -> undefined 
{-
-- FUNCTION 
-- Take a folding list and return the "starting angle"
startingBase :: [Maybe FoldingDirection] -> Maybe Base
startingBase  [Nothing] = Nothing
startingBase  (i:is) = 
  case i of 
    Just Straight -> undefined 
    Just Right    -> undefined 
    Just Left     -> undefined 
-- case we have processed all elements
startingBase [] acc = 
  case acc of
    0      -> Just 'A'   
    90     -> Just 'C'
    180    -> Just 'T'
    270    -> Just 'G'
    (-90)  -> Just 'G'
    (-180) -> Just 'T'
    (-270) -> Just 'C'
    _     -> Nothing 

-- FUNCTION 
-- Take an angle and pattern match to the appropriate base 
angle :: Maybe Integer -> Maybe Base 
angle = 
  case angle of 
    Just 0      -> Just 'A'
    Just 90     -> Just 'C'
    Just 180    -> Just 'T'
    Just 270    -> Just 'G'
    Just (-90)  -> Just 'G'
    Just (-180) -> Just 'T'
    Just (-270) -> Just 'C'
    _           -> Nothing 
-}


-- FUNCTION 
-- From a given base, return the indices of the bases that match that base in a strand 
availableStartingBaseList :: Base -> [Integer]
availableStartingBaseList = undefined

-- FUNCTION 
-- Takes Amino acid from instruction list and call calls the correct function
{-
callAminoAcid :: Maybe Instruction -> (Strand -> Strand)  
callAminoAcid instruction = 
  case instruction of 
    Just Pun -> Nothing 
    Just Cut ->  
    Just Del ->  
    Just Swi ->   
    Just Mvr ->  
    Just Mvl -> 
    Just Cop ->  
    Just Off ->  
    Just Ina -> 
    Just Inc ->  
    Just Ing ->  
    Just Int ->  
    Just Rpy ->  
    Just Rpu ->  
    Just Lpy ->  
    Just Lpu ->  
    _    -> Nothing
-}