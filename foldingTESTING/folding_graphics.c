#include <stdio.h>
#include "../src/strand_def.h"

//macro cells in printing grid 
#define GRID_DIMENSION   7
//size of 2D arrays that make up cells 
#define CELL_HEIGHT  3
#define CELL_WIDTH   5

void folding_graphics(struct decodedStrand*);
void print_cell(char, int); 

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



//the 4th dimensional 2D array of 2D arrays
char theGrid[GRID_DIMENSION][GRID_DIMENSION][CELL_HEIGHT][CELL_WIDTH];



/*                      ^
 *                    <cop> 
 *                      V
 */
char  copUP[CELL_HEIGHT][CELL_WIDTH] = {
                                         {"  ^  "},
                                         {" cop "},
                                         {"     "}
                                       };




int main() {
    struct decodedStrand userDecode = {
                                        .foldingPattern = "rr",
                                        .instruction = {6,6}
                                      };
    struct decodedStrand *decodedPointer = &userDecode; 

    folding_graphics(decodedPointer); 


    return 0; 

}






//function serves to call print_cell multiple times for each folding direction in the pattern 
//will likely handle the logistics of new lines? 
void folding_graphics(struct decodedStrand *decodedPointer) {
    for(int i = 0; i <= decodedPointer->foldingPatternSize; i++) {
        print_cell(decodedPointer->foldingPattern[i], decodedPointer->instruction[i]);
        printf("\n");
    }
}

// this function will take in the folding direction and instruction number to 
// print the correct instruction and folding arrow
void print_cell(char folding_direction, int instructionNumber) {
    int i = 0;

    while(i <=CELL_HEIGHT) {
        for(int j = 0; j < CELL_WIDTH; j++) {
            printf("%c",copUP[i][j]);
        }
    printf("\n");
    i++;
    }
}
