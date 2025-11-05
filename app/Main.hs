module Main where 

import Instructions
import Utils

main :: IO () 
main = undefined

test = do 
  strand <- randStrand 10 
  putStrLn ("Strand: " ++ show strand) 
  putStrLn ("Instructions: " ++ show (strandToInstructions strand)) 
  putStrLn ("Starting Base: " ++ show (startingBase $ strandToInstructions strand)) 
