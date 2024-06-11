
void clearString(unsigned char *buffer, int size);

void trim_string_at_newLine(unsigned char *buffer);

//If the strings are equal, it returns 0.
//If str1 is less than str2, it returns a negative value.
//If str1 is greater than str2, it returns a positive value.
int compareStrings(const unsigned char *str1, const unsigned char *str2);

void strcpy_custom(char *dest, const char *src);
