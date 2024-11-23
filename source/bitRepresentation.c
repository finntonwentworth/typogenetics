#include <stdint.h>
#include <string.h>
#include <stdio.h>

// |     |  A  |  C  |  G  |  T  |
// |---  | --- | --- | --- | --- |
// |**A**| pun | cut | del | swi |
// |**C**| mvr | mvl | cop | off |
// |**G**| ina | inc | ing | int |
// |**T**| rpy | rpu | lpy | lpu |

// |        |  A   |  C   |  G   |  T   |
// |        | 1000 | 0100 | 0010 | 0001 |
// |---     | ---  | ---  | ---  | ---  |
// | A 1000 | 1000 | 1100 | 1010 | 1001 |
// | C 0100 | 1100 | 0100 | 0110 | 0101 |
// | G 0010 | 1010 | 0110 | 0010 | 0011 |
// | T 0001 | 1001 | 0101 | 0011 | 0001 |


                             //A           C           G           T
const unsigned char bases[] = {0b00000001, 0b00000010, 0b00000100, 0b00001000};

void printCharAsBits(unsigned char character) {
    for (int bit = 0; bit < sizeof(unsigned char) * 8; bit++) {
        printf("%i", character & 0x01);
        character = character >> 1;
    }
}

void printCharArrAsBits(unsigned char arr[]) {
    printf("[");
    for (int i = 0; arr[i] != '\0'; i++) {
        printCharAsBits(arr[i]);
        printf(", ");
    }
    printf("]\n");
}

int main(void) {
    unsigned char strand[100] = {'A', 'A', 'A', 'C', 'A', 'G', 'A', 'T', 'C', 'A', 'C', 'C', 'C', 'G', 'C', 'T', 'G', 'A', 'G', 'C', 'G', 'G', 'G', 'T', 'T', 'A', 'T', 'C', 'T', 'G', 'T', 'T'};
    printf("Enter an even strand: ");
    // scanf("%99s", strand);

    // Encode the bases
    int i = 0;
    while (i < sizeof(strand) && strand[i] != '\0') {
        switch (strand[i]) {
            case 'A':
                strand[i] = bases[0];
                break;
            case 'C':
                strand [i] = bases[1];
                break;
            case 'G':
                strand [i] = bases[2];
                break;
            case 'T':
                strand [i] = bases[3];
                break;
            default:
                printf("Unrecognized base at position %d\n\r", i);
                break;
        }
        i++;
    }

    printf("\n\nEncoded:\n");
    printCharArrAsBits(strand);

    unsigned char aminoAcids[sizeof(strand) / 2 ];

    for (int i = 0; i < sizeof(strand) && strand[i] != '\0'; i++) {
        aminoAcids[i] = strand[i*2] | strand[(i*2)+1];
    }

    printf("\nInstructions:\n");
    printCharArrAsBits(aminoAcids);
}