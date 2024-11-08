
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
  printf(" AA: pun (-) | AC: cut (s) | AG: del (s) | AT: swi (r)\n \r");
  printf(" --------------------------------------------------- \n \r");
  printf(" CA: mvr (s) | CC: mvl (s) | CG: cop (r) | CT: off (l)\n \r");
  printf(" --------------------------------------------------- \n \r");
  printf(" GA: ina (s) | GC: inc (r) | GG: ing (r) | GT: int (l) \n \r");
  printf(" --------------------------------------------------- \n \r");
  printf(" TA: rpy (r) | TC: rpu (l) | TG: lpy (l) | TT: lpu (l) \n \r");
  printf(" \n");

  printf(" 3. Each instruction 'folds' the enzyme in a specific way, with the direction straight(s), left(l), or right(r) \n \r");
  printf(" (AA is a 'punctutation mark' acting to split the enzyme into 2 or more separate enzymes) \n \r");
  printf(" 4. Each enzyme will begin acting on a specfic base in your strand based on the starting and ending bases orientation relevant to each other that encode the enzyme \n \r "); 

  struct user_strand strand; 

  printf("Enter a strand: \n");
  scanf("%s",strand.dna_strand);
  //Check that the user's strand is valid/ 'well formed'
  while(validstrand(strand.dna_strand)!=1){
        printf(" Sorry, strands can only consist of A, G, T, or C! \n \r");
        printf(" Please Enter a new strand: \r \n");
        scanf("%s",strand.dna_strand);
  }


  printf(" Your strand is: %s \n \r", strand.dna_strand);
  printf("\n");
  printf(" Decoding Enzymes: \n \r");
  printf("\n");
  printf("Function returns %s", determinefoldingpattern(strand.dna_strand));
  strcpy(strand.folding_pattern,determinefoldingpattern(strand.dna_strand));
  // I would like to assign the folding pattern determined in this function to the 
  // folding_pattern element of user_struct
  //strcpy(starting_base(strand.dna_strand,strand.folding_pattern),strand.folding_pattern);
  printf("test point 2\n");
  printf("Folding structure is: %s \n \r",strand.folding_pattern);
}
