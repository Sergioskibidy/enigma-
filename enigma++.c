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
//I converted key into local variables.

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

    //Divides by 2 the number and stores the modulo into an array, the binary is stored backwards.
    while (number != 0) {
        temp = number % 2;
        number = number / 2;
        binary[i] = temp;
        i--;
    }
    //If the length of the binary is not yet 8 digits, 0s are added to the front of the binary
    while (i >= 0) {
        binary[i] = 0;
        i--;
    }
}

//Prints the binary from the binary array
void printBinary() {
    for (int i = 0; i < 8; i++) {
        printf("%d",binary[i]);
    }
}

//add validation checks
//This is the encryption algorithm for the first algorithm
void simpleEncryption() { 
    int key; //The seed of srand()
    int i = 0;
    int mask = 0;
    int encrypted = 0; //Encrypted letter

    //The user inputs the seed(key) for the srand(), and inputs the text to encrypt
    printf("Input the key: ");
    scanf("%d", &key);
    getchar();
    printf("Please input your plaintext.\n");
    fgets(text,sizeof(text),stdin);

    //Encrypts the text
    srand(key);
    //Iterates letter by letter, including spaces
    while ((text[i] != '\n') && (text[i] != '\0')) {
        mask = rand() % 256; //calcuates the mask
        encrypted = (unsigned char)text[i] ^ mask; //Bitwise XOR is applied to the current letter
        binaryConverter(encrypted); //Converted into binary
        printBinary(); //Binaary is outputed
        printf(" ");
        i++;
    }

    printf("\n");
}

//add validation checks
//This is the decryption algorithm for the first algorithm
void simpleDecryption() {
    int key; //The seed of srand()
    int i = 0;
    int temp = 0;
    char decypheredText[8000];
    char letter;
    char decimal[10]; //Takes in binary as a string, 8 + '\n' and '\0'
    int mask = 0;

    //The user inputs the seed(key) for the srand(), and inputs the text to decrypt
    printf("Input the key: ");
    scanf("%d", &key);
    getchar();
    printf("Please input your cyphertext in binary.\n");

    //Decrypts the text
    srand(key);
    printf("Terminate with the word 'END'.\n");
    //Takes a 8 digit long string until 'END'  is inputed, every input it decrypts the
    //letter and stores it in an array
    while(scanf(" %8s", decimal) == 1) {
        if (strcmp(decimal, "END") == 0) {
            break;
        }

        temp = (int)strtol(decimal,NULL,2); //Converts decimal into binary.
        mask = rand() % 256; //calculates the mask
        temp = temp ^ mask; //Bitwise operation on the cypher letter

        letter = temp; //letter automatically stored as an character, as letter is declared as char and temp as int.
        decypheredText[i] = letter; //Stores the letter in an array

        i++;
    }
    decypheredText[i] = '\0'; //assigns the end pointer to the array, so c knows where is the end of the string
    printf("%s\n",decypheredText);
}

int linConGen(int number) {
    int a = 10000;  // Multiplier
    unsigned int m = 2147483647; // Prevents integer overflow
    int c = 2;  // Constant
    int newNumber = (a * number + c) % m;   // Formula
    return newNumber;
}

//add validation check
//This is the encryption algorithm for the third algorithm
void subtractiveGenEncryption() {
    int keyNums[10000] = {0}; //Stores the sequence of numbers needed for the encryption
    int temp;
    int n = 55; //The starting position of n in the encryption algorithm, n is applied to the formula
    int mask = 0;
    int i = 0;
    int encrypted = 0; //Encrypted letter

    //User inputs 55 numbers and stored in an array, the numbers are the key
    printf("Input the key(55 numbers): ");
    for (int i = 0; i < 55; i++) {
        temp = 0;
        scanf("%d", &temp);
        //The extra operations added to the formula is to make sure negative numbers are converted into positive ones.
        keyNums[i] = ((temp % 256) + 256) % 256;
    }
    getchar();
    //Then takes the text to be encrypted
    printf("Please input your plaintext.\n");
    fgets(text,sizeof(text),stdin);

    //Encrypts each letter and outputs it
    while ((text[i] != '\n') && (text[i] != '\0')) {
        //The extra operations added to the formula is to make sure negative numbers are converted into positive ones.
        mask = (((keyNums[n-24] - keyNums[n-55]) % 256) + 256) % 256;
        //The new number in the sequence calculated is stored in the keys array.
        //E.g. X_(56) is calculated from X_(1) and X_(32)
        keyNums[n] = mask; 
        encrypted = (unsigned char)text[i] ^ mask; //Bitwise XOR opperation in each letter,
        binaryConverter(encrypted); //Converted into binary
        printBinary(); //Binaary is outputed
        printf(" ");
        i++;
        n++;
    }

    printf("\n");
}

//add validation check
//This is the decryption algorithm for the third algorithm
void subtractiveGenDecryption() {
    int keyNums[10000] = {0}; //Stores the sequence of numbers needed for the encryption
    int temp = 0;
    int i = 0;
    int n = 55; //The starting position of n in the encryption algorithm, n is applied to the formula
    char decypheredText[8000];
    char letter;
    char decimal[10]; //Takes in binary as a string, 8 + '\n' and '\0'
    int mask = 0;

    //User inputs 55 numbers and stored in an array, the numbers are the key
    printf("Input the key(55 numbers): ");
    for (int i = 0; i < 55; i++) {
        temp = 0;
        scanf("%d", &temp);
        //The extra operations added to the formula is to make sure negative numbers are converted into positive ones.
        keyNums[i] = ((temp % 256) + 256) % 256;
    }
    getchar();
    //Then takes the text to be encrypted
    printf("Please input your cyphertext in binary.\n");

    //Decrypts the text
    //Takes a 8 digit long string until 'END'  is inputed, every input it decrypts the
    //letter and stores it in an array
    temp = 0;
    printf("Terminate with the word 'END'.\n");
    while(scanf(" %8s", decimal) == 1) {
        if (strcmp(decimal, "END") == 0) {
            break;
        }

        temp = (int)strtol(decimal,NULL,2); //Converts decimal into binary.
        //The extra operations added to the formula is to make sure negative numbers are converted into positive ones.
        mask = (((keyNums[n-24] - keyNums[n-55]) % 256) + 256) % 256;
        //The new number in the sequence calculated is stored in the keys array.
        //E.g. X_(56) is calculated from X_(1) and X_(32)
        keyNums[n] = mask;
        temp = temp ^ mask; //Bitwise XOR is done to the encypted letter to decrypt it.

        letter = temp; //letter automatically stored as an character, as letter is declared as char and temp as int.
        decypheredText[i] = letter; //letter stored into an array

        i++;
        n++;
    }
    decypheredText[i] = '\0'; //assigns the end pointer to the array, so c knows where is the end of the string
    printf("%s\n",decypheredText);
}


int main(int argc,char *argv[]) {
    //Create menu pls

    return 0;
}
