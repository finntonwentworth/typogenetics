#include <stdio.h>
#include <string.h>


#define MAX_STRAND_SIZE     1000

struct decodedstrand {
    int  instruction[MAX_STRAND_SIZE];
    char instructiontext[3*MAX_STRAND_SIZE];
    char foldingpattern[MAX_STRAND_SIZE];
    int  foldingpatternsize; 
    int  enzymecount = 1; 
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

struct decodedstrand get_instructions_and_folding(char strand[], int size) {
    struct decodedstrand decode; 
    int i = 0, k = 0, j = 0; 
    
    char firstbase,secondbase; 
    //while the index is less than or equal to the number of relevant elements in userstrand
    while(i <= size){
        // set two placeholder char to the bases of index i and index i + 1
        firstbase  = strand[i]; 
        secondbase = strand[i+1]; 
        

    // nested switch checks pair and determines corresponding instruction
    switch (firstbase) {
      case 'A':
        switch(secondbase){
          case 'A':
            decode.instructiontext[j]   = 'p';
            decode.instructiontext[j+1] = 'u';
            decode.instructiontext[j+2] = 'n';
            decode.instruction[k] = 0; 
            // inform that there is more than one enzyme
            decode.enzymecount++; 
            //insert dash into folding pattern to tell that this strand encodes for 2 (or more enzymes)
            decode.foldingpattern[k] = '-';
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
    //size of folding pattern will be k-1 relevant elements 
    decode.foldingpatternsize = k-1; 
    
    // return the instructions and folding pattern
    return decode;
}

/* ------ FUNCTION ------*/ 
/*
 * Function takes in folding pattern and returns preferred base for enzyme to bind to
 *
 * Accepts:  
 * Decoded folding pattern, 
 * Returns: 
 * char base of binding preference 
 * 
 * TO DO: Make this function write graphics/ display the folding happening 
 * or maybe that should be the role of another function
 *
*/
char calculate_starting_base(char foldingpattern[], int foldingpatternsize) {
    // first element is known to be 'r'
    int i = 1;
    // absolute orientation represented by angle theta, 
    int theta = 0;
    // char to store returned starting base 
    char startingbase;  
    // for each relevant element in the folding pattern
    while(i < foldingpatternsize) {

      switch(foldingpattern[i]){
        case 's':
        //maintain heading, i.e. do not change angle
           theta = theta;
           break;
        case 'r':
        //perform a CW rotation of 90 degrees    
           theta = theta - 90;  
           break;
        case 'l':
        //perform a CCW rotation of 90 degrees    
           theta = theta + 90;  
           break;
        default: 
           break;
       }
       i++; 
    }
    // after the while loop, theta will be some multiple of 90 degrees
    // shake off the extra roations 
    theta = theta % 360; 
    // why does it feel like there's a better way to do this 
    if(theta == 0) {
        startingbase = 'A'; 
    }else if (theta == 90 || theta == -270){
        startingbase = 'C'; 
    }else if(theta == 180 || theta == -180) {
        startingbase = 'T'; 
    }else if (theta == -90 || theta == 270){
        startingbase = 'G'; 
    }

    return startingbase;
}


/* ------ FUNCTION ------*/ 
/*
 * Function presents choice of starting base to bind to (and allows random selection?)
 *
 * Accepts:  
 * User dna strand,# of relevant elements, Starting base from folding pattern
 * Returns: 
 * Array containing the sequential element numbers of bases from user strand to begin executing enzyme instructions on 
 * 
*/

int *matching_starting_base_elements(char strand[],int size, char startingbase){
   int i = 0;
   int j = 0; 
   static int matchingbaseelements[MAX_STRAND_SIZE];
   //int *startingbasepositions = matchingbaseelements;
   //increment through relevant elements of userstrand
   while(i <= size){
     // if the userstrand element matches the calculated starting base  
     if(strand[i] == startingbase){
         //set an element of matchingbaseelements to the index of the matching base
           matchingbaseelements[j] = i;
           j++;
       } 
     i++;
   } 
   matchingbaseelements[j] = '\0'; 
   return matchingbaseelements; 
}

/* ------ FUNCTION ------*/ 
/*
 * Function places arrow marking current position under string 
 *
 * Accepts:  
 * int representing starting base position/ current acting position
 * Returns: 
 * Array containing # of spaces and arrow to graphically mark position
 *
 * 
*/
char *current_enzyme_position(int startingbaseposition){
   static char arrowmarker[MAX_STRAND_SIZE];  
   int i = 0; 
   while(i < startingbaseposition-1){
       arrowmarker[i] = ' '; 
       i++;
   }
   arrowmarker[i] = '^'; 
   return arrowmarker; 
}

/* ------ FUNCTION ------*/ 
/*
 * Function serves to call any of the "15" enzyme functions provided an instruction number 
 *
 * Accepts:  
 * int instruction number   
 * Returns: 
 * pointer to call function? i think that is how it works  
 * 
*/
// i think this is supposed to accept a pointer to a function
void call_instruction(int instructionnumber) {

}