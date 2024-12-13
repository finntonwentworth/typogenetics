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
    
    // TESTING 
    // trying to eliminate screen scroll when printing pattern
    //move up one row 
       printf("\x1B[1A");
    // set save point
       printf("\x1B[s");
       print_grid(theGrid);
    // return to save point
       printf("\x1B[u");
       patternIndex++;
       sleep(1);
    }
  //jump down one grid 
  printf("\x1B[99B");
  return patternIndex;
}
