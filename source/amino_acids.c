
#define MAX_STRAND_SIZE         1000

struct strand {
  char dnaStrand[MAX_STRAND_SIZE]; 
  int  size; 
  char outputStrand[MAX_STRAND_SIZE][MAX_STRAND_SIZE]; 
};
/* ------ FUNCTION ------*/ 
/*
 * Performs cut amino acid functionality 
 * Cuts the strand to the right of the current acting position
 * 
 *
 * Accepts:  
 * current enzyme position,
 * current form of dna strand 
 * Returns: 
 * struct strand 
 * so that it can write to the output strand 
 * 
*/

struct strand cut_acid(int currentEnzymePosition, struct strand userStrand){
        

    return userStrand; 
}

/* ------ FUNCTION ------*/ 
/*
 * Function serves to call any of the "15" enzyme functions provided an instruction number 
 * Calls function 
 *
 * Accepts:  
 * int instruction number   
 * This will need to accept the strand string as well i think 
 * Returns: 
 * nothing
 * and return the strand struct to easily returned the changed string
 * 
*/
struct strand call_instruction(int instructionnumber, struct strand userStrand) {
    switch (instructionnumber){
        case 1:
            cut_acid();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
            break;
        case 13:
            break;
        case 14:
            break;
        case 15:
            break;
        default:
            break;
    }
}

