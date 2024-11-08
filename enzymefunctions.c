
#include <stdio.h>
#include <string.h>


#define STRAND_SIZE     1000

// and pulls base pair elements
int validstrand(char strand[]) {
    int ii = 0;
    while(strand[ii] != '\0'){
       // If the string only contains A, G, T, C or the terminating character: 
       if(strand[ii] == 'A' || strand[ii] == 'C' || strand[ii] == 'G' || strand[ii] == 'T' || strand[ii] == '\0'){
         ii++;
         }else{
            return 0;
         } 
    }
    return 1;
}


// Starting Base function's goal:

// Determine base pairs for corresponding instruction, then determine folding structure to determine the starting base 
//store the instructions for the enzymes of the strand so that they can be referenced later
// ^ or maybe just re scan the strand for determing instructions in the next function I write 

//NEXT GOAL FOR FUNCTION:
//Begin determining starting base, i.e. folding structure 
// eventually do ascii graphics but thats a far ways away

//void starting_base(char strand[1000],char folding_structure[1000]){
//void starting_base(struct user_strand strand) {
const char *determinefoldingpattern(char strand[]){
// counter and variables for the bases 
 int ii = 0;
 char firstbase, secondbase; 
 char folding_structure[1000]; 
 int kk = 0; 


  
  // for each valid element in the strand 
  while(strand[ii] == 'A' || strand[ii] == 'G' || strand[ii] == 'T' || strand[ii] == 'C'){
  //   set the base variables equal to the element
    firstbase = strand[ii];
    secondbase = strand[ii+1];
  //  if there is an odd numbered of bases in strand 
    if(secondbase == '\0'){
      // print last base by itself rather than check instruction
      printf(" Last base is: %c \r \n", firstbase);  
      break;
    }

    // print base pair 
    printf(" Bases are: %c%c \r \n", firstbase, secondbase);
    // nested switch checks pair and determines corresponding instruction
    switch (firstbase) {
      case 'A':
        switch(secondbase){
          case 'A':
            printf(" Corresponding instruction is: pun\r \n");
            break;
          case 'C':
            printf(" Corresponding instruction is: cut\r \n");
            folding_structure[kk] = 's'; 
            break;
          case 'G':
            printf(" Corresponding instruction is: del\r \n");
            folding_structure[kk] = 's'; 
            break;
          case 'T':
            printf(" Corresponding instruction is: swi\r \n");
            folding_structure[kk] = 'r'; 
            break;
        }
        break;
      case 'C':
        switch(secondbase){
          case 'A':
            printf(" Corresponding instruction is: mvr\r \n");
            folding_structure[kk] = 's'; 
            break;
          case 'C':
            printf(" Corresponding instruction is: mvl\r \n");
            folding_structure[kk] = 's'; 
            break;
          case 'G':
            printf(" Corresponding instruction is: cop\r \n");
            folding_structure[kk] = 'r'; 
            break;
          case 'T':
            printf(" Corresponding instruction is: off\r \n");
            folding_structure[kk] = 'l'; 
            break;
        }
      break;
      case 'G':
        switch(secondbase){
          case 'A':
            printf(" Corresponding instruction is: ina\r \n");
            folding_structure[kk] = 's'; 
            break;
          case 'C':
            printf(" Corresponding instruction is: inc\r \n");
            folding_structure[kk] = 'r'; 
            break;
          case 'G':
            printf(" Corresponding instruction is: ing\r \n");
            folding_structure[kk] = 'r'; 
            break;
          case 'T':
            printf(" Corresponding instruction is: int\r \n");
            folding_structure[kk] = 'l'; 
            break;
        }
      break;
      case 'T':
        switch(secondbase){
          case 'A':
            printf(" Corresponding instruction is: rpy\r \n");
            folding_structure[kk] = 'r'; 
            break;
          case 'C':
            printf(" Corresponding instruction is: rpu\r \n");
            folding_structure[kk] = 'l'; 
            break;
          case 'G':
            printf(" Corresponding instruction is: lpy\r \n");
            folding_structure[kk] = 'l'; 
            break;
          case 'T':
            printf(" Corresponding instruction is: lpu\r \n");
            folding_structure[kk] = 'l'; 
            break;
        }
        break;
    }
    //move to next pair of bases in strand 
    ii = ii +2;
    // move to the next folding element 
    kk++; 


    } // end of 'while'

  folding_structure[0] = 'r';
  folding_structure[999] = '\0';
  printf("test point 1\n");  
  return folding_structure; 

  }// end of function
   
// FUNCTION PURPOSE 
// determine the starting acting point of the enzyme on the strand and place the
// a ^ where the start is 
/*
char calculate_start(char strand[]) {
}

const char* determinefolding(char strand[1000]) {

}
*/
