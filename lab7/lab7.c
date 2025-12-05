#include <stdio.h>

#define ALPHABET 26

void find_unique_latin_chars(char *str) {
    int count[ALPHABET] = {0};

    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];
        if (c >= 'a' && c <= 'z') {
            count[c - 'a']++;
        }
        else if (c >= 'A' && c <= 'Z') {
            count[c - 'A']++;
        }
    }
    
    int found = 0;
    for (int i = 0; i < ALPHABET; i++) {
        if (count[i] == 1) {
            printf("%c ", 'a' + i);
            found = 1;
        }
    }
    
    if (!found) {
        printf("таких символов нет");
    }
    printf("\n");
}

int main() {
    char *str = "Hello world";
    find_unique_latin_chars(str);
    
    return 0;
}