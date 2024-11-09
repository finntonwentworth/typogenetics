
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
  }

  printf(" Your strand is: %s \n \r", userstrand.dnastrand);
  printf("\n");
  printf(" Decoding Enzymes: \n \r");
  printf("\n");
  
  // decode the user's strand into instructions and folding pattern
  userdecode = determine_folding(userstrand.dnastrand, userstrand.size); 
  
  //print the instructions in plain text
  printf(" \tInstructions are:\n");
  while(userdecode.instructiontext[i] != '\0'){
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
      printf(" \t\t\twith last base %c \n\r",userstrand.dnastrand[i-4]); 
  }
  // print the folding pattern 
  i = 0; 
  printf("\n \r");
  printf(" \tFolding Pattern is: \n");
  while(userdecode.foldingpattern[i] != '\0'){
    if(i == 0){
        printf("\t\t\t%c",userdecode.foldingpattern[i]);
    } else {
        printf("%c",userdecode.foldingpattern[i]);
    }
    i++; 
  }
  printf("\n");
}
