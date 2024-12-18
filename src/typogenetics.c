#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>
#include "typogenetics.h"




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
 * -Sr (--Select-random)
 *      randomly pick starting base for each enzyme 
 *
 * -Sf (--Select-first) 
 *      enzymes will select the first matching element to their base binding preference. 
 *
 * (an idea, but won't work if the output is multiple strands/ needs a way to pick one)
 * -i <int> 
 *      <int> # of interations
 *
 */ 

int main(int argC, char **argV) {

  //set locale for unicode printing
  setlocale(LC_ALL, "");
  //variables for input params 
  int opt,randSelectFlag,firstSelectFlag; 

  // usermode controls autostops and printing graphics 
  int userModeFlag = 1;
  char *userInput;   

  // Stat trackers
  int totalOutputStrands = 2;
  int iterationCount = 1;
                                      
  //struct stores user entered strand and it's size, along with other relevant information as it is processed
  //Each strand will have 2 outputs at least - main and complement
  //we start bound to the main strand, and the complement is generated potentially through instructions
  struct strand userStrand = {
                               .mainStrand = { ' ' }, 
                               .complementaryStrand = { ' ' },
                               .outputStrandCount = 2,
                               .boundStrandFlag = 0,
                               .copyModeFlag = 0,
                             };
  // struct stores decoded information about the strand
  struct decodedStrand userDecode = {
                                      .instruction = {0},
                                      .instructionText = {' '},
                                      .instructionTextSize = 0,
                                      .foldingPattern = {' '},
                                      .foldingPatternSize = 0, 
                                      .enzymeCount = 0, 
                                    };

  // parse user input for different config flags and initial input 
  while((opt = getopt(argC, argV, "hs:r:S:")) != -1) {
      switch(opt){
          case 'h':
              printf("*                                                                                      \n");
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
              printf("* -Sr  (--Select-random)                                                               \n");
              printf("*      randomly pick starting base for each enzyme                                     \n");
              printf("*                                                                                      \n");
              printf("* -Sf (--Select-first)                                                                 \n");
              printf("*      enzymes will select the first matching element to their base binding preference.\n");
              printf("*\n");
              return 1;  
          case 's':
            // if -s was passed char array set userStrand.mainStrand to it's value 
            userInput = optarg;
            strcpy(userStrand.mainStrand, userInput); 
            break;
          case 'r':
            userInput = rand_strand(atoi(optarg)); 
            strcpy(userStrand.mainStrand, userInput); 
            break;
          case 'S':
            userInput = optarg;
            if(strcmp(userInput, "f") == 0){
                firstSelectFlag = 1; 
          // disable usermode
                userModeFlag = 0; 
            }else if(strcmp(userInput, "r") == 0){
                randSelectFlag = 1;
          // disable usermode
                userModeFlag = 0; 
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

  print_splash();

  struct strand *strandPointer = &userStrand;
  int i;
  int startingBaseIndex;
  int instructionExecutionIndex = 0; 
  int instructionIndex = 0;           //keep track of where I am in the instruction array 
  int instructionNumberIndex = 0;     //keep track of where I am in the instruction text array
  int foldingIndex, patternIndex = 0;               //keep track of where I am in the folding pattern array
  int indentFlag = 1;                 //flag to indent first character printed  

  // variable for tracking user input
  int enter = -1;

  /* ----------- BEGINNGING OF MAIN LOOP ----------*/

  do {
  //index for managing loops 
  i = 0;
  startingBaseIndex = 0;
  instructionExecutionIndex = 0; 
  instructionIndex = 0;           //keep track of where I am in the instruction array 
  instructionNumberIndex = 0;     //keep track of where I am in the instruction text array
  foldingIndex = 0; 
  patternIndex = 0;               //keep track of where I am in the folding pattern array
  indentFlag = 1;                 //flag to indent first character printed  
  

  // Calculate the number of user inputed bases
  userStrand.mainSize = relevant_elements(userStrand.mainStrand); 
  if(userStrand.mainSize == 0) {
      fprintf(stderr, "Entered Empty Strand. Exiting\n"); 
      return -2; 
  }
  //Check that the user's strand is valid/ 'well formed'
  if(valid_strand(userStrand.mainStrand, userStrand.mainSize)!=1) {
        fprintf(stderr," Strands can only consist of A, G, T, or C.\n \r");
        fprintf(stderr," Try '-h' for more information\n \r");
        return -2;
  }
  printf("\n");
  printf(" User Options Selected: \n");
  if(firstSelectFlag == 1) {
      printf(" \t-Sf: Enzymes will bind to their first available preferred starting base\n");
  }else if(randSelectFlag == 1) {
      printf(" \t-Sr: Enzymes will randomly bind to one of the available preferred starting base\n");
  } else {
      printf(" \tNone.\n");
  }
  printf("\n");

  // Copy the initial strand into the 0th element of the output strand 2-D array
  strcpy(userStrand.outputStrand[0], userStrand.mainStrand); 

  printf(" Your strand is: %s \n \r", userStrand.mainStrand);
  printf(" Initial strand is %d bases long \n \r", userStrand.mainSize); 
  printf("\n");
  printf(" Decoding Enzymes: \n \r");
  printf("\n");
  
  // decode the user's strand into instructions and folding pattern
  userDecode = get_instructions_and_folding(userStrand.mainStrand, userStrand.mainSize); 
  
  //print the instructions in plain text
  printf(" \tTotal Strand Instructions are:\n");
  while(i <= 3*userStrand.mainSize){
    if(i == 0) {
        printf("\t\t\t%c%c%c ",userDecode.instructionText[i],userDecode.instructionText[i+1],userDecode.instructionText[i+2]);
    } else {
        printf("%c%c%c ",userDecode.instructionText[i],userDecode.instructionText[i+1],userDecode.instructionText[i+2]);
    }
    i = i+3; 
  }
  printf("\n \r");
  //if there are an odd number of bases, print last element  
  if(userStrand.mainSize % 2 != 0){
      printf(" \t\t\twith last base %c \n\r",userStrand.mainStrand[userStrand.mainSize-1]); 
  }

  //reset i for later use
  i = 0; 

  printf("\n \r");
  
  //print the full folding pattern for clarity
  // may be removed in the future since it's not technically correct
  printf(" \tAll Enzymes folding pattern:\n"); 
  printf(" \t\t\t%s\n", userDecode.foldingPattern);
  printf("\n \r");
   
  //this variable is just so that I can print from lowest to highest in the while but still decrement
  int maxEnzymeCount = userDecode.enzymeCount;

  //if all elements of foldingPattern are '-' then exit  
  while(i < userDecode.enzymeCount) {
    //if an element is not '-' then break out of this loop 
      if(userDecode.foldingPattern[i] != '-'){
          break; 
      }
      i++;
  }
      if(i == userDecode.enzymeCount){
          printf("Strand consists only of A. Enzyme has no behavior. Ending.\n");
          return -1;
      }

  //reset i for later use
  i = 0; 

  if(maxEnzymeCount > 1){
      printf("Strand has %d genes that code for %d enzymes\n", maxEnzymeCount ,maxEnzymeCount); 
  }
  printf("\n \r");


  // while there are still enzymes left to execute
  while(userDecode.enzymeCount > 0) {
    printf("\n \r");
    // set copy mode flag off at the start of all enzyme activity
    userStrand.copyModeFlag = 0; 
    userStrand.boundStrandFlag = 0;
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
       } else if(userDecode.instruction[instructionNumberIndex] == 0) {
          printf("   ");
          instructionNumberIndex++; 
          instructionIndex = instructionIndex+3; 
          break;
        }
       //if loop flag is set print tabs before first instruction
       if(indentFlag == 1) {
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
    while(foldingIndex < userDecode.foldingPatternSize ) {
        if(userDecode.foldingPattern[foldingIndex] == '-' && indentFlag == 1) {
            //print space rather than  '-' for aesthetics
            printf("\t\t\t ");
            foldingIndex++; 
            indentFlag = 0; 
            break;
        } else if(userDecode.foldingPattern[foldingIndex] == '-') {
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

    if(userModeFlag == 1) {
      wait_for_user();
    }
    
    //print new lines for formatting
    for(int i = 0; i < GRID_DIMENSION*CELL_HEIGHT; i++) {
      printf("\n \r");
    }
    // print the enzyme folding grid 
    // if user mode is on 
    if(userModeFlag == 1) {
      patternIndex = enzyme_folding(userDecode, patternIndex);
    }

    if(userModeFlag == 1) {
      wait_for_user();
    }

    //reset i for later use
    i = 1;

    // calculate the starting base based on the folding pattern of the enzyme 
    char startingBase = calculate_starting_base(userDecode.foldingPattern,startingBaseIndex,foldingIndex); 


    //set the next starting point to the
    startingBaseIndex = foldingIndex;
    //print the calcuated starting base to bind to 
    printf(" Starting base to bind to is: '%c'\n",startingBase);
    //if calculate_starting_base returned '-', then inform the user
    if(startingBase == '-') {
        printf("Single AA Amino Acid detected. No binding chosen\n"); 
        instructionExecutionIndex++;  
    }
    
    int *matchingElements = matching_starting_base_elements(userStrand.mainStrand, userStrand.mainSize, startingBase);
    //if the first element is the 'null' character, then there are no matching elements
    if(*matchingElements == -1) {
        printf("There are no matching elements to bind to. Ending enzyme\n");
    } else {
        printf(" Matching elements are:\n"); 
        //print the 0th element 
        //add one to index from 1 instead of 0
        printf(" \t\t\tBase %d\n",*matchingElements+1); 
        //print the rest of the matching elements
        while(matchingElements[i] != -1) {
            //add one to index from 1 instead of 0
            printf(" \t\t\tBase %d\n",matchingElements[i]+1);
            i++;
        }
        // if there is more than one option of bases and the first select flag is not enabled:
        if(i != 1 && firstSelectFlag !=1) {
          //if random select was enabled
            if(randSelectFlag == 1) {
               //randomly select an option 
               printf("Randomly selecting an available base\n"); 
               userStrand.currentBoundPosition = matchingElements[(rand() % i)]+1; 
            } else {
                // prompt the user to select one
                printf("Please enter a base number to begin acting on: \n \r"); 
                scanf("%d", &userStrand.currentBoundPosition);
                //check that the entered value matches one of the elements of matchingElements
                //and correct for index starting at 0 instead of 1
                while(userStrand.mainStrand[(userStrand.currentBoundPosition-1)] != startingBase) {
                    printf("Sorry, enter a valid base number! \n");
                    scanf("%d", &userStrand.currentBoundPosition);
                }
            }
        } else {
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
        //the complementary will be blank for the first printing
        printf(" \t\t\t\t\t");        
        print_complementary_strand(userStrand.complementarySize, userStrand.complementaryStrand); 
        printf("\n");
        printf(" \t\t\t\t\t%s\n",userStrand.mainStrand);        
        //print a line underneath array with ^ pointing at the starting base 
        char *arrowMarker = current_enzyme_position(strandPointer,1);
        printf(" \t\t\t\t\t%s\n",arrowMarker); 

        //Begin acting on strand with instructions: 
        while(instructionExecutionIndex <= userDecode.foldingPatternSize) {
          //if the instruction is pun, don't print anything more for this enzyme, just break
          if(userDecode.instruction[instructionExecutionIndex] == 0) {
              instructionExecutionIndex++;  
              break;
          }

          //determine what instruction to execute
          call_instruction(userDecode.instruction[instructionExecutionIndex], strandPointer); 
          printf(" Executing: %c%c%c\n", userDecode.instructionText[3*instructionExecutionIndex],userDecode.instructionText[3*instructionExecutionIndex+1], userDecode.instructionText[3*instructionExecutionIndex+2]); 
          arrowMarker = current_enzyme_position(strandPointer,0);
          printf(" \t\t\t\t\t%s\n",arrowMarker); 
          printf(" \t\t\t\t\t");
          print_complementary_strand(userStrand.complementarySize, userStrand.complementaryStrand); 
          printf("\n");
          printf(" \t\t\t\t\t%s\n",userStrand.mainStrand);        
          //print a line underneath array with ^ pointing at the bound base 
          arrowMarker = current_enzyme_position(strandPointer, 1);
          printf(" \t\t\t\t\t%s\n",arrowMarker); 
          //check if the enzyme has moved off of the strand or into a gap, accounting for indexing from 1 for currentBoundPosition
          if(check_falling_off(strandPointer) == 1) {
              printf("Enzyme has moved off of strand. Exiting.\n");

              //increment until we reach the first instruction in the next enzyme
              while(userDecode.instruction[instructionExecutionIndex] != 0) {
                  instructionExecutionIndex++;
              }
              instructionExecutionIndex++;
              break;
          } 
                  
          instructionExecutionIndex++;  
      }
        printf("Enzyme %d complete.\n", (maxEnzymeCount - (userDecode.enzymeCount-1)));
  }


    //reset the indent flag 
    indentFlag = 1;
    userDecode.enzymeCount--;

    if(userModeFlag == 1) {
      wait_for_user();
    }
    
  }//END OF WHILE
   printf("All enzymes executed.\n");
   printf("Initial Strand:\n");
   printf(" \t%s\n",userStrand.outputStrand[0]); 
   printf("Final Strand(s):\n");

   strcpy(userStrand.outputStrand[1], userStrand.mainStrand);

   int j = 0;
   //reverse the order of the remaining complementary strand and place it into the output
   for(int i = userStrand.complementarySize-1; i >= 0; i--) {
      userStrand.outputStrand[2][j] = userStrand.complementaryStrand[i];
      j++;  
   }
   userStrand.outputStrand[2][j] = '\0';


   //cut any gaps in the strands into their own separate outputs 
   strand_splitter(strandPointer);


   //print the output strands 
   printf("Main Strand: \n");
   printf(" 1. \t%s\n",userStrand.outputStrand[1]); 
   printf("Complementary Strand: \n");
   printf(" 2. \t");
   for (int i = 0; i <userStrand.complementarySize; i++){
      printf("%c",userStrand.outputStrand[2][i]);
   }
   printf("\n");
   printf("Generated Strands: \n");
   for(int i = 3; i <= userStrand.outputStrandCount; i++){
      // if the first element is not A,G,T, or C, then it's an empty strand
      if(userStrand.outputStrand[i][0] == 'A' || userStrand.outputStrand[i][0] == 'C' || userStrand.outputStrand[i][0] == 'G' || userStrand.outputStrand[i][0] == 'T') {
          printf(" %d.  \t%s\n",i,userStrand.outputStrand[i]);
      } else {
          //so don't print
   }
  }
  int validInput = 0;

  while(validInput == 0) {
    printf("Select an output strand number to begin acting on, or enter '0' to quit \n");
    scanf("%d", &enter);

    switch (enter) {
        case 0:
          validInput = 1;
          break;
        default:
          if(enter > userStrand.outputStrandCount || enter < 0) {
            printf("Please enter a number corresponding to an output strand: \n");
          } else {
            // copy the selected option into the mainStrand, choosing the proper output strand index
            strcpy(userStrand.mainStrand, userStrand.outputStrand[enter]);
            for (int i = 0; i <userStrand.complementarySize; i++){
            //set complement to spaces
              userStrand.outputStrand[2][i] = ' ';
            }
            iterationCount++;
            totalOutputStrands += userStrand.outputStrandCount;
            //reset strands values for the new iterations
            //except for the main strand 
            userStrand = init_user_strand(userStrand.mainStrand, userStrand.outputStrandCount);
            userDecode = init_decoded_strand();
            validInput = 1;
          }
          break;
      }
    }
} while(enter != 0); // END OF do while

  printf("Total number of iterations: %d\n",iterationCount);
  printf("Exiting Typogenetics\n");
  return 0; 
}
