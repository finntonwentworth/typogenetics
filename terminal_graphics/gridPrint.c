#include <stdio.h>
#include <unistd.h>

#define SQUARE_DIMENSION    50

int main() {
    int flip_flop = 0;

    printf("\x1B[2J");
    printf("\x1B[H");
    for(int i = 0; i < 5; i++) {
        printf("\n");
    }

    printf("This is my test line\n");

    for(int i = 0; i < 5; i++) {
        printf("\n");
    }
    for (int a = 0; a < 4; a++) {
        for(int i = 0; i < SQUARE_DIMENSION; i++) {
            for (int j = 0; j < 2 * SQUARE_DIMENSION; j++) {
              if(flip_flop == 0) {

                 printf("X");
              } else {
                 printf("-");
              }
            }
            printf("\n");
        }
      if(a != 4){
//        printf("\x1B[2J");
//     jump to home  (0,0)
        printf("\x1B[H");
        printf("\n");
        printf("\n");
        flip_flop = !flip_flop;
      } else {
//        printf("\x1B[H");
//        flip_flop = !flip_flop;
    }
    usleep(500000);
    }
}
