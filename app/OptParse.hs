module OptParse 
  (Options(..)
  )
  where 

--import Options.Applicative 

{-

ARGS: 
--strand <String> [-s <String>] 
User inputted strand 

--random <Int> [-r <Int>] 
Generate a random strand with <Int> elements

-}
-- Data type for command line options 
data Options 
  = UserStrand String
  | RandomStrand Int 
  | Help
  deriving Show


printHelp :: IO ()
printHelp  = putStrLn "Usage: typogenetics [-s] OR [-r <Int>]."

