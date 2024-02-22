#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char plaintext[], char key[]) {
    int i, j;
    int keyLength = strlen(key);
    int textLength = strlen(plaintext);

    for (i = 0; i < textLength; i++) {
        char currentChar = plaintext[i];

        if (isalpha(currentChar)) {
            char base = isupper(currentChar) ? 'A' : 'a';
            int offset = currentChar - base;

            // Use the corresponding monoalphabetic substitution cipher for the current letter
            char substitution = (key[i % keyLength] - 'A' + offset) % 26 + base;

            printf("%c", substitution);
        } else {
            // Non-alphabetic characters remain unchanged
            printf("%c", currentChar);
        }
    }
}

int main() {
    char plaintext[1000];
    char key[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the key: ");
    scanf("%s", key);

    printf("\nEncrypted Text: ");
    encrypt(plaintext, key);

    return 0;
}
