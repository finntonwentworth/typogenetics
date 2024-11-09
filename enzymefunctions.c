
#include <stdio.h>
#include <string.h>


#define MAX_STRAND_SIZE     1000

struct decodedstrand {
    int  instruction[MAX_STRAND_SIZE];
    char instructiontext[3*MAX_STRAND_SIZE];
    char foldingpattern[MAX_STRAND_SIZE];
};

/* ------ FUNCTION ------*/ 
/*
 * Counts the number of User inputed elements  
 *
 * Accepts: User String 
 * Returns: 
 * Integer value of # of user inputed elements
*/
int relevant_elements(char strand[]) {
    int elementcounter = 0; 
    while(strand[elementcounter] !='\0'){
        elementcounter++;
    };
    return elementcounter; 
}
/* ------ FUNCTION ------*/ 
/*
 * checks that the user input consists only of A, G, T, C, or the null character
 *
 * Accepts: User String, Length of user string's relevant elements
 * Returns: 
 * 1 if valid 
 * otherwise 0 
*/
int valid_strand(char strand[], int size) {
    int i = 0;
    while(i<= size){
       // If the string only contains A, G, T, C or the terminating character: 
       if(strand[i] == 'A' || strand[i] == 'C' || strand[i] == 'G' || strand[i] == 'T' || strand[i] == '\0'){
         i++;
         }else{
            return 0;
         } 
    }
    return 1;
}



// Determine base pairs for corresponding instruction, then determine folding structure to determine the starting base 
//store the instructions for the enzymes of the strand so that they can be referenced later

/* ------ FUNCTION ------*/ 
/*
 * 'Decodes' the user's string, and returns a struct with elements: 
 *          - Char Array of Text instructions in order  
 *          - Int array of Numerical instructions in order 
 *          - Char array of direction of folding pattern in order
 *
 * Accepts: User String, Length of user string's relevant elements  
 * Returns: 
 * decodedstrand struct 
*/

// This function will read through the user's strand and return two arrays as elements of a struct:
// the instructions 
// and the folding pattern 
//
struct decodedstrand determine_folding(char strand[], int size) {
    struct decodedstrand decode; 
    int i = 0, k = 0, j = 0; 
    
    char firstbase,secondbase; 
    //while the strand element is not the terminating character
    while(i <= size){
        firstbase  = strand[i]; 
        secondbase = strand[i+1]; 
        

    // print base pair 
    // nested switch checks pair and determines corresponding instruction
    switch (firstbase) {
      case 'A':
        switch(secondbase){
          case 'A':
            decode.instructiontext[j]   = 'p';
            decode.instructiontext[j+1] = 'u';
            decode.instructiontext[j+2] = 'n';
            decode.instruction[k] = 0; 
            decode.foldingpattern[k] = ' ';
            break;
          case 'C':
            decode.instructiontext[j]   = 'c';
            decode.instructiontext[j+1] = 'u';
            decode.instructiontext[j+2] = 't';
            decode.instruction[k] = 1; 
            decode.foldingpattern[k] = 's'; 
            break;
          case 'G':
            decode.instructiontext[j]   = 'd';
            decode.instructiontext[j+1] = 'e';
            decode.instructiontext[j+2] = 'l';
            decode.instruction[k] = 2; 
            decode.foldingpattern[k] = 's'; 
            break;
          case 'T':
            decode.instructiontext[j]   = 's';
            decode.instructiontext[j+1] = 'w';
            decode.instructiontext[j+2] = 'i';
            decode.instruction[k] = 3; 
            decode.foldingpattern[k] = 'r'; 
            break;
        //if the default case is reached, 
        //then secondbase must be the null character
        //so set the last element foldingpattern to the null character
          default:
            decode.foldingpattern[k] = '\0';
            break;
        }
        break;
      case 'C':
        switch(secondbase){
          case 'A':
            decode.instructiontext[j]   = 'm';
            decode.instructiontext[j+1] = 'v';
            decode.instructiontext[j+2] = 'r';
            decode.instruction[k] = 4; 
            decode.foldingpattern[k] = 's'; 
            break;
          case 'C':
            decode.instructiontext[j]   = 'm';
            decode.instructiontext[j+1] = 'v';
            decode.instructiontext[j+2] = 'l';
            decode.instruction[k] = 5; 
            decode.foldingpattern[k] = 's'; 
            break;
          case 'G':
            decode.instructiontext[j]   = 'c';
            decode.instructiontext[j+1] = 'o';
            decode.instructiontext[j+2] = 'p';
            decode.instruction[k] = 6; 
            decode.foldingpattern[k] = 'r'; 
            break;
          case 'T':
            decode.instructiontext[j]   = 'o';
            decode.instructiontext[j+1] = 'f';
            decode.instructiontext[j+2] = 'f';
            decode.instruction[k] = 7; 
            decode.foldingpattern[k] = 'l'; 
            break;
          default:
            decode.foldingpattern[k] = '\0';
            break;
        }
      break;
      case 'G':
        switch(secondbase){
          case 'A':
            decode.instructiontext[j]   = 'i';
            decode.instructiontext[j+1] = 'n';
            decode.instructiontext[j+2] = 'a';
            decode.instruction[k] = 8; 
            decode.foldingpattern[k] = 's'; 
            break;
          case 'C':
            decode.instructiontext[j]   = 'i';
            decode.instructiontext[j+1] = 'n';
            decode.instructiontext[j+2] = 'c';
            decode.instruction[k] = 9; 
            decode.foldingpattern[k] = 'r'; 
            break;
          case 'G':
            decode.instructiontext[j]   = 'i';
            decode.instructiontext[j+1] = 'n';
            decode.instructiontext[j+2] = 'g';
            decode.instruction[k] = 10; 
            decode.foldingpattern[k] = 'r'; 
            break;
          case 'T':
            decode.instructiontext[j]   = 'i';
            decode.instructiontext[j+1] = 'n';
            decode.instructiontext[j+2] = 't';
            decode.instruction[k] = 11; 
            decode.foldingpattern[k] = 'l'; 
            break;
          default:
            decode.foldingpattern[k] = '\0';
            break;
        }
      break;
      case 'T':
        switch(secondbase){
          case 'A':
            decode.instructiontext[j]   = 'r';
            decode.instructiontext[j+1] = 'p';
            decode.instructiontext[j+2] = 'y';
            decode.instruction[k] = 12; 
            decode.foldingpattern[k] = 'r'; 
            break;
          case 'C':
            decode.instructiontext[j]   = 'r';
            decode.instructiontext[j+1] = 'p';
            decode.instructiontext[j+2] = 'u';
            decode.instruction[k] = 13;
            decode.foldingpattern[k] = 'l'; 
            break;
          case 'G':
            decode.instructiontext[j]   = 'l';
            decode.instructiontext[j+1] = 'p';
            decode.instructiontext[j+2] = 'y';
            decode.instruction[k] = 14;
            decode.foldingpattern[k] = 'l'; 
            break;
          case 'T':
            decode.instructiontext[j]   = 'l';
            decode.instructiontext[j+1] = 'p';
            decode.instructiontext[j+2] = 'u';
            decode.instruction[k] = 15;
            decode.foldingpattern[k] = 'l'; 
            break;
          default:
            decode.foldingpattern[k] = '\0';
            break;
        }
        break;
    }
    //move to next pair of bases in strand 
    i = i +2;
    // move to the next instruction
    j = j + 3; 
    // move to the next instruction number and folding element 
    k++; 

    
    } // end of 'while'
    //Actually, the first element is r 
    decode.foldingpattern[0] = 'r';
    // and append terminating character to folding pattern
    decode.foldingpattern[k] = '\0';
    // return the instructions and folding pattern
    return decode;
}

// FUNCTION PURPOSE 
// determine the starting acting point of the enzyme on the strand and place the
// a ^ where the start is 
/*
char calculate_start(char strand[]) {
}

const char* determinefolding(char strand[1000]) {
*/
