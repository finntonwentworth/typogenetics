#include <stdio.h>

//macro cells in printing grid 
#define GRID_DIMENSION   7
//size of 2D arrays that make up cells 
#define CELL_HEIGHT  5
#define CELL_WIDTH   11

/*                      ^
 *                    <cop> 
 *                      V
 */
char  copUP[CELL_HEIGHT][CELL_WIDTH] = {
                                         {"         "},
                                         {"    ^    "},
                                         {"   cop   "},
                                         {"         "},
                                         {"         "}
                                       };
char  copRIGHT[CELL_HEIGHT][CELL_WIDTH] = {
                                         {"         "},
                                         {"         "},
                                         {"   cop > "},
                                         {"         "},
                                         {"         "}
                                       };
char  copDOWN[CELL_HEIGHT][CELL_WIDTH] = {
                                         {"         "},
                                         {"         "},
                                         {"   cop   "},
                                         {"    V    "},
                                         {"         "}
                                       };
char  copLEFT[CELL_HEIGHT][CELL_WIDTH] = {
                                         {"         "},
                                         {"         "},
                                         {"  <cop   "},
                                         {"         "},
                                         {"         "}
                                       };

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
void determine_next_folding_sprite(int instruction[], char foldingPattern[]) {

}

// this function will take in the folding direction and instruction number to 
// print the correct instruction and folding arrow
void populate_cell(char grid[][CELL_WIDTH*GRID_DIMENSION], int cellRow, int cellColumn) {

    for(int i = 0; i < CELL_HEIGHT; i++) {
        for(int j = 0; j < CELL_WIDTH; j++) {
            grid[i+(cellRow * CELL_HEIGHT)][j+(cellColumn*CELL_WIDTH)] = copUP[i][j];
        }
    }
}
