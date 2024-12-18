#include "folding_functions.c"

/*--- Folding Functions ---*/
void populate_cell(char[][CELL_WIDTH*GRID_DIMENSION],struct sprite*); 
void print_grid(char[][CELL_WIDTH*GRID_DIMENSION]); 
struct sprite *determine_next_folding_sprite(int,char, struct sprite*); 
void fill_with_spaces(char[][CELL_WIDTH*GRID_DIMENSION]); 
int check_screen_refresh(struct sprite*);
