#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

#define MSG_MAX     128U
#define ALPHABET    26U

static char message[MSG_MAX];     /* what we are working on right now */
static char scratch[MSG_MAX];     /* somewhere to build the answer     */
static uint8_t shiftKey = 3U;     /* 0..25 (default shift 3)           */

static void clearBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static void readMessage(void) {
    printf("Enter a message (max %u chars): ", MSG_MAX - 1U);
    if (fgets(message, (int)MSG_MAX, stdin) != NULL) {
        /* Remove trailing newline if present */
        uint16_t i = 0U;
        while (message[i] != '\0') {
            if (message[i] == '\n' || message[i] == '\r') {
                message[i] = '\0';
                break;
            }
            i++;
        }
    } else {
        message[0] = '\0';
    }
}

static uint16_t textLength(const char *s) {
    uint16_t len = 0U;
    while (s[len] != '\0' && len < (MSG_MAX - 1U)) {
        len++;
    }
    return len;
}

static char shiftChar(char c, uint8_t key) {
    key = key % ALPHABET;
    if (c >= 'A' && c <= 'Z') {
        return (char)('A' + (c - 'A' + key) % ALPHABET);
    } else if (c >= 'a' && c <= 'z') {
        return (char)('a' + (c - 'a' + key) % ALPHABET);
    }
    return c;
}

static void encode(void) {
    uint16_t len = textLength(message);
    for (uint16_t i = 0U; i <= len; i++) {
        scratch[i] = shiftChar(message[i], shiftKey);
    }
    printf("Encoded message: %s\n", scratch);
}

static void decode(void) {
    uint16_t len = textLength(message);
    uint8_t decodeKey = (ALPHABET - (shiftKey % ALPHABET)) % ALPHABET;
    for (uint16_t i = 0U; i <= len; i++) {
        scratch[i] = shiftChar(message[i], decodeKey);
    }
    printf("Decoded message: %s\n", scratch);
}

static void reverseText(char *s, uint16_t n) {
    if (n == 0U) return;
    uint16_t left = 0U;
    uint16_t right = n - 1U;
    while (left < right) {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++;
        right--;
    }
}

static uint16_t countVowels(const char *s) {
    uint16_t count = 0U;
    while (*s != '\0') {
        char c = (char)tolower((unsigned char)*s);
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        }
        s++;
    }
    return count;
}

static uint8_t isPalindrome(const char *s) {
    char cleaned[MSG_MAX];
    uint16_t j = 0U;

    while (*s != '\0' && j < (MSG_MAX - 1U)) {
        if (isalpha((unsigned char)*s)) {
            cleaned[j++] = (char)tolower((unsigned char)*s);
        }
        s++;
    }
    cleaned[j] = '\0';

    if (j == 0U) return 0U;

    uint16_t left = 0U;
    uint16_t right = j - 1U;
    while (left < right) {
        if (cleaned[left] != cleaned[right]) {
            return 0U;
        }
        left++;
        right--;
    }
    return 1U;
}

static void letterHistogram(const char *s) {
    uint16_t freqs[ALPHABET] = {0U};
    while (*s != '\0') {
        char c = (char)tolower((unsigned char)*s);
        if (c >= 'a' && c <= 'z') {
            freqs[c - 'a']++;
        }
        s++;
    }

    printf("\n--- Letter Histogram ---\n");
    for (uint16_t i = 0U; i < ALPHABET; i++) {
        if (freqs[i] > 0U) {
            printf("%c | ", (char)('a' + i));
            for (uint16_t k = 0U; k < freqs[i]; k++) {
                putchar('#');
            }
            printf(" (%u)\n", freqs[i]);
        }
    }
    printf("------------------------\n");
}

static void showMessage(void) {
    uint16_t len = textLength(message);
    uint16_t vowels = countVowels(message);
    
    printf("\n========================================\n");
    printf(" MESSAGE REPORT\n");
    printf("----------------------------------------\n");
    printf(" Current Message : %s\n", message);
    printf(" Length          : %u characters\n", len);
    printf(" Current Key     : %u\n", shiftKey);
    printf(" Vowel Count     : %u\n", vowels);
    printf(" Is Palindrome   : %s\n", isPalindrome(message) ? "Yes" : "No");
    printf("========================================\n");
}

int main(void) {
    int choice = 0;
    /* Initialize with a default message */
    snprintf(message, MSG_MAX, "Hello Caesar");

    do {
        printf("\n--- Secret Message Machine Menu ---\n");
        printf("1. Read New Message\n");
        printf("2. Set Shift Key (0-25)\n");
        printf("3. Encode Message\n");
        printf("4. Decode Message\n");
        printf("5. Reverse Text (In Place)\n");
        printf("6. Count Vowels\n");
        printf("7. Check Palindrome\n");
        printf("8. Show Letter Histogram\n");
        printf("9. Show Message Report\n");
        printf("0. Exit\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            clearBuffer();
            continue;
        }
        clearBuffer();

        switch (choice) {
            case 1:
                readMessage();
                break;
            case 2: {
                int keyInput;
                printf("Enter shift key (0-25): ");
                if (scanf("%d", &keyInput) == 1) {
                    if (keyInput >= 0 && keyInput <= 25) {
                        shiftKey = (uint8_t)keyInput;
                        printf("Shift key updated to %u\n", shiftKey);
                    } else {
                        printf("Error: Key must be between 0 and 25!\n");
                    }
                } else {
                    printf("Invalid input!\n");
                }
                clearBuffer();
                break;
            }
            case 3:
                encode();
                break;
            case 4:
                decode();
                break;
            case 5:
                reverseText(message, textLength(message));
                printf("Message reversed in place: %s\n", message);
                break;
            case 6:
                printf("Vowel count: %u\n", countVowels(message));
                break;
            case 7:
                printf("Is palindrome? %s\n", isPalindrome(message) ? "Yes" : "No");
                break;
            case 8:
                letterHistogram(message);
                break;
            case 9:
                showMessage();
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Unknown option!\n");
                break;
            }
    } while (choice != 0);

    return 0;
}