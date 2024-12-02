#include <stdio.h>
#include "sprites.h"


// prints all chars in the grid
void print_grid(char grid[][CELL_WIDTH*GRID_DIMENSION]) {
    //print down each row
    for(int i = 0; i <(CELL_HEIGHT * GRID_DIMENSION); i++) {
        printf("\t");
        //print across for each row 
        for(int j = 0; j <(CELL_WIDTH * GRID_DIMENSION); j++) {
            printf("%c",grid[i][j]);

        }
        printf("\n"); 
    }
}

// determines the next needed sprite to be populated in the grid 
// needs to know the previous grid element? and then give the position of the next one 
struct sprite *determine_next_folding_sprite(int instruction[], char foldingPattern[], struct sprite *spritePointer) {

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


    // this copies the sprite into the structure. 
    // Now i need a way to dynamically change what variable it calls 
    for(int i = 0; i < CELL_HEIGHT; i++) {
        for(int j = 0; j < CELL_WIDTH; j++) {
            spritePointer->element[i][j] = copRIGHT[i][j];
        }
    }
    spritePointer->elementRow = 3;
    spritePointer->elementColumn = 3;

    return spritePointer; 
}

// this function will take in the folding direction and instruction number to 
// print the correct instruction and folding arrow
void populate_cell(char grid[][CELL_WIDTH*GRID_DIMENSION], struct sprite *spritePointer) {
    for(int i = 0; i < CELL_HEIGHT; i++) {
        for(int j = 0; j < CELL_WIDTH; j++) {
            grid[i+(spritePointer->elementRow * CELL_HEIGHT)][j+(spritePointer->elementColumn *CELL_WIDTH)] = spritePointer->element[i][j];
        }
    }
}
