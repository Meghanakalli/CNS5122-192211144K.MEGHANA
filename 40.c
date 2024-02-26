#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// English letter frequencies (source: https://en.wikipedia.org/wiki/Letter_frequency)
const float english_frequencies[ALPHABET_SIZE] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, // A-G
    0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, // H-N
    0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, // O-U
    0.00978, 0.02360, 0.00150, 0.01974, 0.00074                    // V-Z
};

// Structure to store letter frequencies
typedef struct {
    char letter;
    float frequency;
} LetterFrequency;

// Function to count letter frequencies in a string
void countLetterFrequencies(const char *text, LetterFrequency *frequencies) {
    int counts[ALPHABET_SIZE] = {0};
    int i;

    // Count occurrences of each letter
    for (i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if (isalpha(c)) {
            int index = tolower(c) - 'a';
            counts[index]++;
        }
    }

    // Calculate frequencies
    int total_letters = 0;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        total_letters += counts[i];
    }

    for (i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i].letter = 'a' + i;
        frequencies[i].frequency = (float)counts[i] / total_letters;
    }
}

// Comparison function for qsort
int compareFrequency(const void *a, const void *b) {
    const LetterFrequency *freqA = (const LetterFrequency *)a;
    const LetterFrequency *freqB = (const LetterFrequency *)b;

    if (freqA->frequency < freqB->frequency) {
        return 1;
    } else if (freqA->frequency > freqB->frequency) {
        return -1;
    } else {
        return 0;
    }
}

// Function to decrypt ciphertext using a given key
void decryptWithKey(const char *ciphertext, const char *key, char *plaintext) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            plaintext[i] = key[tolower(c) - 'a'] + base;
        } else {
            plaintext[i] = c;
        }
    }
}

int main() {
    char ciphertext[1000];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    // Calculate letter frequencies of the ciphertext
    LetterFrequency ciphertext_frequencies[ALPHABET_SIZE];
    countLetterFrequencies(ciphertext, ciphertext_frequencies);

    // Sort letter frequencies in descending order
    qsort(ciphertext_frequencies, ALPHABET_SIZE, sizeof(LetterFrequency), compareFrequency);

    // Get the most likely plaintext letters based on frequency analysis
    char key[ALPHABET_SIZE + 1];
    int i;
    for ( i = 0; i < ALPHABET_SIZE; i++) {
        key[i] = ciphertext_frequencies[i].letter;
    }
    key[ALPHABET_SIZE] = '\0';

    // Decrypt ciphertext using the obtained key
    char plaintext[1000];
    decryptWithKey(ciphertext, key, plaintext);

    printf("Top 10 possible plaintexts (in rough order of likelihood):\n");
    for (i = 0; i < 10; i++) {
        printf("%d. %s\n", i + 1, plaintext);
        // Swap two adjacent letters in the key to get a new possible plaintext
        char temp = key[i];
        key[i] = key[i + 1];
        key[i + 1] = temp;
        decryptWithKey(ciphertext, key, plaintext);
    }

    return 0;
}

