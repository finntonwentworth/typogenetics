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
                                                        {"         "},
                                                        {"    ^    "},
                                                        {"   cop   "},
                                                        {"         "},
                                                        {"         "}
                                                       };
//extern const char  copRIGHT[CELL_HEIGHT][CELL_WIDTH] = {
char  copRIGHT[CELL_HEIGHT][CELL_WIDTH] = {
                                                        {"         "},
                                                        {"         "},
                                                        {"   cop > "},
                                                        {"         "},
                                                        {"         "}
                                                       };
//extern const char  copDOWN[CELL_HEIGHT][CELL_WIDTH] = {
char  copDOWN[CELL_HEIGHT][CELL_WIDTH] = {
                                                        {"         "},
                                                        {"         "},
                                                        {"   cop   "},
                                                        {"    v    "},
                                                        {"         "}
                                                       };
//extern const char  copLEFT[CELL_HEIGHT][CELL_WIDTH] = {
char  copLEFT[CELL_HEIGHT][CELL_WIDTH] = {
                                                        {"         "},
                                                        {"         "},
                                                        {" < cop   "},
                                                        {"         "},
                                                        {"         "}
                                                      };

