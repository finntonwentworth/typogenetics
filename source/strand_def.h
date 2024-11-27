#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRAND_SIZE         1000

/*--- Macros for printing Upsidedown bases ---*/
#define UPSIDEDOWN_A    "\u2c6f"
#define UPSIDEDOWN_T    "\ua7b1"
#define UPSIDEDOWN_G    "\u2141"
#define UPSIDEDOWN_C    "\u2183"

/*--- Header Guard --- */
#ifndef STRAND_DEF
#define STRAND_DEF

/* ----- STRAND ----- */
/*
 * Strands are represented as structs which hold useful metadata about the strand
 *
 * mainStrand: holds the currently acted upon strand 
 * complementaryStrand: array to hold copied elements 
 * size: # of relevant elements in the strand for loops 
 * currentBoundPosition: int representing what element the enzyme is bound to 
 * outputStrandCount: Counter for printing the end strands if they are subdivided/ copied 
 * ouputStrand: 2-D array holding the input, active, and all remaining generated strands 
 */
struct strand {
  char mainStrand[MAX_STRAND_SIZE]; 
  char complementaryStrand[MAX_STRAND_SIZE];
  int  boundStrandFlag; //0 = mainStrand ; 1 = complementaryStrand
  int  mainSize; 
  int  complementarySize;
  int  currentBoundPosition; 
  int  outputStrandCount;
  char outputStrand[MAX_STRAND_SIZE/2][MAX_STRAND_SIZE/2]; 
};

/* -----DECODED STRAND ----- */
/*
 * "Decoded" strands hold all the information about the instructions, folding pattern, and # of enzymes 
 *
 * instruction: array of instructions numbers that are fed into call_instruction 
 * instructionText: array of instruction 3 letter op-codes 
 * instructionTextSize: int of size of relevant text elements 
 * foldingPattern: char array of folding directions determined from enzyme instructions 
 * foldingPatternSize: int size of # of relevant elements 
 * enzymeCount: # of enzymes encoded for by the strand, = # of genes 
 */
struct decodedStrand {
    int  instruction[MAX_STRAND_SIZE];
    char instructionText[3*MAX_STRAND_SIZE];
    int  instructionTextSize; 
    char foldingPattern[MAX_STRAND_SIZE];
    int  foldingPatternSize; 
    int  enzymeCount; 
};

#endif /*STRAND_DEF*/
