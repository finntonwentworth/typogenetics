#include "strand_def.h"

/* ------ FUNCTION ------*/ 
/*
 * Performs general action of moving the enzymes position, and copy mode functionailty
 * 
 * Sub instruction called as a part of move commands, like mvr/mvl or searches. Also handles copy functionality
 * 
 *   boundStrand |  moveDirection | increment or decrement
 *   ----------------------------------------------------
 *    0 (main)   |   0 (right)    |         +
 *    0 (main)   |   1 (left)     |         -
 *    1 (comp)   |   0 (right)    |         -
 *    1 (comp)   |   1 (left)     |         +
 *
 * Accepts:  
 * current enzyme position,
 * currently bound strand flag 
 * Returns: 
 * int of newly bound position 
 * 
*/


void  move_subInstruction(struct strand *strandPointer, int moveDirection) {

    switch (strandPointer->boundStrandFlag) {
        case 0:
        switch (moveDirection) {
            case 0:
                strandPointer->currentBoundPosition += 1; 
                break;
            case 1:
                strandPointer->currentBoundPosition -= 1; 
                break; 
        }
        break;
        case 1:
        switch (moveDirection) {
            case 0:
                strandPointer->currentBoundPosition -= 1; 
                break;
            case 1:
                strandPointer->currentBoundPosition += 1; 
                break;
        }
        break;
    }
    switch (strandPointer->copyModeFlag) {
        case 1:
            switch (strandPointer->boundStrandFlag) {
                case 0:
                    switch (strandPointer->mainStrand[strandPointer->currentBoundPosition]) {
                        case 'A':
                            strandPointer->complementaryStrand[strandPointer->currentBoundPosition] = 'T';
                            break;
                        case 'T':
                            strandPointer->complementaryStrand[strandPointer->currentBoundPosition] = 'A';
                            break;
                        case 'G':
                            strandPointer->complementaryStrand[strandPointer->currentBoundPosition] = 'C';
                            break;
                        case 'C':
                            strandPointer->complementaryStrand[strandPointer->currentBoundPosition] = 'G';
                            break;
                    }
                    break;
                case 1:
                    switch (strandPointer->complementaryStrand[strandPointer->currentBoundPosition]) {
                        case 'A':
                            strandPointer->mainStrand[strandPointer->currentBoundPosition] = 'T';
                            break;
                        case 'T':
                            strandPointer->mainStrand[strandPointer->currentBoundPosition] = 'A';
                            break;
                        case 'G':
                            strandPointer->mainStrand[strandPointer->currentBoundPosition] = 'C';
                            break;
                        case 'C':
                            strandPointer->mainStrand[strandPointer->currentBoundPosition] = 'G';
                            break;
                    }
                    break;

        default:
            break;
            }
    }
}
/* ------ FUNCTION ------*/ 
/*
 * performs copy mode function to be called when a base needs to be copied  
 *
 * Accepts:  
 * strand struct pointer
 * Returns: 
 * nothing 
 * 
*/
void copy_base_subInstruction(struct strand *strandPointer) {

}

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
  move_subInstruction(strandPointer, 0); 
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
    //Invert the bound strand flag. This will bind the enzyme to the opposite to the opposite strand
    strandPointer->boundStrandFlag = !strandPointer->boundStrandFlag;
}

/* ------ FUNCTION ------*/ 
/*
 * Performs mvr amino acid functionality 
 * moves the enzyme one unit to the right on mainStrand 
 * and one unit left on complementary strand
 *
 * Accepts:  
 * struct pointer of type strand 
 * Returns: 
 * nothing 
 * 
*/
void mvr_acid(struct strand *strandPointer) {
    move_subInstruction(strandPointer, 0); 
}
/* ------ FUNCTION ------*/ 
/*
 * Performs mvl amino acid functionality 
 * moves the enzyme one unit to the left 
 * and one unit right on complementary strand
 *
 * Accepts:  
 * struct pointer of type strand 
 * Returns: 
 * nothing 
 * 
*/
void mvl_acid(struct strand *strandPointer) {
    move_subInstruction(strandPointer, 1); 
}
/* ------ FUNCTION ------*/ 
/*
 * Performs cop amino acid functionality 
 * Strand turns on copy mode- sets a flag in the struct
 * other functions handle inserting complementary bases
 *
 * Accepts:  
 * struct pointer of type strand 
 * Returns: 
 * nothing 
 * 
*/
void cop_acid(struct strand *strandPointer) {
    strandPointer->copyModeFlag = 1;
    copy_base_subInstruction(strandPointer); 
}
/* ------ FUNCTION ------*/ 
/*
 * Performs cop amino acid functionality 
 * Strand turns off copy mode- sets a flag in the struct
 *
 * Accepts:  
 * struct pointer of type strand 
 * Returns: 
 * nothing 
 * 
*/
void off_acid(struct strand *strandPointer) {
    strandPointer->copyModeFlag = 0;
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
            mvr_acid(userStrandPointer);
            break;
        case 5:
            mvl_acid(userStrandPointer);
            break;
        case 6:
            cop_acid(userStrandPointer);
            break;
        case 7:
            off_acid(userStrandPointer);
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

