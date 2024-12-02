//macro cells in printing grid 
#define GRID_DIMENSION   7
//size of 2D arrays that make up cells 
#define CELL_HEIGHT  5
#define CELL_WIDTH   11

struct sprite {
    int elementRow; 
    int elementColumn; 
    char element[CELL_HEIGHT][CELL_WIDTH]; 
};
/*                      ^
 *                    <cop> 
 *                      V
 */
//extern const char  copUP[CELL_HEIGHT][CELL_WIDTH] =    {
char  copUP[CELL_HEIGHT][CELL_WIDTH] =    {
                                                        {"    ^    "},
                                                        {"    |    "},
                                                        {"   cop   "},
                                                        {"         "},
                                                        {"         "}
                                                       };
//extern const char  copRIGHT[CELL_HEIGHT][CELL_WIDTH] = {
char  copRIGHT[CELL_HEIGHT][CELL_WIDTH] = {
                                                        {"         "},
                                                        {"         "},
                                                        {"   cop-->"},
                                                        {"         "},
                                                        {"         "}
                                                       };
//extern const char  copDOWN[CELL_HEIGHT][CELL_WIDTH] = {
char  copDOWN[CELL_HEIGHT][CELL_WIDTH] = {
                                                        {"         "},
                                                        {"         "},
                                                        {"   cop   "},
                                                        {"    |    "},
                                                        {"    v    "}
                                                       };
//extern const char  copLEFT[CELL_HEIGHT][CELL_WIDTH] = {
char  copLEFT[CELL_HEIGHT][CELL_WIDTH] = {
                                                        {"         "},
                                                        {"         "},
                                                        {"<--cop   "},
                                                        {"         "},
                                                        {"         "}
                                                      };


// ok this is 4 blocks of 16 sections of 5 sub sections of 11 elements
// [a][b][c][d]
// a = folding direction 
    //-  0 = up
    //-  1 = right
    //-  2 = down
    //-  3 = left
// b = instruction with that folding 
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
// c = row of specific sprite 
// d = column of specific sprite
char tableOfSprites[4][16][CELL_HEIGHT][CELL_WIDTH] = {
                                                        {
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"         "},// pun 
                                                               {"         "},
                                                               {"         "} 
                                                           },
                                                           {
                                                               {"    ^    "},
                                                               {"    |    "},
                                                               {"   cut   "}, //cutUP
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"    ^    "},
                                                               {"    |    "},
                                                               {"   del   "}, //delUP
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"    ^    "},
                                                               {"    |    "},
                                                               {"   swi   "}, //swiUP
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"    ^    "},
                                                               {"    |    "},
                                                               {"   swi   "}, //swiUP
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },

                                                        }, 
                                                        {
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },

                                                        }, 
                                                        {
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },

                                                        }, 
                                                        {
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           },
                                                           {
                                                               {},
                                                               {},
                                                               {},
                                                               {},
                                                               {}
                                                           }

                                                        } 
                                                      };

