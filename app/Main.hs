module Main where 

-- import OptParse
import Strands
import Data.Maybe (isJust,fromJust)
import Control.Monad (when)

printMaybeList :: Show a => Maybe a -> IO ()
printMaybeList = liftA2 
  when isJust $ print . fromJust

main :: IO () 
main = do
  userStrand <- getUserInputStrand
  let instructionList = generateInstructionList userStrand
  putStrLn "Your list of Instructions is: "
  mapM_ printMaybeList instructionList
  let foldingPattern = generateFoldingList instructionList
  putStrLn "Your folding pattern is: "
  mapM_ printMaybeList foldingPattern

