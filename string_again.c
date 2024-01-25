#include <stdio.h>
#include <stdlib.h>

/*
-- strlen(): - Returns the length of a string.
-- strcpy(): - Copies one string to another.   // Getting weird characters when accessing elements of string
-- Need to practice -- strcat(): - Concatenates two strings together.
-- Need to practice -- strcmp(): - Compares two strings.
strchr(): - Finds the first occurrence of a character in a string.
strrchr(): - Finds the last occurrence of a character in a string.
strlwr(): - Converts all characters in a string to lowercase.
strupr(): - Converts all characters in a string to uppercase.
strrev(): - Reverses the order of characters in a string.
*/

int mstrlen(char *str) {
    int count = 0;
    while (str[count] != '\0') {
        count++;
    }
    return count;
}

char *mstrcpy(char *dest, char *src) {
    while (src != NULL) {
        for (int i = 0; src[i] != '\0'; i++) {
            dest[i] = src[i];
            dest[i+1] = '\0';
        }
        return dest;
    }
    return NULL;
}

char *mstrcat(char *dest, char *src) {
    int destlen = mstrlen(dest);
    int srclen = mstrlen(src);
    if (src == NULL) {
        printf("Source is empty\n");
        return NULL;
    }
    for (int i = 0; i < srclen; i++) {
        dest[destlen+i] = src[i];
    }
    dest[destlen+srclen] = '\0';
    return dest;
}

int mstrcmp(char *str1, char *str2) {
    if (str1 == NULL || str2 == NULL) {
        printf("Can't compare null values\n");
        return -1;
    }
    int counter = 0;
    while (str1[counter] == str2[counter] && str1[counter] != '\0' && str2[counter] != '\0') {
        counter++;
    }
    if (str1[counter] < str2[counter]) {
        return -1;
    }
    else if (str1[counter] > str2[counter]) {
        return 1;
    }
    else {
        return 0;
    }
}



int main(void) {

    char *str1 = "This is a test";
    printf("Length: %d\n", mstrlen(str1));
    char str2[mstrlen(str1)];
    mstrcpy(str2, str1);
    printf("String 1: %s\nString 2: %s\n",str1, str2);
    printf("Length 1: %d\nLength 2: %d\n", mstrlen(str1), mstrlen(str2));
    
    for (int i = 0; str2[i] != '\0'; i++) {
        printf("%c\n", str2[i]);
    }

    char str3[256];
    mstrcpy(str3, str1);
    mstrcat(str3, str1);

    char *str4 = "This is a test";

    printf("%s\n", str3);
    printf("%s\n", str1);

    printf("Compare str1, str2: %d\n", mstrcmp(str1, str2));
    printf("Compare str1, str3: %d\n", mstrcmp(str1, str3));
    printf("Compare str1, str4: %d\n", mstrcmp(str1, str4));
    printf("Compare str1, str3: %d\n", mstrcmp(str1, NULL));

}