#include <stdio.h>
#include <string.h>

int modInverse(int a, int m) {
    a = a % m;
    int x;
    for (x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

void affineCipherDecrypt(int a, int b, char *ciphertext) {
    int len = strlen(ciphertext);
    int i;
    for (i = 0; i < len; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            int c = ciphertext[i] - 'A';
            int p = (modInverse(a, 26) * (c - b + 26)) % 26;
            ciphertext[i] = 'A' + p;
        }
    }
}

int main() {
    char ciphertext[1000];
    printf("Enter the ciphertext: ");
    scanf("%[^\n]s", ciphertext);

    // Assuming "B" corresponds to "E" and "U" corresponds to "T"
    int a, b;
    a = 14; // Based on the assumption that "B" (most frequent) corresponds to "E"
    b = (20 - ('U' - 'A') * modInverse(a, 26) + 26) % 26; // Decrypt "U" (second most frequent) to "T"

    affineCipherDecrypt(a, b, ciphertext);

    printf("Decrypted text: %s\n", ciphertext);

    return 0;
}

