#include <unistd.h>
#include "../strand_def.h"
#include "folding_graphics.h"


int enzyme_folding(struct decodedStrand userDecode, int patternIndex) {
  struct sprite cell = {
                        .lastFacingDirection = '-',
                       };

  struct decodedStrand *decodedPointer = &userDecode; 
  struct sprite *spritePointer = &cell;  
  //the 2D array of cells
  // allows me to populate cells plus an offset
  char theGrid[GRID_DIMENSION*CELL_HEIGHT][GRID_DIMENSION*CELL_WIDTH];
  fill_with_spaces(theGrid,spritePointer); 
//  for(int i = 0; i < foldingIndex; i++) {
    while(patternIndex < userDecode.foldingPatternSize) {
       if(userDecode.instruction[patternIndex] == 0) {
         patternIndex++;
         break;
       }
       spritePointer = determine_next_folding_sprite(userDecode.instruction[patternIndex],userDecode.foldingPattern[patternIndex],spritePointer); 
       if(check_screen_refresh(spritePointer) == 1) {
           fill_with_spaces(theGrid,spritePointer);
       }
       populate_cell(theGrid,spritePointer); 
       print_grid(theGrid);
       patternIndex++;
       sleep(1);
    }
  return patternIndex;
}
