#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 10

// Function to check if the key matrix is valid (invertible)
int is_valid_key(int key[MAX_SIZE][MAX_SIZE], int size) {
int det = 0;
// Calculate determinant of the key matrix
if (size == 2) {
det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
} else if (size == 3) {
det = key[0][0] * (key[1][1] * key[2][2] - key[1][2] * key[2][1]) -
key[0][1] * (key[1][0] * key[2][2] - key[1][2] * key[2][0]) +
key[0][2] * (key[1][0] * key[2][1] - key[1][1] * key[2][0]);
}
// Check if determinant is non-zero (key is invertible)
return det != 0;
}

// Function to encrypt the message using the Hill Cipher algorithm
void hill_encrypt(char *message, int key[MAX_SIZE][MAX_SIZE], int size) {
int len = strlen(message);
int i, j, k, sum;
int plain[MAX_SIZE];

// Convert message to uppercase
for (i = 0; i < len; i++) {
message[i] = toupper(message[i]);
}

// Pad the message with 'X' if its length is not a multiple of the key size
while (len % size != 0) {
message[len++] = 'X';
}
message[len] = '\0';

// Encrypt the message
for (i = 0; i < len; i += size) {               
// Convert block of characters to numbers
for (j = 0; j < size; j++) {
plain[j] = message[i + j] - 'A';
}

// Matrix multiplication
for (j = 0; j < size; j++) {
sum = 0;
for (k = 0; k < size; k++) {
sum += key[j][k] * plain[k];
}
// Take modulus 26 to wrap around the alphabet
message[i + j] = (sum % 26) + 'A';
}
}
}

int main() {
int key[MAX_SIZE][MAX_SIZE];
int key_size, i, j;
char message[1000];

// Input key size
printf("Enter the size of the key matrix (2 or 3): ");
scanf("%d", &key_size);

// Input key matrix
printf("Enter the elements of the key matrix:\n");
for (i = 0; i < key_size; i++) {
for (j = 0; j < key_size; j++) {
scanf("%d", &key[i][j]);
}
}

// Check if the key matrix is valid (invertible)
if (!is_valid_key(key, key_size)) {
printf("Invalid key matrix. Please enter a valid key matrix.\n");
return 1;
}

// Input message
printf("Enter the message to be encrypted (only alphabetic characters): ");
scanf("%s", message);

// Encrypt the message
hill_encrypt(message, key, key_size);

// Output the encrypted message
printf("Encrypted message: %s\n", message);
return 0;


}


