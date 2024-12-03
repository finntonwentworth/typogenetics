#include <stdio.h>
#include <string.h>
#include "../strand_def.h"
#include "folding_graphics.h"

int main() {
    struct decodedStrand userDecode = {
                                        .foldingPattern = "rlsl",
                                        .foldingPatternSize = 4,
                                        .instruction = {2,3,4,5}
                                      };
    //start at position 3,3
    struct sprite cell = {
                          .lastFacingDirection = '-',
                          .testElement = 0
                         };

    struct decodedStrand *decodedPointer = &userDecode; 
    struct sprite *spritePointer = &cell;  
    //the 2D array of cells
    // allows me to populate cells plus an offset
    char theGrid[GRID_DIMENSION*CELL_HEIGHT][GRID_DIMENSION*CELL_WIDTH];

    //start after the first element since we print that one facing right at 3,3
    for(int i = 0; i < decodedPointer->foldingPatternSize; i++) {
       populate_cell(theGrid, determine_next_folding_sprite(decodedPointer->instruction[i],decodedPointer->foldingPattern[i],spritePointer));
       spritePointer->testElement +=1;
       printf("lastFacingDirection is %c\n",spritePointer->lastFacingDirection);
       printf("cell populating at %d, %d\n", spritePointer->elementRow, spritePointer->elementColumn); 
    }

    print_grid(theGrid);
    return 0; 

}



