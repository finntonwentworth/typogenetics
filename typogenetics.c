




#include <stdint.h>

#include <stdio.h>
#include "enzymefunctions.h"




int main(void) {
char instruction_prompt;

  // dont forget to clarify and update the rules
  
  printf("Welcome to Typogenetics!\n \r");
  printf("Would you like to hear the rules? [y/n]");
  scanf(" %c",&instruction_prompt);
  
  if(instruction_prompt == 'y'){
  printf("Here are the rules:\n \r");
  printf("1. Begin by entering an arbitrary strand consisting of the 4 bases: A, G, T & C. \n \r");
  printf("Each pair of bases will encode for an instruction in an 'enzyme,' which will in turn manipulate the strand that you entered. \r \n");
  printf("2. There are 16 enzyme instructions: \r \n");
  printf("\n");
  printf("AA: pun (-) | AC: cut (s) | AG: del (s) | AT: swi (r)\r \n");
  printf("--------------------------------------------------- \r \n");
  printf("CA: mvr (s) | CC: mvl (s) | CG: cop (r) | CT: off (l)\r \n");
  printf("--------------------------------------------------- \r \n");
  printf("GA: ina (s) | GC: inc (r) | GG: ing (r) | GT: int (l) \r \n");
  printf("--------------------------------------------------- \r \n");
  printf("TA: rpy (r) | TC: rpu (l) | TG: lpy (l) | TT: lpu (l) \r \n");
  printf("\n");

  printf("3. Each instruction 'folds' the enzyme in a specific way, with the direction straight(s), left(l), or right(r) \r \n");
  printf("(AA is a 'punctutation mark' acting to split the enzyme into 2 or more separate enzymes \r \n)");
  printf("4. Each enzyme will begin acting on a specfic base in your strand based on the starting and ending bases orientation relevant to each other that encode the enzyme \r \n "); 
}

    
    //dynamic string length? how to? 
 
    char start_strand[100]; 


  printf("Enter a strand: \n");
  scanf("%s",start_strand);

    int ii = 0;
    while(start_strand[ii] != '\0'){
      // If the string only contains A, G, T, C or the terminating character: 
     if(start_strand[ii] == 'A' || start_strand[ii] == 'C' || start_strand[ii] == 'G' || start_strand[ii] == 'T' || start_strand[ii] == '\0'){
       ii++;
       } else{
          printf(" Sorry, strands can only consist of A, G, T, or C! \n \r");
          printf(" Please Enter a new strand: \r \n");
          scanf("%s", start_strand);
      } 
    }
  
    printf(" Your strand is: %s \r \n", start_strand);
    printf("\n");
    printf(" Decoding Enzymes: \r \n");
    printf("\n");

   
    starting_base(start_strand);
 
  return 0;
}