
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "enzymefunctions.h"

#include <unistd.h>

/* PARAMETERS LIST
 *
 * MANDATORY: 
 * -s (--strand)  <char strand[]> 
 *     Use inputted strand[] as input or generate random strand with <int> # of bases
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
  int i, startingbaseindex  = 0; 
  char *userInput;   
  //struct stores user entered strand and it's size  
  struct strand userstrand; 
  // struct stores decoded information about the strand
  struct decodedstrand userdecode;

  while((opt = getopt(argC, argV, "s:r:S:")) != -1){
      switch(opt){
          case 's':
            // if -s was passed char array set userstrand.dnastrand to it's value 
            userInput = optarg;
            strcpy(userstrand.dnastrand, userInput); 
            break;
          case 'r':
            userInput = rand_strand(atoi(optarg)); 
            strcpy(userstrand.dnastrand, userInput); 
            break;
          case 'S':
            userInput = optarg;
            if(strcmp(userInput, "f") == 0){
                firstSelectFlag = 1; 
            }else if(strcmp(userInput, "r") == 0){
                randSelectFlag = 1;
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
  userstrand.size = relevant_elements(userstrand.dnastrand); 
  if(userstrand.size == 0){
      fprintf(stderr, "Entered Empty Strand. Exiting\n"); 
      return -2; 
  }
  //Check that the user's strand is valid/ 'well formed'
  if(valid_strand(userstrand.dnastrand, userstrand.size)!=1){
        fprintf(stderr," Strands can only consist of A, G, T, or C.\n \r");
        return -2;
  }
  printf(" User Options Selected: \n");
  if(firstSelectFlag == 1){
      printf(" \t-Sf: Enzymes will bind to their first available preferred starting base\n");
  }else if(randSelectFlag == 1){
      printf(" \t-Sr: Enzymes will randomly bind to one of the available preferred starting base\n");
  }
  printf("\n");

  printf(" Your strand is: %s \n \r", userstrand.dnastrand);
  printf(" Initial strand is %d bases long \n \r", userstrand.size); 
  printf("\n");
  printf(" Decoding Enzymes: \n \r");
  printf("\n");
  
  // decode the user's strand into instructions and folding pattern
  userdecode = get_instructions_and_folding(userstrand.dnastrand, userstrand.size); 
  
  //print the instructions in plain text
  printf(" \tTotal Strand Instructions are:\n");
  while(i <= 3*userstrand.size){
    if(i == 0){
        printf("\t\t\t%c%c%c ",userdecode.instructiontext[i],userdecode.instructiontext[i+1],userdecode.instructiontext[i+2]);
    } else {
        printf("%c%c%c ",userdecode.instructiontext[i],userdecode.instructiontext[i+1],userdecode.instructiontext[i+2]);
    }
    i = i+3; 
  }
  printf("\n \r");
  //if there are an odd number of bases, print last element  
  if(userstrand.size % 2 != 0){
      printf(" \t\t\twith last base %c \n\r",userstrand.dnastrand[userstrand.size-1]); 
  }

  //reset i for later use
  i = 0; 

  printf("\n \r");
  
  //print the full folding pattern for clarity
  // may be removed in the future since it's not technically correct
  printf("Total Enzyme(s) folding pattern:\n"); 
  printf(" \t\t\t%s\n", userdecode.foldingpattern);
  printf("\n \r");
   
  //this variable is just so that I can print from lowest to highest in the while but still decrement
  int maxenzymecount = userdecode.enzymecount;

  //if all elements of foldingpattern are '-' then exit  
  while(i < userdecode.enzymecount){
    //if an element is not '-' then break out of this loop 
      if(userdecode.foldingpattern[i] != '-'){
          break; 
      }
      i++;
      if(i == userdecode.enzymecount-1){
          printf("Strand consists only of A. Enzyme has no behavior. Ending.\n");
          return -1;
      }
  }

  //reset i for later use
  i = 0; 

  if(maxenzymecount > 1){
      printf("Strand has %d genes that code for %d enzymes\n", maxenzymecount,maxenzymecount); 
  }
  printf("\n \r");
  // Testing: 
  // seperate index variable for the folding pattern which will maintain it's
  // value so that I can return to recalculate the next enzyme
  int instructionindex = 0;
  int instructionnumberindex = 0;
  int foldingindex = 0;  
  int indentflag = 1;  
  // while there are still enzymes left to execute
  while(userdecode.enzymecount > 0) {
    printf("\n \r");
    //print from 1 to max instead of decrementing from max to 1  
    printf("Generating Enzyme %d folds and executing enzyme instructions:\n",(maxenzymecount - (userdecode.enzymecount-1)));


    //print the instructions associated with the enzyme
    printf(" \tEnzyme %d instructions are: \n",(maxenzymecount - (userdecode.enzymecount-1)));
    while(instructionindex < userdecode.instructiontextsize) {
        // if the instruction is pun and either it's the first instruction or the loop flag is set, 
       if(userdecode.instruction[instructionnumberindex] == 0  && indentflag == 1){
        //print tabs in front of instructions for formatting 
          printf("\t\t\tpun");
          instructionnumberindex++; 
          instructionindex = instructionindex+3; 
          indentflag = 0; 
          break;
       //else if instruction is pun, just print spaces and increment past   
       }else if(userdecode.instruction[instructionnumberindex] == 0){
          printf("   ");
          instructionnumberindex++; 
          instructionindex = instructionindex+3; 
          break;
        }
       //if loop flag is set print tabs before first instruction
       if(indentflag == 1){
          printf("\t\t\t%c%c%c ",userdecode.instructiontext[instructionindex],userdecode.instructiontext[instructionindex+1],userdecode.instructiontext[instructionindex+2]);
          indentflag = 0; 
        } else {
          printf("%c%c%c ",userdecode.instructiontext[instructionindex],userdecode.instructiontext[instructionindex+1],userdecode.instructiontext[instructionindex+2]);
        }
        instructionnumberindex++; 
        instructionindex = instructionindex+3; 
    }
    printf("\n \r");
    indentflag = 1;

    // print the folding pattern 
    printf(" \tFolding Pattern is: \n");
    while(foldingindex < userdecode.foldingpatternsize ){
        if(userdecode.foldingpattern[foldingindex] == '-' && indentflag == 1){
            //print space rather than  '-' for aesthetics
            printf("\t\t\t ");
            foldingindex++; 
            indentflag = 0; 
            break;
        } else if(userdecode.foldingpattern[foldingindex] == '-'){
            //print space rather than  '-' for aesthetics
            printf(" ");
            foldingindex++; 
            break;
        }
        if(indentflag == 1){
            printf("\t\t\t%c",userdecode.foldingpattern[foldingindex]);
            indentflag = 0; 
        } else {
            printf("%c",userdecode.foldingpattern[foldingindex]);
        }
        foldingindex++; 
    }

    printf("\n \r");

    //reset i for later use
    i = 1;

    // calculate the starting base based on the folding pattern of the enzyme 
    char startingbase = calculate_starting_base(userdecode.foldingpattern,startingbaseindex,foldingindex); 


    //set the next starting point to the
    startingbaseindex = foldingindex;
    //print the calcuated starting base to bind to 
    printf(" Starting base to bind to is: '%c'\n",startingbase);
    //if calculate_starting_base returned '-', then inform the user
    if(startingbase == '-'){
        printf("Single AA Amino Acid detected. No binding chosen\n"); 
    }
    
    int *matchingelements = matching_starting_base_elements(userstrand.dnastrand, userstrand.size, startingbase);
    int startingbaseposition;
    //if the first element is the 'null' character, then there are no matching elements
    //this may need to decrement enzymecount and break once I add instruction execution
    if(*matchingelements == -1) {
        printf("There are no matching elements to bind to. Ending enzyme\n");
    }else {

        printf(" Matching elements are:\n"); 
        //print the 0th element 
        //add one to index from 1 instead of 0
        printf(" \t\t\tBase %d\n",*matchingelements+1); 
        //print the rest of the matching elements
        while(matchingelements[i] != -1){
            //add one to index from 1 instead of 0
            printf(" \t\t\tBase %d\n",matchingelements[i]+1);
            i++;
        }
        // if there is more than one option of bases:
        if(i != 1){
            // prompt the user to select one
            printf("Please enter a base number to begin acting on: \n \r"); 
            scanf("%d", &startingbaseposition);
            //check that the entered value matches one of the elements of matchingelements
            //and correct for index starting at 0 instead of 1
            while(userstrand.dnastrand[(startingbaseposition-1)] != startingbase){
                printf("Sorry, enter a valid base number! \n");
                scanf("%d", &startingbaseposition);
            }
        } else{
            // automatically select the only choice
            startingbaseposition = matchingelements[0]+1;
        }
        printf("\n \r"); 
        printf("Enzyme will start acting on base %c at position %d\n",startingbase,startingbaseposition);
        printf("\n \r"); 
        printf(" \t\t\t\t\t%s\n",userstrand.dnastrand);        
        //print a line underneath array with ^ pointing at the starting base 
        char *arrowmarker = current_enzyme_position(userstrand.size, startingbaseposition);
        printf(" \t\t\t\t\t%s\n",arrowmarker); 
    }


    //reset the indent flag 
    indentflag = 1;
    userdecode.enzymecount--;
    
  }//END OF WHILE
   printf("All enzymes executed.\n");
   printf("Final Strand(s):\n");
   printf(" \t%s\n", userstrand.dnastrand);
   printf("Exiting Typogenetics\n");
   return 0; 
}
