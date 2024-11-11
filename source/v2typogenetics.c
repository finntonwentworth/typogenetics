
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "enzymefunctions.h"



int main(void) {
    

  // dont forget to clarify and update the rules
  
  printf("Welcome to Typogenetics!\n \r");
  printf(" Here are the rules:\n \r");
  printf(" 1. Begin by entering an arbitrary strand consisting of the 4 bases: A, G, T & C. \n \r");
  printf(" Each pair of bases will encode for an instruction in an 'enzyme,' which will in turn manipulate the strand that you entered. \n \r");
  printf(" 2. There are 16 enzyme instructions: \n \r");
  printf(" \n");
  printf(" 0.  AA: pun (-) | 1.  AC: cut (s) | 2.  AG: del (s) | 3.  AT: swi (r)\n \r");
  printf(" --------------------------------------------------------------------- \n \r");
  printf(" 4.  CA: mvr (s) | 5.  CC: mvl (s) | 6.  CG: cop (r) | 7.  CT: off (l)\n \r");
  printf(" --------------------------------------------------------------------- \n \r");
  printf(" 8.  GA: ina (s) | 9.  GC: inc (r) | 10. GG: ing (r) | 11. GT: int (l)\n \r");
  printf(" --------------------------------------------------------------------- \n \r");
  printf(" 12. TA: rpy (r) | 13. TC: rpu (l) | 14. TG: lpy (l) | 15. TT: lpu (l)\n \r");
  printf(" \n");

  printf(" 3. Each instruction 'folds' the enzyme in a specific way, with the direction straight(s), left(l), or right(r) \n \r");
  printf(" (AA is a 'punctutation mark' acting to split the enzyme into 2 or more separate enzymes) \n \r");
  printf(" 4. Each enzyme will begin acting on a specfic base in your strand based on the starting and ending bases orientation relevant to each other that encode the enzyme \n \r "); 

  struct strand userstrand; 
  struct decodedstrand userdecode;
  int i = 0; 

  printf("Enter a strand: \n");
  scanf("%s",userstrand.dnastrand);

  // Calculate the number of user inputed bases
  userstrand.size = relevant_elements(userstrand.dnastrand); 
  //Check that the user's strand is valid/ 'well formed'
  while(valid_strand(userstrand.dnastrand, userstrand.size)!=1){
        printf(" Sorry, strands can only consist of A, G, T, or C! \n \r");
        printf(" Please Enter a new strand: \r \n");
        scanf("%s",userstrand.dnastrand);
        userstrand.size = relevant_elements(userstrand.dnastrand); 
  }

  printf(" Your strand is: %s \n \r", userstrand.dnastrand);
  printf(" Initial strand is %d bases long \n \r", userstrand.size); 
  printf("\n");
  printf(" Decoding Enzymes: \n \r");
  printf("\n");
  
  // decode the user's strand into instructions and folding pattern
  userdecode = get_instructions_and_folding(userstrand.dnastrand, userstrand.size); 
  
  //print the instructions in plain text
  printf(" \tInstructions are:\n");
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
  
  // print the folding pattern 
  printf(" \tFolding Pattern is: \n");
  while(i < userdecode.foldingpatternsize ){
    if(i == 0){
        printf("\t\t\t%c",userdecode.foldingpattern[i]);
    } else {
        printf("%c",userdecode.foldingpattern[i]);
    }
    i++; 
  }

  printf("\n \r");

  // will this ever be useful to store in the userdecode struct? 
  char startingbase = calculate_starting_base(userdecode.foldingpattern, userdecode.foldingpatternsize); 
  printf(" Starting base to bind to is: '%c'\n",startingbase);
  
  //reset i for later use
  i = 1;
  
  int *matchingelements = matching_starting_base_elements(userstrand.dnastrand, userstrand.size, startingbase);
  printf(" Matching elements are:\n"); 
  //print the 0th element 
  printf(" \t\t\tBase %d\n",*matchingelements+1); 
  //print the rest of the matching elements
  while(matchingelements[i] != '\0'){
    printf(" \t\t\tBase %d\n",matchingelements[i]+1);
    i++;
  }
  int startingbaseposition;
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
  } else {
      // automatically select the only choice
      startingbaseposition = matchingelements[0]+1;
  }

  printf("\n \r"); 
  printf("Enzyme will start acting on base %c at position %d\n",startingbase,startingbaseposition);
  printf("\n \r"); 
  printf(" \t\t\t\t\t%s\n",userstrand.dnastrand);        
  //print a line underneath array with ^ pointing at the starting base 
  char *arrowmarker = current_enzyme_position(startingbaseposition);
  printf(" \t\t\t\t\t%s\n",arrowmarker); 
}
