module Types where 

-- cannot define subtypes that classify A and G as purines (same for pyramidines)
-- Prefer simple runtime pattern matching as opposed to created sum type with additional boilerplate constructors 

data Base 
  = A
  | G
  | T 
  | C
  deriving(Show,Enum,Bounded)

type Strand = [Base]

-- a data type to represent the game state: 
-- this feels universal investigate further
data Game = Game { mainStrand :: Strand 
                 , complementaryStrand :: Strand 
                 , instructions :: [Instruction]
                 , foldingPattern :: [FoldingDirection]
                 , boundPosition :: Integer 
                 , currentlyBoundStrand :: Bool -- correct way to do this? True = mainStrand, False = complementary
                 } deriving (Show) 

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
 deriving(Show)

data FoldingDirection 
  = Straight 
  | Right 
  | Left 
  deriving(Show)