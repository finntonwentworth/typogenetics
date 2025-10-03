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

del :: Int -> Strand -> Strand 
del index strand = take index strand ++ [' '] ++ drop index strand

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
-- Take a strand, insert a base and return new, modified strand
-- interestingly does not error if index > length of strand 
ina :: Int -> String -> String
ina index strand = take index strand ++ ['A'] ++ drop index strand

inc :: Int -> String -> String
inc index strand = take index strand ++ ['C'] ++ drop index strand

ing :: Int -> String -> String
ing index strand = take index strand ++ ['G'] ++ drop index strand

int :: Int -> String -> String
int index strand = take index strand ++ ['T'] ++ drop index strand

rpy :: a
rpy = undefined

rpu :: a
rpu = undefined

lpy :: a
lpy = undefined

lpu :: a
lpu = undefined