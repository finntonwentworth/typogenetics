#include "strand_def.h"



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
    while(strand[elementcounter] !='\0') {
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
    while(i<= size) {
       // If the string only contains A, G, T, C or the terminating character: 
       if(strand[i] == 'A' || strand[i] == 'C' || strand[i] == 'G' || strand[i] == 'T' || strand[i] == '\0') {
         i++;
         } else {
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
 * decodedStrand struct 
*/

struct decodedStrand get_instructions_and_folding(char strand[], int size) {
    struct decodedStrand decode = {.enzymeCount = 1}; 
    int i = 0, k = 0, j = 0; 
     
    char firstbase,secondbase; 
    //while the index is less than or equal to the number of relevant elements in userstrand
    while(i <= size) {
        // set two placeholder char to the bases of index i and index i + 1
        firstbase  = strand[i]; 
        secondbase = strand[i+1]; 
        

    // nested switch checks pair and determines corresponding instruction
    switch (firstbase) {
      case 'A':
        switch(secondbase) {
          case 'A':
            decode.instructionText[j]   = 'p';
            decode.instructionText[j+1] = 'u';
            decode.instructionText[j+2] = 'n';
            decode.instruction[k] = 0; 
            // inform that there is more than one enzyme encoded by this strand
            decode.enzymeCount++; 
            //insert dash into folding pattern 
            decode.foldingPattern[k] = '-';
            break;
          case 'C':
            decode.instructionText[j]   = 'c';
            decode.instructionText[j+1] = 'u';
            decode.instructionText[j+2] = 't';
            decode.instruction[k] = 1; 
            decode.foldingPattern[k] = 's'; 
            break;
          case 'G':
            decode.instructionText[j]   = 'd';
            decode.instructionText[j+1] = 'e';
            decode.instructionText[j+2] = 'l';
            decode.instruction[k] = 2; 
            decode.foldingPattern[k] = 's'; 
            break;
          case 'T':
            decode.instructionText[j]   = 's';
            decode.instructionText[j+1] = 'w';
            decode.instructionText[j+2] = 'i';
            decode.instruction[k] = 3; 
            decode.foldingPattern[k] = 'r'; 
            break;
        //if the default case is reached, 
        //then secondbase must be the null character
        //so set the last element foldingPattern to the null character
          default:
            decode.foldingPattern[k] = '\0';
            break;
        }
        break;
      case 'C':
        switch(secondbase) {
          case 'A':
            decode.instructionText[j]   = 'm';
            decode.instructionText[j+1] = 'v';
            decode.instructionText[j+2] = 'r';
            decode.instruction[k] = 4; 
            decode.foldingPattern[k] = 's'; 
            break;
          case 'C':
            decode.instructionText[j]   = 'm';
            decode.instructionText[j+1] = 'v';
            decode.instructionText[j+2] = 'l';
            decode.instruction[k] = 5; 
            decode.foldingPattern[k] = 's'; 
            break;
          case 'G':
            decode.instructionText[j]   = 'c';
            decode.instructionText[j+1] = 'o';
            decode.instructionText[j+2] = 'p';
            decode.instruction[k] = 6; 
            decode.foldingPattern[k] = 'r'; 
            break;
          case 'T':
            decode.instructionText[j]   = 'o';
            decode.instructionText[j+1] = 'f';
            decode.instructionText[j+2] = 'f';
            decode.instruction[k] = 7; 
            decode.foldingPattern[k] = 'l'; 
            break;
          default:
            decode.foldingPattern[k] = '\0';
            break;
        }
      break;
      case 'G':
        switch(secondbase) {
          case 'A':
            decode.instructionText[j]   = 'i';
            decode.instructionText[j+1] = 'n';
            decode.instructionText[j+2] = 'a';
            decode.instruction[k] = 8; 
            decode.foldingPattern[k] = 's'; 
            break;
          case 'C':
            decode.instructionText[j]   = 'i';
            decode.instructionText[j+1] = 'n';
            decode.instructionText[j+2] = 'c';
            decode.instruction[k] = 9; 
            decode.foldingPattern[k] = 'r'; 
            break;
          case 'G':
            decode.instructionText[j]   = 'i';
            decode.instructionText[j+1] = 'n';
            decode.instructionText[j+2] = 'g';
            decode.instruction[k] = 10; 
            decode.foldingPattern[k] = 'r'; 
            break;
          case 'T':
            decode.instructionText[j]   = 'i';
            decode.instructionText[j+1] = 'n';
            decode.instructionText[j+2] = 't';
            decode.instruction[k] = 11; 
            decode.foldingPattern[k] = 'l'; 
            break;
          default:
            decode.foldingPattern[k] = '\0';
            break;
        }
      break;
      case 'T':
        switch(secondbase) {
          case 'A':
            decode.instructionText[j]   = 'r';
            decode.instructionText[j+1] = 'p';
            decode.instructionText[j+2] = 'y';
            decode.instruction[k] = 12; 
            decode.foldingPattern[k] = 'r'; 
            break;
          case 'C':
            decode.instructionText[j]   = 'r';
            decode.instructionText[j+1] = 'p';
            decode.instructionText[j+2] = 'u';
            decode.instruction[k] = 13;
            decode.foldingPattern[k] = 'l'; 
            break;
          case 'G':
            decode.instructionText[j]   = 'l';
            decode.instructionText[j+1] = 'p';
            decode.instructionText[j+2] = 'y';
            decode.instruction[k] = 14;
            decode.foldingPattern[k] = 'l'; 
            break;
          case 'T':
            decode.instructionText[j]   = 'l';
            decode.instructionText[j+1] = 'p';
            decode.instructionText[j+2] = 'u';
            decode.instruction[k] = 15;
            decode.foldingPattern[k] = 'l'; 
            break;
          default:
            decode.foldingPattern[k] = '\0';
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
    decode.instructionTextSize = j - 3; 
    
    //size of folding pattern will be k-1 relevant elements 
    decode.foldingPatternSize = k-1; 
    

    //Actually, the first element is r if the first instruction is not pun 
    if(decode.foldingPattern[0] != '-') {
        decode.foldingPattern[0] = 'r';
    }

    //if the last element is '-', then subtract off the extra enzyme count we added on 
    if(decode.foldingPattern[decode.foldingPatternSize-1] == '-') {
        decode.enzymeCount--; 
    }

  //write 'r' to the next non pun folding direction after pun instructions 
  //as long as it is not the last element of the the folding pattern
    for(int i = 0; i <= decode.foldingPatternSize; i++) {
        if(decode.foldingPattern[i] != '-' && decode.foldingPattern[i-1] == '-' && i != decode.foldingPatternSize) {
            decode.foldingPattern[i] = 'r';
        }
    } 
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
char calculate_starting_base(char foldingPattern[], int startpoint, int endpoint) {
    // absolute orientation represented by angle theta, 
    int theta = 0;
    // char to store returned starting base 
    char startingbase;  
    
    // if the folding pattern consists of just pun 
    if(foldingPattern[startpoint] == '-') {
        return '-';
    } else {
        
    // first element is known to be 'r' (if it's not '-')
        startpoint++;

    // for each relevant element in the folding pattern
        while(startpoint < endpoint) {

          switch(foldingPattern[startpoint]) {
            case 's':
            //maintain heading, i.e. do not change angle
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
           startpoint++; 
        }
        // after the while loop, theta will be some multiple of 90 degrees
        // shake off the extra roations 
        theta = theta % 360; 
        // why does it feel like there's a better way to do this 
        if(theta == 0) {
            startingbase = 'A'; 
        } else if(theta == 90 || theta == -270) {
            startingbase = 'C'; 
        } else if(theta == 180 || theta == -180) {
            startingbase = 'T'; 
        } else if(theta == -90 || theta == 270) {
            startingbase = 'G'; 
        } else {
            startingbase = '\0'; 
        }

        return startingbase;
    }
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

int *matching_starting_base_elements(char strand[],int size, char startingbase) {
   int i = 0;
   int j = 0; 
   static int matchingbaseelements[MAX_STRAND_SIZE];
   //increment through relevant elements of userstrand
   while(i <= size) {
     // if the userstrand element matches the calculated starting base  
     if(strand[i] == startingbase) {
         //set an element of matchingbaseelements to the index of the matching base
           matchingbaseelements[j] = i;
           j++;
       } 
     i++;
   } 
   //use -1 to mark terminating character 
   matchingbaseelements[j] = -1; 
   return matchingbaseelements; 
}

/* ------ FUNCTION ------*/ 
/*
 * Function places arrow marking current position under/over string 
 *
 * Accepts:  
 * strand pointer , int marking that we are printing above the string or below the string
 * 0 = above strands
 * 1 = below strands
 * Returns: 
 * pointer to  2-D Array containing # of spaces and arrow to graphically mark position
 *
 * THIS SHOULD PROBABLY BE REVISED I WAS STRUGGLING WITH RETURNING A 2-D ARRAY  
*/
char *current_enzyme_position(struct strand *strandPointer, int printingPosition) {
   static char arr[MAX_STRAND_SIZE];  
   //clear the array - put spaces in each spot in the array 
   for(int i = 0; i<=strandPointer->mainSize; i++) {
       arr[i] = ' '; 
   }
   for(int i = 0; i<=strandPointer->complementarySize; i++) {
       arr[i] = ' '; 
   }
   //if you're on the main strand and you're printing below the strand
   if(strandPointer->boundStrandFlag == 0 && printingPosition == 1) {
       //draw the upwards arrow
       arr[strandPointer->currentBoundPosition-1] = '^'; 
       return arr; 
   } else if(strandPointer->boundStrandFlag && printingPosition == 0) {
   //if the bound strand flag is set to the complementary draw a down arrow
       arr[strandPointer->currentBoundPosition-1] = 'V'; 
       return arr; 
   } else {
       return arr;
   }

}
/* ------ FUNCTION ------*/ 
/*
 * Function prints the upsidedown version of the complementary strand
 *
 * Accepts:  
 * int representing size of strand, char array of rightside up complementary strand elements
 * Returns: 
 * nothing 
 * 
*/

void print_complementary_strand(int length, char complementaryStrand[]) {
   for(int i = 0; i <= length; i++) {
      switch (complementaryStrand[i]) {
          case 'A':
              printf(UPSIDEDOWN_A);
              break;
          case 'C':
              printf(UPSIDEDOWN_C);
              break;
          case 'T':
              printf(UPSIDEDOWN_T);
              break;
          case 'G':
              printf(UPSIDEDOWN_G);
              break;
          default:
              printf(" ");
              break;
      }
   } 
}
/* ------ FUNCTION ------*/ 
/*
 * Function splits strands with spaces into multiple outputs 
 * this has got to go through each output array looking for spaces in strands
 * if it finds one, it writes the rest of the strand to another output strand
 * overwrites output strand value in struct 
 * Accepts:  
 * strandPointer struct pointer
 * Returns: 
 * nothing 
 * 
*/
void strand_splitter(struct strand *strandPointer) {
    //search for space delimiter in the main strand
   int i = 1;
   int j = 0;
   int firstStrandFlag = 1;
   char *token; 
   while(i <= strandPointer->outputStrandCount) {
       token = strtok(strandPointer->outputStrand[i], " ");
       while(token != NULL) {
           if(firstStrandFlag == 1) {
               firstStrandFlag = 0;
               token = strtok(NULL, " ");
           } else {
               strcpy(strandPointer->outputStrand[1+strandPointer->outputStrandCount+j],token);
               j++;
               token = strtok(NULL, " ");
          }
       }
        firstStrandFlag = 1;
        i++;
    }

   //now that I've cleared out the spaced strands, remove any spaces from the first and second strand
   token = strtok(strandPointer->outputStrand[1], " "); 
   if(token != NULL){
       strcpy(strandPointer->outputStrand[1],token);
   }

   token = strtok(strandPointer->outputStrand[2], " "); 
   if(token != NULL){
       strcpy(strandPointer->outputStrand[2],token);
   }
   
   //add the number of strands we added to the ouput count
   strandPointer->outputStrandCount = strandPointer->outputStrandCount + j + 1;
}

/* ------ FUNCTION ------*/ 
/*
 * Function checks if the enzyme is still bound to an element of a strand
 *
 * Accepts:  
 * strandPointer struct pointer
 * Returns: 
 * 1 if the strand is no longer bound 
 * 0 if it is  
 * 
*/

int check_falling_off(struct strand *strandPointer) {

    switch (strandPointer->boundStrandFlag) {
        case 0:
            if(strandPointer->mainStrand[strandPointer->currentBoundPosition-1] !='A' && strandPointer->mainStrand[strandPointer->currentBoundPosition-1] != 'G' && strandPointer->mainStrand[strandPointer->currentBoundPosition-1] != 'T' && strandPointer->mainStrand[strandPointer->currentBoundPosition-1] != 'C') {
                return 1; 
            } else {
                return 0; 
            }
            break;
        case 1:
            if(strandPointer->complementaryStrand[strandPointer->currentBoundPosition-1] !='A' && strandPointer->complementaryStrand[strandPointer->currentBoundPosition-1] != 'G' && strandPointer->complementaryStrand[strandPointer->currentBoundPosition-1] != 'T' && strandPointer->complementaryStrand[strandPointer->currentBoundPosition-1] != 'C') {
                return 1; 
            } else {
                return 0; 
            }
            break;
        default:
            break;
    }

    //ERROR - if no conditions match
    fprintf(stderr,"function 'check_falling_off' returned ERROR\n");
    return -5; 
}

void wait_for_user(void) {
  char enter;
  printf("Press Enter to continue: \n");
  scanf("%c", &enter);
}

/* ------ FUNCTION ------*/ 
/*
 *
 *
 * Accepts:  
 * 
 * Returns: 
 * 
 *
 * 
*/
//struct strand init_user_strand(struct strand userStrand) {
struct strand init_user_strand(char userMainStrand[], int outputStrandCount) {
  struct strand newBlankStrand = {
                               .complementaryStrand = { ' ' },
                               .outputStrandCount = 2,
                               .boundStrandFlag = 0,
                               .copyModeFlag = 0,
                                 };
  strcpy(newBlankStrand.mainStrand, userMainStrand);
  for(int i = 0; i < MAX_STRAND_SIZE; i++){
    newBlankStrand.complementaryStrand[i] = ' ';
    for(int j = 0; j < outputStrandCount; j ++) {
      newBlankStrand.outputStrand[j][i] = ' ';
    }
  }
  
  return newBlankStrand;
}

/* ------ FUNCTION ------*/ 
/*
 *
 *
 * Accepts:  
 * 
 * Returns: 
 * 
 *
 * 
*/
struct decodedStrand init_decoded_strand(void) {

  struct decodedStrand newDecodedStrand = {
                                            .instruction = {0},
                                            .instructionText = {' '},
                                            .instructionTextSize = 0,
                                            .foldingPattern = {' '},
                                            .foldingPatternSize = 0, 
                                            .enzymeCount = 0, 
                                          };

  for(int i = 0; i < 3*MAX_STRAND_SIZE; i++){
    newDecodedStrand.instructionText[i] = '=';
  }
  for(int i = 0; i < MAX_STRAND_SIZE; i++){
    newDecodedStrand.instruction[i] = -1; 
    newDecodedStrand.foldingPattern[i] = ' ';
  }
  return newDecodedStrand;
}
