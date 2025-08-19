module Instructions 
  (
     Instruction (..)
    ,FoldingDirection (..)
    ,pun
    ,cut
    ,del
    ,swi
    ,mvr
    ,mvl
    ,cop
    ,off
    ,ina
    ,inc
    ,ing
    ,int
    ,rpy
    ,rpu
    ,lpy
    ,lpu
  ) 
  where

import Strands

-- Data type for constructing a list of instructions 
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

-- Data type for creating the folding pattern list 
data FoldingDirection
  = Straight 
  | Right 
  | Left 
 deriving(Show)

pun :: a
pun = undefined 

cut :: a
cut = undefined

del :: a
del = undefined

swi :: a
swi = undefined

mvr :: a
mvr = undefined

mvl :: a
mvl = undefined

cop :: a
cop = undefined

off :: a
off = undefined

-- FUNCTION 
-- Take a strand, insert a character and return a strand
ina :: Base -> Int -> String -> String
ina base index strand = undefined 


inc :: a
inc = undefined

ing :: a
ing = undefined

int :: a
int = undefined

rpy :: a
rpy = undefined

rpu :: a
rpu = undefined

lpy :: a
lpy = undefined

lpu :: a
lpu = undefined