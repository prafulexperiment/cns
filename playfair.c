#include <stdio.h>
#include <string.h>
#define SIZE 30

void generateKeyTable(char key[], char keyT[5][5]) {
    int dicty[26] = {0};
    int i, j, k, idx = 0;

    for (i = 0; i < strlen(key); i++) {
        if (key[i] != 'j' && dicty[key[i] - 'a'] == 0) {
            dicty[key[i] - 'a'] = 1;
            keyT[idx / 5][idx % 5] = key[i];
            idx++;
        }
    }

    for (k = 0; k < 26; k++) {
        if (k + 'a' != 'j' && dicty[k] == 0) {
            keyT[idx / 5][idx % 5] = k + 'a';
            idx++;
        }
    }
}

void search(char keyT[5][5], char a, char b, int arr[]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (keyT[i][j] == a) {
                arr[0] = i;
                arr[1] = j;
            }
            if (keyT[i][j] == b) {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}

void encrypt(char str[], char keyT[5][5]) {
    int a[4];
    for (int i = 0; i < strlen(str); i += 2) {
        search(keyT, str[i], str[i + 1], a);
        if (a[0] == a[2]) {
            str[i] = keyT[a[0]][(a[1] + 1) % 5];
            str[i + 1] = keyT[a[2]][(a[3] + 1) % 5];
        } else if (a[1] == a[3]) {
            str[i] = keyT[(a[0] + 1) % 5][a[1]];
            str[i + 1] = keyT[(a[2] + 1) % 5][a[3]];
        } else {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
}

void decrypt(char str[], char keyT[5][5]) {
    int a[4];
    for (int i = 0; i < strlen(str); i += 2) {
        search(keyT, str[i], str[i + 1], a);
        if (a[0] == a[2]) {
            str[i] = keyT[a[0]][(a[1] + 4) % 5];
            str[i + 1] = keyT[a[2]][(a[3] + 4) % 5];
        } else if (a[1] == a[3]) {
            str[i] = keyT[(a[0] + 4) % 5][a[1]];
            str[i + 1] = keyT[(a[2] + 4) % 5][a[3]];
        } else {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
}
void removeExtraChar(char original[], char decrypted[]) {
    int orig_len = strlen(original);
    int dec_len = strlen(decrypted);

    if (dec_len > orig_len) {
        decrypted[dec_len - 1] = '\0';
    }
}

int main() {
    char str[SIZE], key[SIZE];
    char keyT[5][5];

    printf("Enter the key text: ");
    fgets(key, SIZE, stdin);
    key[strcspn(key, "\n")] = '\0';

    printf("Enter the text to encrypt: ");
    fgets(str, SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';

    generateKeyTable(key, keyT);
    
    printf("Original text: %s\n", str);
    char original[SIZE];
    strcpy(original,str);
    encrypt(str, keyT);
    printf("Encrypted text: %s\n", str);
    
  

    decrypt(str, keyT);
    removeExtraChar(original,str);
    printf("Decrypted text: %s\n", str);

    return 0;
}
