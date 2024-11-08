#include "enzymefunctions.c"



int validstrand(char[]); 
const char *determinefoldingpattern(char[]);


struct user_strand {
  char dna_strand[STRAND_SIZE]; 
  char folding_pattern[STRAND_SIZE]; 
  char starting_offset[STRAND_SIZE];  
};
