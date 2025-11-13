module Types where 


data Base 
  = A
  | G
  | T 
  | C
  | Blank
  deriving(Show, Enum, Bounded, Eq)

type Strand = [Base]
type BoundPosition = Int
--type Enzyme = [Instruction] 

data BoundStrand 
  = Upper 
  | Lower 
  deriving(Show, Eq)


data Output = Output { o_mainStrand :: Strand
                     , o_complementStrand :: Strand
                     , o_outputStrands :: [Strand]
                     }

data Instruction 
 = Pun
 | Cut
 | Del
 | Swi
 | Mvr
 | Mvl
 | Cop
 | Off
 | Ina
 | Inc
 | Ing
 | Int
 | Rpy
 | Rpu
 | Lpy
 | Lpu
 deriving(Show, Eq)

data FoldingDirection 
  = Straight 
  | Right 
  | Left 
  deriving(Show)