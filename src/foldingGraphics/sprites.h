//macro cells in printing grid 
#define GRID_DIMENSION   9
//size of 2D arrays that make up cells 
#define CELL_HEIGHT  5
#define CELL_WIDTH   10
/* --- SPRITE --- */
/*
 * Sprite holds the next enzyme element to be drawn in the folding animation, along with 
 * the position data
 *
 * int elementRow: Row # of sprite in the grid 
 * int elementColumn: Column # of sprite in the grid 
 * char lastFacingDirection: char representing the orientation of the next move 
 * char element[][]: 2D array holding sprite element 
 *
 */
struct sprite {
    int elementRow; 
    int elementColumn; 
    char lastFacingDirection;
    char element[CELL_HEIGHT][CELL_WIDTH]; 
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
char spriteTable[4][16][CELL_HEIGHT][CELL_WIDTH] = {
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
                                                               {"   mvr   "}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"    ^    "},
                                                               {"    |    "},
                                                               {"   mvl   "},
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"    ^    "},
                                                               {"    |    "},
                                                               {"   cop   "}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"    ^    "},
                                                               {"    |    "},
                                                               {"   off   "}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"    ^    "},
                                                               {"    |    "},
                                                               {"   ina   "},
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"    ^    "},
                                                               {"    |    "},
                                                               {"   inc   "}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"    ^    "},
                                                               {"    |    "},
                                                               {"   ing   "},
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"    ^    "},
                                                               {"    |    "},
                                                               {"   int   "}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"    ^    "},
                                                               {"    |    "},
                                                               {"   rpy   "},
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"    ^    "},
                                                               {"    |    "},
                                                               {"   rpu   "}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"    ^    "},
                                                               {"    |    "},
                                                               {"   lpy   "},
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"    ^    "},
                                                               {"    |    "},
                                                               {"   lpu   "}, 
                                                               {"         "},
                                                               {"         "}
                                                           },

                                                        }, 
                                                        {
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"         "},// pun 
                                                               {"         "},
                                                               {"         "} 
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   cut-->"}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   del-->"}, //delUP
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   swi-->"}, //swiUP
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   mvr-->"}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   mvl-->"},
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   cop-->"}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   off-->"}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   ina-->"},
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   inc-->"}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   ing-->"},
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   int-->"}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   rpy-->"},
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   rpu-->"}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   lpy-->"},
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   lpu-->"}, 
                                                               {"         "},
                                                               {"         "}
                                                           },

                                                        }, 
                                                        {
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"         "},// pun 
                                                               {"         "},
                                                               {"         "} 
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   cut   "}, 
                                                               {"    |    "},
                                                               {"    v    "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   del   "}, //delUP
                                                               {"    |    "},
                                                               {"    v    "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   swi   "}, //swiUP
                                                               {"    |    "},
                                                               {"    v    "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   mvr   "}, 
                                                               {"    |    "},
                                                               {"    v    "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   mvl   "},
                                                               {"    |    "},
                                                               {"    v    "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   cop   "}, 
                                                               {"    |    "},
                                                               {"    v    "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   off   "}, 
                                                               {"    |    "},
                                                               {"    v    "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   ina   "},
                                                               {"    |    "},
                                                               {"    v    "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   inc   "}, 
                                                               {"    |    "},
                                                               {"    v    "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   ing   "},
                                                               {"    |    "},
                                                               {"    v    "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   int   "}, 
                                                               {"    |    "},
                                                               {"    v    "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   rpy   "},
                                                               {"    |    "},
                                                               {"    v    "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   rpu   "}, 
                                                               {"    |    "},
                                                               {"    v    "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   lpy   "},
                                                               {"    |    "},
                                                               {"    v    "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"   lpu   "}, 
                                                               {"    |    "},
                                                               {"    v    "}
                                                           },

                                                        }, 
                                                        {
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"         "},// pun 
                                                               {"         "},
                                                               {"         "} 
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"<--cut   "}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"<--del   "}, //delUP
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"<--swi   "}, //swiUP
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"<--mvr   "}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"<--mvl   "},
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"<--cop   "}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"<--off   "}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"<--ina   "},
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"<--inc   "}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"<--ing   "},
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"<--int   "}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"<--rpy   "},
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"<--rpu   "}, 
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"<--lpy   "},
                                                               {"         "},
                                                               {"         "}
                                                           },
                                                           {
                                                               {"         "},
                                                               {"         "},
                                                               {"<--lpu   "}, 
                                                               {"         "},
                                                               {"         "}
                                                           },

                                                        }, 
                                                      };

