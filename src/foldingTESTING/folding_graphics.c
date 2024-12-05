#include <stdio.h>
#include <unistd.h>
#include "../strand_def.h"
#include "folding_graphics.h"

int main() {
    const struct decodedStrand userDecode = {
                                        .foldingPattern = "rrsssssrsrss",
                                        .foldingPatternSize = 12,
                                        .instruction = {2,3,4,5,6,7,8,4,10,11,12,13}
                                      };
    //start at middle of grid by initializing '-' as last direction
    struct sprite cell = {
                          .lastFacingDirection = '-',
                         };

    const struct decodedStrand *decodedPointer = &userDecode; 
    struct sprite *spritePointer = &cell;  
    //the 2D array of cells
    // allows me to populate cells plus an offset
    char theGrid[GRID_DIMENSION*CELL_HEIGHT][GRID_DIMENSION*CELL_WIDTH];

    //start after the first element since we print that one facing right at 3,3
    fill_with_spaces(theGrid,spritePointer); 
    for(int i = 0; i < decodedPointer->foldingPatternSize-1; i++) {
//       spritePointer = determine_next_folding_sprite(decodedPointer->instruction[i],decodedPointer->foldingPattern[i],spritePointer);
       spritePointer = determine_next_folding_sprite(userDecode.instruction[i],userDecode.foldingPattern[i],spritePointer);
       if(check_screen_refresh(spritePointer) == 1) {
           fill_with_spaces(theGrid,spritePointer);
           print_grid(theGrid);
       }
       populate_cell(theGrid,spritePointer); 
       printf("placing element at : %d,%d\n", spritePointer->elementColumn, spritePointer->elementRow);
       print_grid(theGrid);
       sleep(1);
    }

    return 0; 

}



