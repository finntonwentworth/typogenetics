#include "rand_strand_function.c"
#include "utility_functions.c"
#include "amino_acids.c"


/*--- Utility Functions ---*/
int relevant_elements(char[]);
int valid_strand(char[], int); 
struct decodedStrand get_instructions_and_folding(char[], int);
char calculate_starting_base(char[], int, int);
int *matching_starting_base_elements(char[],int,char); 
char *current_enzyme_position(struct strand*,int);
void strand_splitter(struct strand*);

/*--- Rand Strand ---*/
char *rand_strand(int);

/*--- Amino Acids---*/
void cut_acid(struct strand*); 
void del_acid(struct strand*); 
void swi_acid(struct strand*); 
void mvr_acid(struct strand*);
void mvl_acid(struct strand*);
void cop_acid(struct strand*);
void off_acid(struct strand*);
void ina_acid(void);
void inc_acid(void);
void ing_acid(void);
void int_acid(void);
void rpy_acid(void);
void rpu_acid(void);
void lpu_acid(void);
void lpy_acid(void);
void call_instructions(int, struct strand*); 
void move_subInstruction(struct strand*, int);

