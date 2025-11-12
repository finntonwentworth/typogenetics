module Types where 

-- cannot define subtypes that classify A and G as purines (same for pyramidines)
-- Prefer simple runtime pattern matching as opposed to created sum type with additional boilerplate constructors 

-- this should probably include a blank as an element?
data Base 
  = A
  | G
  | T 
  | C
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