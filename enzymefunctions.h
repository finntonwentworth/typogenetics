#include "enzymefunctions.c"

#define MAX_STRAND_SIZE     1000

struct strand {
  char dnastrand[MAX_STRAND_SIZE]; 
  int size; 
  char startingoffset[MAX_STRAND_SIZE];  
};


int relevant_elements(char[]);
int valid_strand(char[], int); 
struct decodedstrand determine_folding(char[], int);


