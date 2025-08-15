module Main where 

--import OptParse
import System.Environment (getArgs)




main :: IO () 
main = do
  args <- getArgs 
--  processArguments args  
  putStrLn "This is just a test message" 


-- FUNCTION 
-- Poll user input, and confirm that it is valid before returning it
getUserInputStrand :: IO String 
getUserInputStrand = do
    putStrLn "Enter a strand consisting only of A, G, T, or C."
    inputStrand <- getLine
    case inputStrand of 
      inputStrand  | not (getValidStrand inputStrand) -> do
          putStrLn "Strands can only consist of A, G, T, or C." 
          getUserInputStrand
      _ -> return inputStrand

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
getValidStrand :: String -> Bool
getValidStrand strand = not (null strand) && all isValidStrandElement strand
