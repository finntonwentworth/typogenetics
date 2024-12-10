
#include <stdio.h>
#include <unistd.h>
#include "../strand_def.h"
#include "folding_graphics.h"


void enzyme_folding(struct decodedStrand userDecode) {
  struct sprite cell = {
                        .lastFacingDirection = '-',
                       };

  struct decodedStrand *decodedPointer = &userDecode; 
  struct sprite *spritePointer = &cell;  
  //the 2D array of cells
  // allows me to populate cells plus an offset
  char theGrid[GRID_DIMENSION*CELL_HEIGHT][GRID_DIMENSION*CELL_WIDTH];
  fill_with_spaces(theGrid,spritePointer); 
  for(int i = 0; i < decodedPointer->foldingPatternSize; i++) {
       spritePointer = determine_next_folding_sprite(userDecode.instruction[i],userDecode.foldingPattern[i],spritePointer);
       if(check_screen_refresh(spritePointer) == 1) {
           fill_with_spaces(theGrid,spritePointer);
       }
       populate_cell(theGrid,spritePointer); 
       printf("placing element at : %d,%d\n", spritePointer->elementColumn, spritePointer->elementRow);
       print_grid(theGrid);
       sleep(1);
    }
  //just print at end for the test
  //  print_grid(theGrid);
}
