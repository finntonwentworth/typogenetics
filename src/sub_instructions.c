#include "strand_def.h"

/* ------ FUNCTION ------*/ 
/*
 * performs copy mode function to be called when a base needs to be copied  
 *
 * Accepts:  
 * strand struct pointer
 * Returns: 
 * nothing 
 *
 * 
*/
void copy_base_subInstruction(struct strand *strandPointer, int insertIndex) {
    if(strandPointer->boundStrandFlag == 0) {
        switch(strandPointer->mainStrand[insertIndex]) {
            case 'A':
                strandPointer->complementaryStrand[insertIndex] = 'T';
                break;
            case 'T':
                strandPointer->complementaryStrand[insertIndex] = 'A';
                break;
            case 'G':
                strandPointer->complementaryStrand[insertIndex] = 'C';
                break;
            case 'C':
                strandPointer->complementaryStrand[insertIndex] = 'G';
                break;
        }
        //if the current bound position is greater than the size of the strand being copied to, 
        //set the size to be the current bound position
        //size does not care about spaces, just the furthest element slot occupied.
        if(strandPointer->currentBoundPosition > strandPointer->complementarySize) { 
            strandPointer->complementarySize = strandPointer->currentBoundPosition; 
        }
    } else {
        switch (strandPointer->complementaryStrand[insertIndex]) {
            case 'A':
                strandPointer->mainStrand[insertIndex] = 'T';
                break;
            case 'T':
                strandPointer->mainStrand[insertIndex] = 'A';
                break;
            case 'G':
                strandPointer->mainStrand[insertIndex] = 'C';
                break;
            case 'C':
                strandPointer->mainStrand[insertIndex] = 'G';
                break;
        }

        //if the current bound position is greater than the size of the strand being copied to, 
        //set the size to be the current bound position
        //size does not care about spaces, just the furthest element slot occupied.
        if(strandPointer->currentBoundPosition > strandPointer->mainSize) { 
            strandPointer->mainSize = strandPointer->currentBoundPosition; 
        }
    }
}

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
            copy_base_subInstruction(strandPointer, strandPointer->currentBoundPosition-1);
            break;
        default:
            break;
            }
    }

/* ------ FUNCTION ------*/ 
/*
 * performs insert mode function to be called when a base needs to be inserted  
 *
 * Accepts:  
 * strand struct pointer, char to be inserted 
 * Returns: 
 * nothing 
 *
 * 
*/
void insert_base_subInstruction(struct strand *strandPointer, char base) {
   //if on the main strand  
   if(strandPointer->boundStrandFlag == 0) {
       for(int i = strandPointer->mainSize-1; i >= strandPointer->currentBoundPosition; i--) {
           //move each element one space up
           strandPointer->mainStrand[i+1] = strandPointer->mainStrand[i];
       }
       //set the element to the right of the bound position equal to the inserted base
       strandPointer->mainStrand[strandPointer->currentBoundPosition] = base; 
       //increase the size of the strand by 1 
       strandPointer->mainSize += 1; 
       //also insert a blank into the complementary strand
       for(int i = strandPointer->complementarySize; i >= strandPointer->currentBoundPosition; i --) {
           strandPointer->complementaryStrand[i] = strandPointer->complementaryStrand[i-1];
       } 
       if(strandPointer->copyModeFlag == 1) {
           copy_base_subInstruction(strandPointer, strandPointer->currentBoundPosition); 
       } else {
           strandPointer->complementaryStrand[strandPointer->currentBoundPosition] = ' '; 
       }
       strandPointer->complementarySize += 1; 
   //if on the complementary strand 
   } else {
       // THIS SHIT DONT WORK SO GOOD 
       //
       //
       //
       for(int i = strandPointer->complementarySize; i >= strandPointer->currentBoundPosition; i--) {
           //shift everything up one 
           strandPointer->complementaryStrand[i] = strandPointer->complementaryStrand[i-1];
       }
       strandPointer->complementaryStrand[strandPointer->currentBoundPosition-1] = base;
       strandPointer->complementarySize +=1;
       strandPointer->currentBoundPosition +=1;
       //now insert 
       for(int i = strandPointer->mainSize; i >= strandPointer->currentBoundPosition; i--) {
           //move each element one space up
           strandPointer->mainStrand[i+1] = strandPointer->mainStrand[i];
       }
/*
       if(strandPointer->copyModeFlag == 1) {
           copy_base_subInstruction(strandPointer, strandPointer->currentBoundPosition-3); 
       } else {
*/
           strandPointer->mainStrand[strandPointer->currentBoundPosition-2] = ' '; 
//       }
       strandPointer->mainSize += 1; 
   }

}
