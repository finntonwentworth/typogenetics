module Main where 

-- import OptParse
import Strands
import Instructions




main :: IO () 
main = do
  userStrand <- getUserInputStrand
  putStrLn "This is just a test message" 

