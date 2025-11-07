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

data BoundStrand 
  = Upper 
  | Lower 
  deriving(Show, Eq)

-- a data type to represent the game state: 
-- this feels universal investigate further
data Game = Game { mainStrand :: Strand 
                 , complementaryStrand :: Strand 
                 -- maybe this should be [[Instruction]]
                 -- So when a Pun is there, it splits the instruction to the next list
                 -- then a game could just execute all items in [[Instructions]]
                 , instructions :: [Instruction] 
                 , foldingPattern :: [FoldingDirection]
                 , boundPosition :: BoundPosition
                 , currentlyBoundStrand :: BoundStrand
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