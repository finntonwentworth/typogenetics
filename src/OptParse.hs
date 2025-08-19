module OptParse
  ( 
    Options(..)
  )
  where 

--import Control.Applicative 

data Options 
  = UserStrand String 
  | RandomStrand Integer

