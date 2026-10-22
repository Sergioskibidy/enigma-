/* file : Enigma++.c */
/* co-author : Jouke Willem van der Heide (j.w.van.der.heide.1@student.rug.nl) */
/* co-author : Sergio Zhou Wu (s.zhou.wu@student.rug.nl)*/
/* date : Mon Okt 9 2026 */
/* version: 1.0 */
/* Description:
* 
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>


int binary[1000]; //Used for binary conversion
char text[8000]; //inputed text
char formatedText[10000];
int key;

void *safeMalloc(int n) {
    void *p = malloc(n);
    if (p == NULL) {
        printf("Error: malloc(%d) failed. Out of memory?\n", n);
        exit(EXIT_FAILURE);
    }
    return p;
}

void *safeCalloc(int n, int size) {
    void *p = calloc(n, size);
    if (p == NULL) {
        printf("Error: malloc(%d) failed. Out of memory?\n", n);
        exit(EXIT_FAILURE);
    }
    return p;
}

//--------------------------------------------------------------------------

void binaryConverter(int number) {
    int temp;
    int i = 7;

    while (number != 0) {
        temp = number % 2;
        number = number / 2;
        binary[i] = temp;
        i--;
    }
    while (i >= 0) {
        binary[i] = 0;
        i--;
    }
}

void printBinary() {
    for (int i = 0; i < 8; i++) {
        printf("%d",binary[i]);
    }
}

void noobEncryption() { //The first num generator
    fgets(text,sizeof(text),stdin);
    srand(key);
    int i = 0;
    int mask = 0;

    while ((text[i] != '\n') && (text[i] != '\0')) {
        mask = rand() % 256;
        int encrypted = text[i] ^ mask;
        binaryConverter(encrypted);
        printBinary();
        printf(" ");
        i++;
    }

    printf("\n");
}

void noobDecryption() {
    srand(key);
    int i = 0;
    int temp = 0;
    char decypheredText[8000];
    char letter;
    char decimal[10];

    printf("Terminate with the word 'END'.\n");
    while(scanf(" %8s", decimal) == 1) {
        if (strcmp(decimal, "END") == 0) {
            break;
        }

        //here downwards it should be all good, gotta find a way to convert to decimal
        temp = (int)strtol(decimal,NULL,2);
        int mask = rand() % 256;
        temp = temp ^ mask;

        letter = temp;
        decypheredText[i] = letter;

        i++;
    }
    decypheredText[i] = '\0';
    printf("%s\n",decypheredText);
}

int linConGen(int number) {
    int a = 10000;  // Multiplier
    unsigned int m = 2147483647; // Prevents integer overflow
    int c = 2;  // Constant
    int newNumber = (a * number + c) % m;   // Formula
    return newNumber;
}


int main(int argc,char *argv[]) {
    printf("Input the key: ");
    scanf("%d", &key);
    getchar();
    printf("Please input your cyphertext/plaintext.\n");
    


    noobEncryption();
    noobDecryption();



    

    return 0;
}
