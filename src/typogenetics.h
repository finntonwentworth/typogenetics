#include "rand_strand_function.c"
#include "utility_functions.c"
#include "amino_acids.c"
#include "print_splash.c"
#include "foldingGraphics/enzyme_folding.c"

/*--- Print Splash Art ---*/
void print_splash(void);

/*--- Utility Functions ---*/
int relevant_elements(char[]);
int valid_strand(char[], int); 
struct decodedStrand get_instructions_and_folding(char[], int);
char calculate_starting_base(char[], int, int);
int *matching_starting_base_elements(char[],int,char); 
char *current_enzyme_position(struct strand*,int);
void strand_splitter(struct strand*);
int  check_falling_off(struct strand*); 
void wait_for_user(void);
struct strand init_user_strand(char[], int); 
struct decodedStrand init_decoded_strand(void);

/*--- Rand Strand ---*/
char *rand_strand(int);


/*--- Folding Graphics ---*/
int enzyme_folding(struct decodedStrand, int);


/*--- Amino Acids---*/
void cut_acid(struct strand*); 
void del_acid(struct strand*); 
void swi_acid(struct strand*); 
void mvr_acid(struct strand*);
void mvl_acid(struct strand*);
void cop_acid(struct strand*);
void off_acid(struct strand*);
void ina_acid(struct strand*);
void inc_acid(struct strand*);
void ing_acid(struct strand*);
void int_acid(struct strand*);
void rpy_acid(struct strand*);
void rpu_acid(struct strand*);
void lpy_acid(struct strand*);
void lpu_acid(struct strand*);
void call_instructions(int, struct strand*); 

/*--- Sub Instructions ---*/
void move_subInstruction(struct strand*, int);
void copy_base_subInstruction(struct strand*, int); 
void insert_base_subInstruction(struct strand*, char); 
