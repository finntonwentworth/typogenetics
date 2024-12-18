#include <stdio.h>
#include <unistd.h>
#include "sprites.h"

/* ------ FUNCTION ------*/ 
/*
 * Prints the total grid
 *
 * Accepts: 2D array 'Grid'
 * Returns: 
 * nothing
*/
void print_grid(char grid[][CELL_WIDTH*GRID_DIMENSION]) {
    //print down each row
    for(int i = 0; i <(CELL_HEIGHT * GRID_DIMENSION); i++) {
        printf("\t\t\t");
        //print across for each row 
        for(int j = 0; j <(CELL_WIDTH * GRID_DIMENSION); j++) {
            printf("%c",grid[i][j]);

        }
        if(i == (CELL_HEIGHT * GRID_DIMENSION)) {
            break;
        } else {
            printf("\n"); 
        }
    }
}
/* ------ FUNCTION ------*/ 
/*
 * Fills grid elements with spaces
 *
 * Accepts: 2D array 'Grid'
 * Returns: 
 * nothing
*/
void fill_with_spaces(char grid[][CELL_WIDTH*GRID_DIMENSION]) {
    for(int i = 0; i <(CELL_HEIGHT * GRID_DIMENSION); i++) {
        for(int j = 0; j <(CELL_WIDTH * GRID_DIMENSION); j++) {
            grid[i][j] = ' ';
        }
    }
}
/* ------ FUNCTION ------*/ 
/*
 * With an instruction, folding direction, and position, determines and writes the 
 * next sprite to sprite.element
 *
 * Accepts: instruction #, folding pattern direction, struct sprite 
 * Returns:  
 * pointer to sprite 
*/
struct sprite *determine_next_folding_sprite(int instruction, char foldingPattern, struct sprite *spritePointer) {
    int directionIndex;
    //instruction gives row 
    //folding letter and position determine column 
    // (ROW NUMBER)
    // 0  = pun (no sprite)
    // 1  = cut
    // 2  = del
    // 3  = swi
    // 4  = mvr
    // 5  = mvl
    // 6  = cop
    // 7  = off
    // 8  = ina 
    // 9  = inc
    // 10 = ing 
    // 11 = int 
    // 12 = rpy
    // 13 = rpu
    // 14 = lpy
    // 15 = lpu
    
    // (COLUMN NUMBER)
    //-  0 = up
    //-  1 = right
    //-  2 = down
    //-  3 = left
   switch(foldingPattern) {
       case 's':
           if(spritePointer->lastFacingDirection == 'U') {
               directionIndex = 0;
               spritePointer->elementRow -= 1;
           } else if(spritePointer->lastFacingDirection == 'R') {
               directionIndex = 1;
               spritePointer->elementColumn +=1;
           } else if(spritePointer->lastFacingDirection == 'D') {
               directionIndex = 2; 
               spritePointer->elementRow +=1;
           } else if(spritePointer->lastFacingDirection == 'L') {
               directionIndex = 3;
               spritePointer->elementColumn -=1;
           }
           break;
       case 'r':
           //if the sprite has no last facing direction, then it's the first element
           //i  dont think this will work with pun, unless I set the last facing direction to '-' on 
           //function entry
           if(spritePointer->lastFacingDirection == '-') {
               spritePointer->lastFacingDirection = 'R';
               directionIndex = 1;
               // set the starting position to the middle of the grid - assuming odd numbered grid 
               spritePointer->elementRow = (GRID_DIMENSION/2);
               spritePointer->elementColumn = (GRID_DIMENSION/2);

           } else if(spritePointer->lastFacingDirection == 'U') {
               spritePointer->lastFacingDirection = 'R';
               directionIndex = 1;
               spritePointer->elementRow -=1;
           } else if(spritePointer->lastFacingDirection == 'R') {
               spritePointer->lastFacingDirection = 'D';
               directionIndex = 2;
               spritePointer->elementColumn +=1;
           } else if(spritePointer->lastFacingDirection == 'D') {
               spritePointer->lastFacingDirection = 'L';
               directionIndex = 3; 
               spritePointer->elementRow +=1;
           } else if(spritePointer->lastFacingDirection == 'L') {
               spritePointer->lastFacingDirection = 'U';
               directionIndex = 0;
               spritePointer->elementColumn -=1;
           }
           break;
       case 'l':
           if(spritePointer->lastFacingDirection == 'U') {
               spritePointer->lastFacingDirection = 'L';
               directionIndex = 3;
               spritePointer->elementRow -=1;
           } else if(spritePointer->lastFacingDirection == 'R') {
               spritePointer->lastFacingDirection = 'U';
               directionIndex = 0;
               spritePointer->elementColumn +=1;
           } else if(spritePointer->lastFacingDirection == 'D') {
               spritePointer->lastFacingDirection = 'R';
               directionIndex = 1; 
               spritePointer->elementRow +=1;
           } else if(spritePointer->lastFacingDirection == 'L') {
               spritePointer->lastFacingDirection = 'D';
               directionIndex = 2;
               spritePointer->elementColumn -=1;
           }
           break;
       default:
           break;
   }
   for(int i = 0; i < CELL_HEIGHT; i++) {
       for(int j = 0; j < CELL_WIDTH; j++) {
           spritePointer->element[i][j] = spriteTable[directionIndex][instruction][i][j];
       }
   }

   return spritePointer; 
}

/* ------ FUNCTION ------*/ 
/*
 * Checks if the folding pattern has exceed the screen bounds and start drawing on a 
 * blank screen
 *
 * Accepts: spritePointer
 * Returns:  
 * 1 if the screen needs to  be refreshed
 * 0 if not
*/
int check_screen_refresh(struct sprite *spritePointer) {
   int screenRefreshFlag = 0;
   //overflow control - if we try to write to a space off the grid, shift to a new blank grid 
   if(spritePointer->elementRow > GRID_DIMENSION-1) {
       spritePointer->elementRow = 0;
       screenRefreshFlag = 1;
   } else if(spritePointer->elementRow < 0) {
       spritePointer->elementRow = GRID_DIMENSION-1; 
       screenRefreshFlag = 1;
   }
   if(spritePointer->elementColumn > GRID_DIMENSION-1) {
       spritePointer->elementColumn = 0;
       screenRefreshFlag = 1;
   } else if(spritePointer->elementColumn < 0) {
       spritePointer->elementColumn = GRID_DIMENSION-1; 
       screenRefreshFlag = 1;
   }

   return screenRefreshFlag;
}

/* ------ FUNCTION ------*/ 
/*
 * Populate a grid elemetn with the sprite determined from determine_next_folding_sprite();
 *
 * Accepts: Grid, spritePointer
 * Returns:  
 * nothing
*/
void populate_cell(char grid[][CELL_WIDTH*GRID_DIMENSION], struct sprite *spritePointer) {
    for(int i = 0; i < CELL_HEIGHT; i++) {
        for(int j = 0; j < CELL_WIDTH-1; j++) {
            grid[i+(spritePointer->elementRow * CELL_HEIGHT)][j+(spritePointer->elementColumn * CELL_WIDTH)] = spritePointer->element[i][j];
        }
    }
}
