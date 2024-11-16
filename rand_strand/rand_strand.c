#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*---FUNCTION---*/
/*
 * User calls rand_strand 100 
 * to generate random strand of 100 bases 
 * with equal distribution for each element 
 *
 */
int main(int argC, char* argV[]){

    //convert second argument into size of output
    //since first argument is rand_strand 
    int size = atoi(argV[1]);

    // int to store randomly generated # 
    // 0 = A 
    // 1 = T
    // 2 = G
    // 3 = C
   int  baseNumber; 
   char outputStrand[size];

   srand(time(0)); 

   if(argC <= 1){ 
       printf("Invalid input\n");
       return -1; 
   }else{
       for(int i = 0; i<size; i++){
            baseNumber = rand() % 4; 
            switch(baseNumber){
                case 0:
                    outputStrand[i] = 'A';
                    break;
                case 1:
                    outputStrand[i] = 'T';
                    break;
                case 2:
                    outputStrand[i] = 'G';
                    break;
                case 3:
                    outputStrand[i] = 'C';
                    break;
                default:
                    break;
            }
            if(i == size - 1){
                outputStrand[i+1] = '\0';
            } 
    };
    printf("%s\n",outputStrand);
    return 1;
    }
}

