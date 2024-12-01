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
struct sprite *determine_next_folding_sprite(int instruction[], char foldingPattern[]) {
    struct sprite *spritePointer;

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
