#include "enzymefunctions.c"

#define MAX_STRAND_SIZE     1000

struct strand {
  char dnastrand[MAX_STRAND_SIZE]; 
  int  size; 
};


int relevant_elements(char[]);
int valid_strand(char[], int); 
struct decodedstrand get_instructions_and_folding(char[], int);
char calculate_starting_base(char[], int);
int *matching_starting_base_elements(char[],int,char); 
char *current_enzyme_position(int);
void call_instruction(int);
