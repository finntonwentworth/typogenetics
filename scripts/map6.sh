#!/bin/bash


counter=0

while [[ $counter -lt 63 ]]
do 
  ../data/io -s $counter -Sf >> log_map_6.txt
  let ++counter
done

