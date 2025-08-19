module Strands 
  (
     Strand
    ,Base
  )
  where 


type Strand = String 
type Base   = Char 

{-
data DebugUserStrand 
  = Strand String 
  | Instructions [Maybe Instruction]
  | FoldingPattern [Maybe FoldingDirection]
  deriving(Show)
-}
