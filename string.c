#include <stdio.h>
#include <stdlib.h>

int mstrlen(char *string) {
    // Returns the length of a string
    int counter = 0;
    while (string[counter] != '\0') {
        counter++;
    }
    return counter;
}

char *mstrcpy(char *dest, char *src) {
    // Copies one string to another
    int counter = 0;
    if (src == NULL) {
        printf("Source is empty\n");
        return NULL;
    }
    while (src[counter] != '\0' && src != NULL) {
        dest[counter] = src[counter];
        counter++;
    }
    dest[counter+1] = '\0';
    return dest;
}

char *mstrcat(char *dest, char *src) {
    // Concatenates two strings together
    int destlen = mstrlen(dest);
    if (src == NULL) {
        printf("Source is empty\n");
        return NULL;
    }

    printf("Destination length = %d", destlen);

    for (int i = 0; i < mstrlen(src); i++) {
        dest[destlen+i] = src[i];
    }

    return dest;
}

int mstrcmp(char *str1, char *str2) {
    // Compares two strings and returns an integer value indicating whether the first string is less than, equal to, or greater than

    if (str1 == NULL || str2 == NULL) {
        printf("Empty string");
        return -1;
    }

    for (int i = 0; str1 != '\0' && str2 != '\0'; i++) {
        if (str1 < str2) {
            return -1;
        }
        else if (str1 > str2) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

int mstrncmp(char *str1, char *str2, int n) {
    // Compares two strings and returns an integer value indicating whether the first string is less than, equal to, or greater than

    if (str1 == NULL || str2 == NULL) {
        printf("Empty string");
        return -1;
    }

    for (int i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) {
        if (i == n) {
            return -1;
        }
        if (str1 < str2) {
                return -1;
        }
        else if (str1 > str2) {
                return 1;
            }
            else {
                return 0;
            }
        }
    }
}

int *mstrstr(char **haystack, char *needle) {

}

char *mstrtok(char *str, char delim) {
    // Breaks a string into tokens based on a specific delimiter
    // If (char == delimiter), add all previous chars 
    // set reference pointer to the character after delimiter so it can be called again with NULL

    if (str == NULL) {
        return NULL;
    }

    // returns a pointer to the character after the delimiter
    // sets previous characters to \0
    char *temp = NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        printf("%c\n", str[i]);
        if (str[i] == delim) {
            temp[i+1] = '\0';
            return temp;
        }
        else {
            temp[i] = str[i];
        }
        str[i] = '\0';
    }

}

char *mrevstr(char *str) {

    
}

int main(void) {

    // Testing strlen
    char *test = "This is my string";
    printf("Length of string is %d\n", mstrlen(test));

    // Testing strcpy
    char copy[256]; 
    printf("Copy before mstrcpy - %s\n", copy);
    mstrcpy(copy, test);
    printf("Test = %s\nCopy = %s\n", test, copy);

    // Testing strcat
    char cat[256] = "This should be concatenated ";
    mstrcat(cat, copy);
    printf("Copy = %s\nCat = %s\n", copy, cat);

    printf("Testing strcmp on copy>cat - %d\n", mstrcmp(copy, cat));
    printf("Testing strcmp on copy>test - %d\n", mstrcmp(copy, test));
    printf("%s %d\n%s %d\n", copy, mstrlen(copy), test, mstrlen(test));

    char str1 = "SHOULD WORKSS";
    char str2 = "SHOULD WORKS";

    printf("%d\n", mstrcmp(str1, str2));
    printf("%d\n", mstrncmp(str1, str2, 20));

    char *tokens = mstrtok(test, ' ');          // USE SINGLE QUOTES WTF

    //printf("%d\n", mstrstr(&str1, "OULD"));

    return 0;
}