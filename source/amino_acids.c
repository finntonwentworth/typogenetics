#define MAX_STRAND_SIZE         1000

/* ----- STRAND ----- */
/*
 * Strands are represented as structs which hold useful metadata about the strand
 *
 * maybe needs marker for the currently upright strand? 
 * 1 = mainStrand 
 * 0 = complementaryStrand 
 *
 * or just strcpy swap them each time? 
 *
 * mainStrand: holds the currently acted upon strand 
 * complementaryStrand: array to hold copied elements 
 * size: # of relevant elements in the strand for loops 
 * currentBoundPosition: int representing what element the enzyme is bound to 
 * outputStrandCount: Counter for printing the end strands if they are subdivided/ copied 
 * ouputStrand: 2-D array holding the input, active, and all remaining generated strands 
 */
struct strand {
  char mainStrand[MAX_STRAND_SIZE]; 
  char complementaryStrand[MAX_STRAND_SIZE];
  int  boundStrandFlag; //0 = mainStrand ; 1 = complementaryStrand
  int  mainSize; 
  int  complementarySize;
  int  currentBoundPosition; 
  int  outputStrandCount;
  char outputStrand[MAX_STRAND_SIZE/2][MAX_STRAND_SIZE/2]; 
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
void cut_acid(struct strand *strandPointer)
{
    int j = 0;
    //increase output count by 1, for mainStrand 
    strandPointer->outputStrandCount +=1; 
    //from the currently bound position to the end of the strand 
    //write that section of the strand to the output 

    for(int i = strandPointer->currentBoundPosition; i < strandPointer->mainSize; i++){
       strandPointer->outputStrand[strandPointer->outputStrandCount][j] = strandPointer->mainStrand[i];
       //set the element we just cut equal to zero
       strandPointer->mainStrand[i] = ' '; 
       j++;  
    }        

    strandPointer->outputStrandCount +=1; 
    j = 0; 
    for(int i = strandPointer->complementarySize; i >= strandPointer->currentBoundPosition; i--){
       strandPointer->outputStrand[strandPointer->outputStrandCount][j] = strandPointer->complementaryStrand[i];
       strandPointer->complementaryStrand[i] = ' '; 
       j++;  
    }
    // now the strand is the size of the number of elements up to the bound position
    strandPointer->complementarySize = strandPointer->mainSize = strandPointer->currentBoundPosition;
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
void call_instruction(int instructionnumber, struct strand *userStrandPointer) {
    switch (instructionnumber){
        case 1:
            cut_acid(userStrandPointer);
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

