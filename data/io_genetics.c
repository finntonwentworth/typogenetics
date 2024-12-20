#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>
#include "../src/typogenetics.h"




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
  struct strand userStrand =        {
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
                return -1;
            }
            break;
          case '?': 
            if(optopt == 's' || optopt == 'r' || optopt == 'S'){
              return -1;
              }
              break;
        }
  }


  struct strand *strandPointer = &userStrand;
  int i;
  int startingBaseIndex;
  int instructionExecutionIndex = 0; 
  int instructionIndex = 0;           //keep track of where I am in the instruction array 
  int instructionNumberIndex = 0;     //keep track of where I am in the instruction text array
  int foldingIndex, patternIndex = 0;               //keep track of where I am in the folding pattern array
  int indentFlag = 1;                 //flag to indent first character printed  


  /* ----------- BEGINNGING OF MAIN LOOP ----------*/

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
      return -2; 
  }
  //Check that the user's strand is valid/ 'well formed'
  if(valid_strand(userStrand.mainStrand, userStrand.mainSize)!=1) {
        return -2;
  }
  if(firstSelectFlag == 1) {
  }else if(randSelectFlag == 1) {
  } else {
  }

  // Copy the initial strand into the 0th element of the output strand 2-D array
  strcpy(userStrand.outputStrand[0], userStrand.mainStrand); 

  printf("%s,", userStrand.mainStrand);
  
  // decode the user's strand into instructions and folding pattern
  userDecode = get_instructions_and_folding(userStrand.mainStrand, userStrand.mainSize); 
  
  //print the instructions in plain text
  while(i <= 3*userStrand.mainSize){
    if(i == 0) {
    } else {
    }
    i = i+3; 
  }
  //if there are an odd number of bases, print last element  
  if(userStrand.mainSize % 2 != 0){
  }

  //reset i for later use
  i = 0; 

  
  //print the full folding pattern for clarity
  // may be removed in the future since it's not technically correct
   
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
          return -1;
      }

  //reset i for later use
  i = 0; 

  if(maxEnzymeCount > 1){
  }


  // while there are still enzymes left to execute
  while(userDecode.enzymeCount > 0) {
    // set copy mode flag off at the start of all enzyme activity
    userStrand.copyModeFlag = 0; 
    userStrand.boundStrandFlag = 0;
    //print from 1 to max instead of decrementing from max to 1  


    //print the instructions associated with the enzyme
    while(instructionIndex < userDecode.instructionTextSize) {
        // if the instruction is pun and either it's the first instruction or the loop flag is set, 
       if(userDecode.instruction[instructionNumberIndex] == 0  && indentFlag == 1){
        //print tabs in front of instructions for formatting 
          instructionNumberIndex++; 
          instructionIndex = instructionIndex+3; 
          indentFlag = 0; 
          break;
       //else if instruction is pun, just print spaces and increment past   
       } else if(userDecode.instruction[instructionNumberIndex] == 0) {
          instructionNumberIndex++; 
          instructionIndex = instructionIndex+3; 
          break;
        }
       //if loop flag is set print tabs before first instruction
       if(indentFlag == 1) {
          indentFlag = 0; 
        } else {
        }
        instructionNumberIndex++; 
        instructionIndex = instructionIndex+3; 
    }
    indentFlag = 1;

    // print the folding pattern 
    while(foldingIndex < userDecode.foldingPatternSize ) {
        if(userDecode.foldingPattern[foldingIndex] == '-' && indentFlag == 1) {
            //print space rather than  '-' for aesthetics
            foldingIndex++; 
            indentFlag = 0; 
            break;
        } else if(userDecode.foldingPattern[foldingIndex] == '-') {
            //print space rather than  '-' for aesthetics
            foldingIndex++; 
            break;
        }
        if(indentFlag == 1){
            indentFlag = 0; 
        } else {
        }
        foldingIndex++; 
    }


    if(userModeFlag == 1) {
      wait_for_user();
    }
    
    //print new lines for formatting
    for(int i = 0; i < GRID_DIMENSION*CELL_HEIGHT; i++) {
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
    //if calculate_starting_base returned '-', then inform the user
    if(startingBase == '-') {
        instructionExecutionIndex++;  
    }
    
    int *matchingElements = matching_starting_base_elements(userStrand.mainStrand, userStrand.mainSize, startingBase);
    //if the first element is the 'null' character, then there are no matching elements
    if(*matchingElements == -1) {
    } else {
        //print the 0th element 
        //add one to index from 1 instead of 0
        //print the rest of the matching elements
        while(matchingElements[i] != -1) {
            //add one to index from 1 instead of 0
            i++;
        }
        // if there is more than one option of bases and the first select flag is not enabled:
        if(i != 1 && firstSelectFlag !=1) {
          //if random select was enabled
            if(randSelectFlag == 1) {
               //randomly select an option 
               userStrand.currentBoundPosition = matchingElements[(rand() % i)]+1; 
            } else {
                // prompt the user to select one
                scanf("%d", &userStrand.currentBoundPosition);
                //check that the entered value matches one of the elements of matchingElements
                //and correct for index starting at 0 instead of 1
                while(userStrand.mainStrand[(userStrand.currentBoundPosition-1)] != startingBase) {
                    scanf("%d", &userStrand.currentBoundPosition);
                }
            }
        } else {
          //if first select was enabled
            if(firstSelectFlag == 1){
            }
         // automatically select the only/first choice 
            userStrand.currentBoundPosition = matchingElements[0]+1; 
        }

    
        //the complementary will be blank for the first printing
        //print a line underneath array with ^ pointing at the starting base 
        char *arrowMarker = current_enzyme_position(strandPointer,1);

        //Begin acting on strand with instructions: 
        while(instructionExecutionIndex <= userDecode.foldingPatternSize) {
          //if the instruction is pun, don't print anything more for this enzyme, just break
          if(userDecode.instruction[instructionExecutionIndex] == 0) {
              instructionExecutionIndex++;  
              break;
          }

          //determine what instruction to execute
          call_instruction(userDecode.instruction[instructionExecutionIndex], strandPointer); 
          arrowMarker = current_enzyme_position(strandPointer,0);
          //print a line underneath array with ^ pointing at the bound base 
          arrowMarker = current_enzyme_position(strandPointer, 1);
          //check if the enzyme has moved off of the strand or into a gap, accounting for indexing from 1 for currentBoundPosition
          if(check_falling_off(strandPointer) == 1) {

              //increment until we reach the first instruction in the next enzyme
              while(userDecode.instruction[instructionExecutionIndex] != 0) {
                  instructionExecutionIndex++;
              }
              instructionExecutionIndex++;
              break;
          } 
                  
          instructionExecutionIndex++;  
      }
  }


    //reset the indent flag 
    indentFlag = 1;
    userDecode.enzymeCount--;

    if(userModeFlag == 1) {
      wait_for_user();
    }
    
  }//END OF WHILE
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
   printf("%s,",userStrand.outputStrand[1]); 
   printf("%c",userStrand.outputStrand[2][i]);
   printf(","); 
   for(int i = 3; i <= userStrand.outputStrandCount; i++) {
      // if the first element is not A,G,T, or C, then it's an empty strand
      if(userStrand.outputStrand[i][0] == 'A' || userStrand.outputStrand[i][0] == 'C' || userStrand.outputStrand[i][0] == 'G' || userStrand.outputStrand[i][0] == 'T') {
          printf("%s,",userStrand.outputStrand[i]);
      } else {
          //so don't print
   }
  printf("\n");
  }
  return 0; 
}
