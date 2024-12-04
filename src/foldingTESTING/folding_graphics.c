#include <stdio.h>
#include <unistd.h>
#include "../strand_def.h"
#include "folding_graphics.h"

int main() {
    struct decodedStrand userDecode = {
                                        .foldingPattern = "rlll",
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

    spritePointer->elementRow = 0;
    spritePointer->elementColumn = 0;
    for(int i = 0; i <=49; i++) {
        poopulate_cell(theGrid,spritePointer,'c'); 
        spritePointer->elementColumn += 1;
        if(spritePointer->elementColumn == 7) {
            spritePointer->elementColumn = 0;
            spritePointer->elementRow += 1;
        }
    }
/*
    spritePointer->elementColumn = 4;
    spritePointer->elementRow = 2;

    populate_cell(theGrid, determine_next_folding_sprite(decodedPointer->instruction[1],decodedPointer->foldingPattern[1],spritePointer));
    pwint_grid(theGrid);
*/
    //start after the first element since we print that one facing right at 3,3
    for(int i = 0; i < decodedPointer->foldingPatternSize; i++) {
       populate_cell(theGrid, determine_next_folding_sprite(decodedPointer->instruction[i],decodedPointer->foldingPattern[i],spritePointer));
       printf("lastFacingDirection is %c\n",spritePointer->lastFacingDirection);
       printf("cell populating at %d, %d\n", spritePointer->elementColumn,spritePointer->elementRow); 
       print_grid(theGrid);
       sleep(1);
    }

    return 0; 

}



