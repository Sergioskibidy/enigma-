/* file : Enigma++.c */
/* co-author : Jouke Willem van der Heide (j.w.van.der.heide.1@student.rug.nl) */
/* co-author : Sergio Zhou Wu (s.zhou.wu@student.rug.nl)*/
/* date : Fri Okt 30 2026 */
/* version: 1.0 */
/* Description:
* This program asks for a couple of inputs and then is able to encrypt and decrypt a message with 3 different types of algorithms.
* Your starting inputs decide if it is going to en/decrypt and what algorithm it uses.
* After that you input a key and or a message to encrypt or binary to decrypt.
* Then it outputs the encrypted or decrypted message.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int binary[8]; //Used for binary conversion
char text[8000]; //inputted text


// Loop to cover excessive characters, to prevent keys with more than 55 numbers or spaces etc.
void removeExcessiveText() {
    char c;
    while ((c = getchar()) != '\n') {
        // Discards the c
    }
}

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

// Generates the random numbers according to the second algorithm
int linConGen(int number) {
    int a = 22695477;  // Multiplier
    unsigned int m = 2147483648;
    int c = 1;  // Constant
    int newNumber = (a * number + c) % m;   // Formula
    return newNumber;
}

//This is the encryption algorithm for the first algorithm
void simpleEncryption(int key) { 
    int i = 0;
    int mask = 0;
    int encrypted = 0; //Encrypted letter

    //Encrypts the text
    srand(key);
    //Iterates letter by letter, including spaces
    while ((text[i] != '\n') && (text[i] != '\0')) {
        mask = rand() % 256; //calcuates the mask
        encrypted = (unsigned char)text[i] ^ mask; //Bitwise XOR is applied to the current letter
        binaryConverter(encrypted); //Converted into binary
        printBinary(); //Binary is outputted
        printf(" ");
        i++;
    }

    printf("\n");
}

//This is the decryption algorithm for the first algorithm
void simpleDecryption(int key) {
    int i = 0;
    int temp = 0;
    char decypheredText[8000];
    char letter;
    char decimal[10]; //Takes in binary as a string, 8 + '\n' and '\0'
    int mask = 0;

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

//This is the encryption algorithm for the second algorithm
void linEncryption(int key) { 
    int i = 0;
    int mask = 0;
    int encrypted = 0; //Encrypted letter
    //Encrypts the text
    int seed = linConGen(key);
    //Iterates letter by letter, including spaces
    while ((text[i] != '\n') && (text[i] != '\0')) {
        mask = linConGen(seed) % 256; //calcuates the mask
        encrypted = (unsigned char)text[i] ^ mask; //Bitwise XOR is applied to the current letter
        binaryConverter(encrypted); //Converted into binary
        printBinary(); //Binary is outputted
        printf(" ");
        i++;
        // Updates number
        seed = linConGen(seed);
    }

    printf("\n");
}

//This is the decryption algorithm for the second algorithm
void linDecryption(int key) {
    int i = 0;
    int temp = 0;
    char decypheredText[8000];
    char letter;
    char decimal[10]; //Takes in binary as a string, 8 + '\n' and '\0'
    int mask = 0;

    printf("Please input your cyphertext in binary.\n");

    //Decrypts the text
    int seed = linConGen(key);
    printf("Terminate with the word 'END'.\n");
    //Takes a 8 digit long string until 'END'  is inputed, every input it decrypts the
    //letter and stores it in an array
    while(scanf(" %8s", decimal) == 1) {
        if (strcmp(decimal, "END") == 0) {
            break;
        }
        temp = (int)strtol(decimal,NULL,2); //Converts decimal into binary.
        mask = linConGen(seed) % 256; //calculates the mask
        temp = temp ^ mask; //Bitwise operation on the cypher letter

        letter = temp; //letter automatically stored as a character, as letter is declared as char and temp as int.
        decypheredText[i] = letter; //Stores the letter in an array

        i++;
        // Updates number
        seed = linConGen(seed);
    }
    decypheredText[i] = '\0'; //assigns the end pointer to the array, so c knows where is the end of the string
    printf("%s\n",decypheredText);
}

//This is the encryption algorithm for the third algorithm
void subtractiveGenEncryption(int keyNums[]) {
    int temp;
    int n = 55; //The starting position of n in the encryption algorithm, n is applied to the formula
    int mask = 0;
    int i = 0;
    int encrypted = 0; //Encrypted letter

    //Encrypts each letter and outputs it
    while ((text[i] != '\n') && (text[i] != '\0')) {
        //The extra operations added to the formula is to make sure negative numbers are converted into positive ones.
        mask = (((keyNums[n-24] - keyNums[n-55]) % 256) + 256) % 256;
        //The new number in the sequence calculated is stored in the keys array.
        //E.g. X_(56) is calculated from X_(1) and X_(32)
        keyNums[n] = mask; 
        encrypted = (unsigned char)text[i] ^ mask; //Bitwise XOR opperation in each letter,
        binaryConverter(encrypted); //Converted into binary
        printBinary(); //Binary is outputed
        printf(" ");
        i++;
        n++;
    }

    printf("\n");
}

//This is the decryption algorithm for the third algorithm
void subtractiveGenDecryption(int keyNums[]) {
    int temp = 0;
    int i = 0;
    int n = 55; //The starting position of n in the encryption algorithm, n is applied to the formula
    char decypheredText[8000];
    char letter;
    char decimal[10]; //Takes in binary as a string, 8 + '\n' and '\0'
    int mask = 0;

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

// Starts the actual functions
// The key is a pointer because it is or a singular int or an array
// An array is a pointer so to prevent having another input, i made it multi usable (might be confusing)
void inputAndStarter(int cryption, int methodType, int *key) {
    // Handles en/de- cryption
    if (cryption == 1) {
        // Get the input message
        printf("Type in your message to encrypt:\n");
        fgets(text,sizeof(text),stdin);
        // Starts correct encryption function
        if (methodType == 1) {
            simpleEncryption(*key);
        } else if (methodType == 2) {
            linEncryption(*key);
        } else {
            subtractiveGenEncryption(key);
        }
    } else {
        // Since decryption works with a loop to convert binary step by step
        // It just calls the function for the message input
        if (methodType == 1) {
            simpleDecryption(*key);
        } else if (methodType == 2) {
            linDecryption(*key);
        } else {
            subtractiveGenDecryption(key);
        }
    }
}

void enigmaSelector(int cryption, int methodType) {
    // Getting the key
    // 1 key
    if (methodType != 3) {
        int key;
        printf("Type in your key: ");
        scanf("%d", &key);
        removeExcessiveText();
        // Function to start other function
        inputAndStarter(cryption, methodType, &key);
    } else {
        // 55 keys
        int temp;
        int keyNums[60] = {0}; //Stores the sequence of numbers needed for the encryption
        //User inputs 55 numbers and stored in an array, the numbers are the key
        printf("Input the key (55 numbers): ");
        for (int i = 0; i < 55; i++) {
            temp = 0;
            scanf("%d", &temp);
            //The extra operations added to the formula is to make sure negative numbers are converted into positive ones.
            keyNums[i] = ((temp % 256) + 256) % 256;
        }
        removeExcessiveText();
        // Function to start en/decryption
        inputAndStarter(cryption, methodType, keyNums);
    }
}

int main(int argc,char *argv[]) {
    // Menu selection
    int cryption;
    do {
        printf("What would you like to do?\n");
        printf("Type 1 for encryption.\n");
        printf("Type 2 for decryption.\n");
        scanf("%d", &cryption);
        if (cryption != 1 && cryption != 2) {
            printf("Wrong input: %d, is not valid.\n", cryption);
            printf("Please try again.\n");
            printf("\n");
        }
    } while (cryption != 1 && cryption != 2);

    int methodType;
    do {
        printf("What method would you like to use?\n");
        printf("Type 1 for standard C seed.\n");
        printf("Type 2 for linear congruential algorithm.\n");
        printf("Type 3 for subtractive generation.\n");
        scanf("%d", &methodType);
        if (methodType < 1 || methodType > 3) {
            printf("Wrong input: %d, is not valid.\n", methodType);
            printf("Please try again.\n");
            printf("\n");
        }
    } while (methodType < 1 || methodType > 3);

    // Function for rest of the input selection
    enigmaSelector(cryption, methodType);

    return 0;
}
