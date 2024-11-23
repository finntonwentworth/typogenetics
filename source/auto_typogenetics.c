
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "enzymefunctions.h"


/* PARAMETERS LIST
 *
 * MANDATORY: 
 * -s (--strand)  <char strand[]> 
 *     Use inputted strand[] as input 
 *
 * OR 
 *
 * -r (--random)  <int> 
 *      Generate a random strand with <int> bases (int - 1 elements)
 *
 * OPTIONAL 
 * -S 
 *      randomly pick starting base for each enzyme 
 *
 * -f (--first-matching) 
 *      enzymes will select the first matching element to their base binding preference. 
 *
 * (an idea, but won't work if the output is multiple strands/ needs a way to pick one)
 * -i <int> 
 *      <int> # of interations
 *
 */ 

int main(int argC, char **argV) {

  int opt,randSelectFlag,firstSelectFlag; 
  int i, startingBaseIndex  = 0; 
  char *userInput;   
  //struct stores user entered strand and it's size  
  struct strand userStrand = {.outputStrandCount = 1};  
  // struct stores decoded information about the strand
  struct decodedStrand userDecode;

  while((opt = getopt(argC, argV, "hs:r:S:")) != -1){
      switch(opt){
          case 'h':
              printf("* PARAMETERS LIST                                                                      \n");
              printf("*                                                                                      \n");
              printf("* MANDATORY:                                                                           \n"); 
              printf("* -s (--strand)  <char strand[]>                                                       \n");
              printf("*     Use inputted strand[] as input                                                   \n");
              printf("*                                                                                      \n");
              printf("* OR                                                                                   \n");
              printf("*                                                                                      \n");
              printf("* -r (--random)  <int>                                                                 \n");
              printf("*      Generate a random strand with <int> bases (int - 1 elements)                    \n");
              printf("*                                                                                      \n");
              printf("* OPTIONAL                                                                             \n"); 
              printf("* -S                                                                                   \n");
              printf("*      randomly pick starting base for each enzyme                                     \n");
              printf("*                                                                                      \n");
              printf("* -f (--first-matching)                                                                \n");
              printf("*      enzymes will select the first matching element to their base binding preference.\n");
              printf("*\n");
              return 1;  
          case 's':
            // if -s was passed char array set userStrand.dnaStrand to it's value 
            userInput = optarg;
            strcpy(userStrand.dnaStrand, userInput); 
            break;
          case 'r':
            userInput = rand_strand(atoi(optarg)); 
            strcpy(userStrand.dnaStrand, userInput); 
            break;
          case 'S':
            userInput = optarg;
            if(strcmp(userInput, "f") == 0){
                firstSelectFlag = 1; 
            }else if(strcmp(userInput, "r") == 0){
                randSelectFlag = 1;
                srand(time(0));
            }else{
                fprintf(stderr, "Invalid argument passed to -S\n");
                return -1;
            }
            break;
          case '?': 
            if(optopt == 's' || optopt == 'r' || optopt == 'S'){
              fprintf(stderr,"Option -%c requires an argument. \n",optopt);
              return -1;
              }
              break;
        }
  }


  // Calculate the number of user inputed bases
  userStrand.size = relevant_elements(userStrand.dnaStrand); 
  if(userStrand.size == 0){
      fprintf(stderr, "Entered Empty Strand. Exiting\n"); 
      return -2; 
  }
  //Check that the user's strand is valid/ 'well formed'
  if(valid_strand(userStrand.dnaStrand, userStrand.size)!=1){
        fprintf(stderr," Strands can only consist of A, G, T, or C.\n \r");
        return -2;
  }
  printf("\n");
  printf(" User Options Selected: \n");
  if(firstSelectFlag == 1){
      printf(" \t-Sf: Enzymes will bind to their first available preferred starting base\n");
  }else if(randSelectFlag == 1){
      printf(" \t-Sr: Enzymes will randomly bind to one of the available preferred starting base\n");
  }
  printf("\n");

  // Copy the initial strand into the 0th element of the output strand 2-D array
  strcpy(userStrand.outputStrand[0], userStrand.dnaStrand); 

  printf(" Your strand is: %s \n \r", userStrand.dnaStrand);
  printf(" Initial strand is %d bases long \n \r", userStrand.size); 
  printf("\n");
  printf(" Decoding Enzymes: \n \r");
  printf("\n");
  
  // decode the user's strand into instructions and folding pattern
  userDecode = get_instructions_and_folding(userStrand.dnaStrand, userStrand.size); 
  
  //print the instructions in plain text
  printf(" \tTotal Strand Instructions are:\n");
  while(i <= 3*userStrand.size){
    if(i == 0){
        printf("\t\t\t%c%c%c ",userDecode.instructionText[i],userDecode.instructionText[i+1],userDecode.instructionText[i+2]);
    } else {
        printf("%c%c%c ",userDecode.instructionText[i],userDecode.instructionText[i+1],userDecode.instructionText[i+2]);
    }
    i = i+3; 
  }
  printf("\n \r");
  //if there are an odd number of bases, print last element  
  if(userStrand.size % 2 != 0){
      printf(" \t\t\twith last base %c \n\r",userStrand.dnaStrand[userStrand.size-1]); 
  }

  //reset i for later use
  i = 0; 

  printf("\n \r");
  
  //print the full folding pattern for clarity
  // may be removed in the future since it's not technically correct
  printf("Total Enzyme(s) folding pattern:\n"); 
  printf(" \t\t\t%s\n", userDecode.foldingPattern);
  printf("\n \r");
   
  //this variable is just so that I can print from lowest to highest in the while but still decrement
  int maxEnzymeCount = userDecode.enzymeCount;

  //if all elements of foldingPattern are '-' then exit  
  while(i < userDecode.enzymeCount){
    //if an element is not '-' then break out of this loop 
      if(userDecode.foldingPattern[i] != '-'){
          break; 
      }
      i++;
      if(i == userDecode.enzymeCount-1 && i != 1){
          printf("Strand consists only of A. Enzyme has no behavior. Ending.\n");
          return -1;
      }
  }

  //reset i for later use
  i = 0; 

  if(maxEnzymeCount > 1){
      printf("Strand has %d genes that code for %d enzymes\n", maxEnzymeCount ,maxEnzymeCount); 
  }
  printf("\n \r");
  // Testing: 
  // seperate index variable for the folding pattern which will maintain it's
  // value so that I can return to recalculate the next enzyme
  int instructionIndex = 0;
  int instructionNumberIndex = 0;
  int foldingIndex = 0;  
  int indentFlag = 1;  
  // while there are still enzymes left to execute
  while(userDecode.enzymeCount > 0) {
    printf("\n \r");
    //print from 1 to max instead of decrementing from max to 1  
    printf("Generating Enzyme %d folds and executing enzyme instructions:\n",(maxEnzymeCount - (userDecode.enzymeCount-1)));


    //print the instructions associated with the enzyme
    printf(" \tEnzyme %d instructions are: \n",(maxEnzymeCount - (userDecode.enzymeCount-1)));
    while(instructionIndex < userDecode.instructionTextSize) {
        // if the instruction is pun and either it's the first instruction or the loop flag is set, 
       if(userDecode.instruction[instructionNumberIndex] == 0  && indentFlag == 1){
        //print tabs in front of instructions for formatting 
          printf("\t\t\tpun");
          instructionNumberIndex++; 
          instructionIndex = instructionIndex+3; 
          indentFlag = 0; 
          break;
       //else if instruction is pun, just print spaces and increment past   
       }else if(userDecode.instruction[instructionNumberIndex] == 0){
          printf("   ");
          instructionNumberIndex++; 
          instructionIndex = instructionIndex+3; 
          break;
        }
       //if loop flag is set print tabs before first instruction
       if(indentFlag == 1){
          printf("\t\t\t%c%c%c ",userDecode.instructionText[instructionIndex],userDecode.instructionText[instructionIndex+1],userDecode.instructionText[instructionIndex+2]);
          indentFlag = 0; 
        } else {
          printf("%c%c%c ",userDecode.instructionText[instructionIndex],userDecode.instructionText[instructionIndex+1],userDecode.instructionText[instructionIndex+2]);
        }
        instructionNumberIndex++; 
        instructionIndex = instructionIndex+3; 
    }
    printf("\n \r");
    indentFlag = 1;

    // print the folding pattern 
    printf(" \tFolding Pattern is: \n");
    while(foldingIndex < userDecode.foldingPatternSize ){
        if(userDecode.foldingPattern[foldingIndex] == '-' && indentFlag == 1){
            //print space rather than  '-' for aesthetics
            printf("\t\t\t ");
            foldingIndex++; 
            indentFlag = 0; 
            break;
        } else if(userDecode.foldingPattern[foldingIndex] == '-'){
            //print space rather than  '-' for aesthetics
            printf(" ");
            foldingIndex++; 
            break;
        }
        if(indentFlag == 1){
            printf("\t\t\t%c",userDecode.foldingPattern[foldingIndex]);
            indentFlag = 0; 
        } else {
            printf("%c",userDecode.foldingPattern[foldingIndex]);
        }
        foldingIndex++; 
    }

    printf("\n \r");

    //reset i for later use
    i = 1;

    // calculate the starting base based on the folding pattern of the enzyme 
    char startingBase = calculate_starting_base(userDecode.foldingPattern,startingBaseIndex,foldingIndex); 


    //set the next starting point to the
    startingBaseIndex = foldingIndex;
    //print the calcuated starting base to bind to 
    printf(" Starting base to bind to is: '%c'\n",startingBase);
    //if calculate_starting_base returned '-', then inform the user
    if(startingBase == '-'){
        printf("Single AA Amino Acid detected. No binding chosen\n"); 
    }
    
    int *matchingElements = matching_starting_base_elements(userStrand.dnaStrand, userStrand.size, startingBase);
    //if the first element is the 'null' character, then there are no matching elements
    if(*matchingElements == -1) {
        printf("There are no matching elements to bind to. Ending enzyme\n");
    }else {

        printf(" Matching elements are:\n"); 
        //print the 0th element 
        //add one to index from 1 instead of 0
        printf(" \t\t\tBase %d\n",*matchingElements+1); 
        //print the rest of the matching elements
        while(matchingElements[i] != -1){
            //add one to index from 1 instead of 0
            printf(" \t\t\tBase %d\n",matchingElements[i]+1);
            i++;
        }
        // if there is more than one option of bases and the first select flag is not enabled:
        if(i != 1 && firstSelectFlag !=1){
          //if random select was enabled
            if(randSelectFlag == 1){
               //randomly select an option 
               printf("Randomly selecting an available base\n"); 
               userStrand.currentBoundPosition = matchingElements[(rand() % i)]+1; 
            }else{
                // prompt the user to select one
                printf("Please enter a base number to begin acting on: \n \r"); 
                scanf("%d", &userStrand.currentBoundPosition);
                //check that the entered value matches one of the elements of matchingElements
                //and correct for index starting at 0 instead of 1
                while(userStrand.dnaStrand[(userStrand.currentBoundPosition-1)] != startingBase){
                    printf("Sorry, enter a valid base number! \n");
                    scanf("%d", &userStrand.currentBoundPosition);
                }
            }
        } else{
          //if first select was enabled
            if(firstSelectFlag == 1){
                printf("Selecting the first matching element\n"); 
            }
            // automatically select the only/first choice
            userStrand.currentBoundPosition = matchingElements[0]+1;
        }
        printf("\n \r"); 
        printf("Enzyme will start acting on base %c at position %d\n",startingBase,userStrand.currentBoundPosition);
        printf("\n \r"); 
        printf(" \t\t\t\t\t%s\n",userStrand.complementaryStrand);        
        printf(" \t\t\t\t\t%s\n",userStrand.dnaStrand);        
        //print a line underneath array with ^ pointing at the starting base 
        char *arrowMarker = current_enzyme_position(userStrand.size, userStrand.currentBoundPosition);
        printf(" \t\t\t\t\t%s\n",arrowMarker); 

        //Begin acting on strand with instructions: 
        for(int i=0; i < userDecode.foldingPatternSize; i++) {
            userStrand = call_instruction(userDecode.instruction[i], userStrand); 
        }
    }


    //reset the indent flag 
    indentFlag = 1;
    userDecode.enzymeCount--;
    
  }//END OF WHILE
   printf("All enzymes executed.\n");
   printf("Initial Strand:\n");
   printf(" \t%s\n",userStrand.outputStrand[0]); 
   printf("Final Strand(s):\n");
   strcpy(userStrand.outputStrand[1], userStrand.dnaStrand);
   for(int i = 1; i <= userStrand.outputStrandCount; i++){
       printf(" \t%s\n", userStrand.outputStrand[i]);
   }
   printf("Exiting Typogenetics\n");
   return 0; 
}
