// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// // Function for converting a string to uppercase
// void toUpperCase(char encrypt[], int ps) {
//     for (int i = 0; i < ps; i++) {
//         if (encrypt[i] >= 'a' && encrypt[i] <= 'z')
//             encrypt[i] -= 32; // Convert lowercase to uppercase
//     }
// }

// // Function for removing spaces from a string
// int removeSpaces(char* plain, int ps) {
//     int count = 0;
//     for (int i = 0; i < ps; i++) {
//         if (plain[i] != ' ')
//             plain[count++] = plain[i];
//     }
//     plain[count] = '\0';
//     return count;
// }

// // Function for creating the key matrix
// void createMatrix(char keystr[], int ks, char keyMat[5][5]) {
//     int dict[26] = {0};
//     int i = 0, j = 0;
//     for (int k = 0; k < ks; k++) {
//         if (dict[keystr[k] - 'A'] == 0 && keystr[k] != 'J') {
//             keyMat[i][j] = keystr[k];
//             dict[keystr[k] - 'A'] = 1;   //mark the character as used (1)
//             j++;
//             if (j == 5) {
//                 i++;
//                 j = 0;
//             }
//         }
//     }
//     for (int k = 0; k < 26; k++) {
//         if (dict[k] == 0 && (char)(k + 'A') != 'J') {
//             keyMat[i][j] = (char)(k + 'A');
//             j++;
//             if (j == 5) {
//                 i++;
//                 j = 0;
//             }
//         }
//     }
// }

// // Function for searching characters in the key matrix
// void search(char keyMat[5][5], char a, char b, int arr[]) {
//     if (a == 'J')
//         a = 'I';
//     else if (b == 'J')
//         b = 'I';
//     for (int i = 0; i < 5; i++) {
//         for (int j = 0; j < 5; j++) {
//             if (keyMat[i][j] == a) {
//                 arr[0] = i;
//                 arr[1] = j;
//             } else if (keyMat[i][j] == b) {
//                 arr[2] = i;
//                 arr[3] = j;
//             }
//         }
//     }
// }

// // Function for preparing the plaintext for encryption
// int prep(char str[], int p) {
//     int sub = p;
//     for (int i = 0; i < sub; i += 2) {
//         if (str[i] == str[i + 1]) {
//             for (int j = sub; j > i + 1; j--) {
//                 str[j] = str[j - 1];
//             }
//             // Instead of inserting 'X', shift elements to the right
//             if (str[i] != 'X') {
//                 str[i + 1] = 'X';
//             } else {
//                 str[i + 1] = 'Z'; // Use 'Z' if 'X' is already present
//             }
//             sub++;
//         }
//     }
//     // If the length is odd, append 'Z' to the end
//     if (sub % 2 != 0) {
//         str[sub++] = 'Z';
//     }
//     str[sub] = '\0';
//     return sub;
// }

// // Function for encryption using Playfair Cipher
// void encrypt(char str[], char keyMat[5][5], int pos) {
//     int a[4];
//     for (int i = 0; i < pos; i += 2) {
//         search(keyMat, str[i], str[i + 1], a);
//         if (a[0] == a[2]) {
//             str[i] = keyMat[a[0]][(a[1] + 1) % 5];
//             str[i + 1] = keyMat[a[0]][(a[3] + 1) % 5];
//         } else if (a[1] == a[3]) {
//             str[i] = keyMat[(a[0] + 1) % 5][a[1]];
//             str[i + 1] = keyMat[(a[2] + 1) % 5][a[1]];
//         } else {
//             str[i] = keyMat[a[0]][a[3]];
//             str[i + 1] = keyMat[a[2]][a[1]];
//         }
//     }
// }

// // Function for decryption using Playfair Cipher
// // Function for decryption using Playfair Cipher
// void decrypt(char str[], char keyMat[5][5], int pos) {
//     int a[4];
//     for (int i = 0; i < pos; i += 2) {
//         search(keyMat, str[i], str[i + 1], a);
//         if (a[0] == a[2]) {
//             str[i] = keyMat[a[0]][(a[1] + 4) % 5];
//             str[i + 1] = keyMat[a[0]][(a[3] + 4) % 5];
//         } else if (a[1] == a[3]) {
//             str[i] = keyMat[(a[0] + 4) % 5][a[1]];
//             str[i + 1] = keyMat[(a[2] + 4) % 5][a[1]];
//         } else {
//             str[i] = keyMat[a[0]][a[3]];
//             str[i + 1] = keyMat[a[2]][a[1]];
//         }
//     }
//     // Remove 'X' characters added during encryption but not part of original plaintext
//     for (int i = 0; i < pos; i++) {
//         if (str[i] == 'X' && str[i + 1] == str[i - 1]) {
//             for (int j = i; j < pos; j++) {
//                 str[j] = str[j + 1];
//             }
//             pos--;
//         }
//     }
//     str[pos] = '\0';
// }


// // Main function
// int main() {
//     char string[200], keyString[200];
//     printf("Enter key: ");
//     scanf("%[^\n]s", keyString);
//     printf("Enter plaintext: ");
//     scanf("\n");
//     scanf("%[^\n]s", string);

//     // Prepare key and plaintext
//     int ks = strlen(keyString);
//     int ps = strlen(string);
//     toUpperCase(keyString, ks);
//     toUpperCase(string, ps);
//     ks = removeSpaces(keyString, ks);
//     ps = removeSpaces(string, ps);
//     ps = prep(string, ps);

//     // Create key matrix
//     char keyMat[5][5];
//     createMatrix(keyString, ks, keyMat);

//     // Encrypt the plaintext
//     encrypt(string, keyMat, ps);
//     printf("Cipher text: %s\n", string);

//     // Decrypt the cipher text
//     decrypt(string, keyMat, ps);
//     printf("Decrypted text: %s\n", string);

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 30

void toLowerCase(char plain[], int ps) {
    int i;
    for (i = 0; i < ps; i++) {
        if (plain[i] > 64 && plain[i] < 91)
            plain[i] += 32;
    }
}

int removeSpaces(char* plain, int ps) {
    int i, count = 0;
    for (i = 0; i < ps; i++)
        if (plain[i] != ' ')
            plain[count++] = plain[i];
    plain[count] = '\0';
    return count;
}

void generateKeyTable(char key[], int ks, char keyT[5][5]) {
    int i, j, k, flag = 0, *dicty;

    dicty = (int*)calloc(26, sizeof(int));

    for (i = 0; i < ks; i++) {
        if (key[i] != 'j')
            dicty[key[i] - 97] = 2;
    }
    dicty['j' - 97] = 1;

    i = 0;
    j = 0;
    for (k = 0; k < ks; k++) {
        if (dicty[key[k] - 97] == 2) {
            dicty[key[k] - 97] -= 1;
            keyT[i][j] = key[k];
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }
    for (k = 0; k < 26; k++) {
        if (dicty[k] == 0) {
            keyT[i][j] = (char)(k + 97);
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }
}

void search(char keyT[5][5], char a, char b, int arr[]) {
    int i, j;

    if (a == 'j')
        a = 'i';
    else if (b == 'j')
        b = 'i';

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (keyT[i][j] == a) {
                arr[0] = i;
                arr[1] = j;
            }
            else if (keyT[i][j] == b) {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}

int mod5(int a) {
    if (a < 0)
        a += 5;
    return (a % 5);
}

void encrypt(char str[], char keyT[5][5], int ps) {
    int i, a[4];
    for (i = 0; i < ps; i += 2) {
        search(keyT, str[i], str[i + 1], a);
        if (a[0] == a[2]) {
            str[i] = keyT[a[0]][mod5(a[1] + 1)];
            str[i + 1] = keyT[a[0]][mod5(a[3] + 1)];
        }
        else if (a[1] == a[3]) {
            str[i] = keyT[mod5(a[0] + 1)][a[1]];
            str[i + 1] = keyT[mod5(a[2] + 1)][a[1]];
        }
        else {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
}

void decrypt(char str[], char keyT[5][5], int ps) {
    int i, a[4];
    for (i = 0; i < ps; i += 2) {
        search(keyT, str[i], str[i + 1], a);
        if (a[0] == a[2]) {
            str[i] = keyT[a[0]][mod5(a[1] - 1)];
            str[i + 1] = keyT[a[0]][mod5(a[3] - 1)];
        }
        else if (a[1] == a[3]) {
            str[i] = keyT[mod5(a[0] - 1)][a[1]];
            str[i + 1] = keyT[mod5(a[2] - 1)][a[1]];
        }
        else {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
}

void playfairCipher(char str[], char key[]) {
    char ps, ks, keyT[5][5];

    ks = strlen(key);
    ks = removeSpaces(key, ks);
    toLowerCase(key, ks);

    ps = strlen(str);
    toLowerCase(str, ps);
    ps = removeSpaces(str, ps);

    generateKeyTable(key, ks, keyT);

    
    encrypt(str, keyT, ps);
    printf("Encrypted text: %s\n", str);

    // Decryption
    decrypt(str, keyT, ps);
    printf("Decrypted text: %s\n", str);
}

int main() {
    char str[SIZE], key[SIZE];

    printf("Enter the key text: ");
    fgets(key, SIZE, stdin);
    key[strcspn(key, "\n")] = '\0'; 

    printf("Enter the text to encrypt/decrypt: ");
    fgets(str, SIZE, stdin);
    str[strcspn(str, "\n")] = '\0'; 
    playfairCipher(str, key);

    return 0;
}