#!/bin/bash

i=0

while [[ $i -lt $1 ]]
do
    ../src/a.out -r $2 -Sr >> log.txt
    let ++i
done

