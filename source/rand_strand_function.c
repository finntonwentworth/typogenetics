#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "strand_def.h"

/*---FUNCTION---*/
/*
 * User calls rand_strand 100 
 * to generate random strand of 100 bases 
 * with equal distribution for each element 
 * Accepts: 
 * int size of random strand to be generated 
 * Returns
 * Char pointer to randomly generated strand
 */
char *rand_strand(int size) {
    static char randStrand[MAX_STRAND_SIZE];

    // int to store randomly generated # 
    // 0 = A 
    // 1 = T
    // 2 = G
    // 3 = C
   int  baseNumber; 

   srand(time(0)); 

   if(size <= 0){ 
      return NULL;
   }else{
       for(int i = 0; i<size; i++){
            baseNumber = rand() % 4; 
            switch(baseNumber){
                case 0:
                    randStrand[i] = 'A';
                    break;
                case 1:
                    randStrand[i] = 'T';
                    break;
                case 2:
                    randStrand[i] = 'G';
                    break;
                case 3:
                    randStrand[i] = 'C';
                    break;
                default:
                    break;
            }
            if(i == size - 1){
                randStrand[i+1] = '\0';
            } 
        };
    }
    return randStrand;
}
