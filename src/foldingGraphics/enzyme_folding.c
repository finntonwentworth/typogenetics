#include <unistd.h>
#include "../strand_def.h"
#include "folding_graphics.h"

#define JUMPHOME      "\x1B[H"
#define JUMPUP9       "\x1B[9A"
#define MOVEUPROW     "\x1B M"
#define MOVEUPONEROW  "\x1B[1A"
#define CLEARSCRN     "\x1B[2J"
#define CLEARTOEND    "\x1B[0J"

int enzyme_folding(struct decodedStrand userDecode, int patternIndex) {
  struct sprite cell = {
                        .lastFacingDirection = '-',
                       };

  struct decodedStrand *decodedPointer = &userDecode; 
  struct sprite *spritePointer = &cell;  
  //the 2D array of cells
  // allows me to populate cells plus an offset
  char theGrid[GRID_DIMENSION*CELL_HEIGHT][GRID_DIMENSION*CELL_WIDTH];
  fill_with_spaces(theGrid); 
  while(patternIndex < userDecode.foldingPatternSize) {
      if(userDecode.instruction[patternIndex] == 0) {
         patternIndex++;
         break;
       }
       spritePointer = determine_next_folding_sprite(userDecode.instruction[patternIndex],userDecode.foldingPattern[patternIndex],spritePointer); 
       if(check_screen_refresh(spritePointer) == 1) {
           fill_with_spaces(theGrid);
       }
       populate_cell(theGrid,spritePointer); 
    
    // TESTING 
    // trying to eliminate screen scroll when printing pattern
//       printf(CLEARSCRN);
//       printf(JUMPHOME);
    for(int i = 0; i < GRID_DIMENSION*CELL_HEIGHT; i++) {
      printf(MOVEUPONEROW);
    }

//       printf(CLEARTOEND);
       print_grid(theGrid);
       patternIndex++;
       usleep(500000);
    }
  //jump down one grid 
  return patternIndex;
}
