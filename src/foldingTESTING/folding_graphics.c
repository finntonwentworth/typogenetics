#include <stdio.h>
#include <string.h>
#include "../strand_def.h"
#include "folding_graphics.h"

/*
 *           A           B           C            D             E            F           G     
 *      ---------------------------------------------------------------------------------------
 *     |1          |           |           |             |             |           |           |
 *  1  |2          |           |           |             |             |           |           |
 *     |3          |           |           |             |             |           |           |
 *      4--------------------------------------------------------------------------------------
 *     |5          |           |           |             |             |           |           |
 *  2  |6          |           |           |             |             |           |           |
 *     |7          |           |           |             |             |           |           |
 *      8--------------------------------------------------------------------------------------
 *     |9          |           |           |             |             |           |           |
 *  3  |10         |           |           |             |             |           |           |
 *     |11         |           |           |             |             |           |           |
 *      12-------------------------------------------------------------------------------------
 *     |13         |           |           |             |             |           |           |
 *  4  |14         |           |           |    START    |             |           |           |
 *     |15         |           |           |             |             |           |           |
 *      16-------------------------------------------------------------------------------------
 *     |17         |           |           |             |             |           |           |
 *  5  |18         |           |           |             |             |           |           |
 *     |19         |           |           |             |             |           |           |
 *      20-------------------------------------------------------------------------------------
 *     |21         |           |           |             |             |           |           |
 *  6  |22         |           |           |             |             |           |           |
 *     |23         |           |           |             |             |           |           |
 *      24-------------------------------------------------------------------------------------
 *     |25         |           |           |             |             |           |           |
 *  7  |26         |           |           |             |             |           |           |
 *     |27         |           |           |             |             |           |           |
 *      28-------------------------------------------------------------------------------------
 *
 *
 *
 *
 *
 */









int main() {
    struct decodedStrand userDecode = {
                                        .foldingPattern = "rl",
                                        .instruction = {6,6}
                                      };
    struct sprite cell;
    struct decodedStrand *decodedPointer = &userDecode; 
    struct sprite *spritePointer = &cell;  
    //the 2D array of cells
    // allows me to populate cells plus an offset
    char theGrid[GRID_DIMENSION*CELL_HEIGHT][GRID_DIMENSION*CELL_WIDTH];

    for(int i = 0; i <= decodedPointer->foldingPatternSize; i++) {
       populate_cell(theGrid,  determine_next_folding_sprite(&decodedPointer->instruction[i],&decodedPointer->foldingPattern[i],spritePointer));
    }

    print_grid(theGrid);
    return 0; 

}



