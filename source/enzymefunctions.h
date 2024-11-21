#include "enzymefunctions.c"
#include "rand_strand_function.c"
#include "amino_acids.c"

#define MAX_STRAND_SIZE     1000

struct strand {
  char dnaStrand[MAX_STRAND_SIZE]; 
  int  size; 
  char outputStrand[MAX_STRAND_SIZE][MAX_STRAND_SIZE]; 
};

/*--- Enzyme Function ---*/
int relevant_elements(char[]);
int valid_strand(char[], int); 
struct decodedStrand get_instructions_and_folding(char[], int);
char calculate_starting_base(char[], int, int);
int *matching_starting_base_elements(char[],int,char); 
char *current_enzyme_position(int, int);

/*--- Rand Strand ---*/
char *rand_strand(int);

/*--- Amino Acids---*/
void call_instruction(int);
