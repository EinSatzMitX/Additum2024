#include "../include/util.h"

void clearString(unsigned char *buffer, int size){
   for (int i = 0; i < size; i++)
   {
      buffer[i] = '\0'; // Basically the same as 0, but cooler
   }
}

void trim_string_at_newLine(unsigned char *buffer){
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            break;
        }
    }
}

int compareStrings(const unsigned char *str1, const unsigned char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

// Function to copy a string from src to dest
void strcpy_custom(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';  // Null-terminate the string
}