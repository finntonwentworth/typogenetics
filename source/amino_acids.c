#include "strand_def.h"

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
    // do this again but for the complementary strand
    strandPointer->outputStrandCount +=1; 
    j = 0; 
    for(int i = strandPointer->complementarySize; i >= strandPointer->currentBoundPosition; i--){
       strandPointer->outputStrand[strandPointer->outputStrandCount][j] = strandPointer->complementaryStrand[i];
       strandPointer->complementaryStrand[i] = ' '; 
       j++;  
    }
    // ?? DOES THIS MAKE SENSE ?? 
    // if i don't arbitrarily set the size of the complementary base I think its fine, i.e. in real applications
    // now the strand is the size of the number of elements up to the bound position
    // come back to this line
   //    strandPointer->mainSize =  strandPointer->complementarySize = strandPointer->currentBoundPosition;
    if(strandPointer->currentBoundPosition <= strandPointer->mainSize) {
        strandPointer->mainSize = strandPointer->currentBoundPosition;
    }
    if(strandPointer->currentBoundPosition <= strandPointer->complementarySize) {
        strandPointer->complementarySize = strandPointer->currentBoundPosition;
    }

}

/* ------ FUNCTION ------*/ 
/*
 * Performs del amino acid functionality 
 * Deletes base underneath currently bound position, leaving a gap, and moves to the base to the right
 * 
 *
 * Accepts:  
 * struct pointer of type strand 
 * Returns: 
 * nothing 
 * 
*/
void del_acid(struct strand *strandPointer) {
  //if currently bound to main strand, del that bound base 
  if(strandPointer->boundStrandFlag == 0) {
     strandPointer->mainStrand[strandPointer->currentBoundPosition-1] = ' ';
  // else del the bound base on the complementary strand
  } else {
     strandPointer->complementaryStrand[strandPointer->currentBoundPosition-1] = ' ';
  }
  //move one base to the right
  strandPointer->currentBoundPosition++;
}
/* ------ FUNCTION ------*/ 
/*
 * Performs swi amino acid functionality 
 * switches from main strand to complementary, or vice versa  
 *
 * Accepts:  
 * struct pointer of type strand 
 * Returns: 
 * nothing 
 * 
*/
void swi_acid(struct strand *strandPointer) {
    strandPointer->boundStrandFlag = !strandPointer->boundStrandFlag;
}

/* ------ FUNCTION ------*/ 
/*
 * Function serves to call any of the "15" enzyme functions provided an instruction number 
 * Calls function 
 *
 * Accepts:  
 * int instruction number, strand struct pointer
 * Returns: 
 * nothing
 * 
*/
void call_instruction(int instructionnumber, struct strand *userStrandPointer) {
    switch (instructionnumber){
        case 1:
            cut_acid(userStrandPointer);
            break;
        case 2:
            del_acid(userStrandPointer);
            break;
        case 3:
            swi_acid(userStrandPointer);
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

