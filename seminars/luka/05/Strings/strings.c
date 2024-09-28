#include <stdio.h>
#include <stdlib.h>

/*
"abcdefg"
"abcdgf"

*/

int strcmp(const char *s1, const char *s2)
{
    while (*s1 != 0 && *s2 != 0) {
        int difference = *s1 - *s2;
        
        if (difference != 0) {
            return difference;
        }
        
        s1++;
        s2++;
    }

    // if (*s1 == 0 && *s2 == 0) {
    //     /*
    //         s1 = "abcd"
    //         s2 = "abcd"
        
    //     */
        
    //     return 0;
    // } else if (*s1 == 0) {
    //     /*
    //         s1 = "abcd"
    //         s2 = "abcde"
    //     */

    //     return -1;
    // }

    // /*
    //     s1 = "abcde"
    //     s2 = "abcd"
    // */

    // return 1;

    return *s1 - *s2;

}

char *strcpy(char *dest, const char *src)
{   
    char *orig_dest = dest;
    // for (const char *ptr = src; ptr != 0; ptr++) {
    //     *dest = *ptr;
    //     dest++;
    // }

    while (*src) {
        *dest++ = *src++;
    }

    *dest = 0;

    return orig_dest;
}

size_t strlen(const char *s)
{
    size_t size = 0;

    while(*s++) {
        size++;
    }

    return size; 
}

// dest = "abcd" \0
// src = "efg" \0
// dest = "abcdefg" \0

char *strcat(char *dest, const char *src)
{
    size_t dest_len = strlen(dest);

    char *target = dest + dest_len;
    strcpy(target, src);

    return dest;
}

char *strdup(const char *s)
{
    size_t string_len = strlen(s);

    char *heap_string = malloc(string_len + 1);
   
    memcpy(heap_string, s, string_len + 1);

    return heap_string;
}

// char arr[4];
// memset(arr, 'f', 4);
// {'f', 'f', 'f', 'f'}


void *memset(void *s, int c, size_t n)
{
    for (int i = 0; i < n; i++) {
        char *target = (char *) s + i;
        *target = c;
    }

    return s;
}

int main()
{
    // strcmp
    printf("strcmp:\n");
    char *s1 = "abcde";
    char *s2 = "bcde";
    int strcmpRes = strcmp(s1, s2);
    if (strcmpRes > 0)
    {
        printf("    s1: %s is greater than s2: %s by %d\n", s1, s2, strcmpRes);
    }
    else if (strcmpRes < 0)
    {
        printf("    s1: %s is less than s2: %s by %d\n", s1, s2, strcmpRes);
    }
    else
    {
        printf("    s1: %s is equal to s2: %s\n", s1, s2);
    }
    printf("\n");

    printf("strcmp:\n");
    char *s1_1 = "abcde";
    char *s2_2 = "bcde";
    int strcmpRes_2 = strcmp(s1_1, s2_2);
    if (strcmpRes_2 > 0)
    {
        printf("    s1: %s is greater than s2: %s by %d\n", s1, s2, strcmpRes_2);
    }
    else if (strcmpRes_2 < 0)
    {
        printf("    s1: %s is less than s2: %s by %d\n", s1, s2, strcmpRes_2);
    }
    else
    {
        printf("    s1: %s is equal to s2: %s\n", s1_1, s2_2);
    }
    printf("\n");

    // strcpy
    printf("strcpy:\n");
    char buffer[50];
    char *strToCopy = "abcde";
    printf("    function returns: %s\n", strcpy(buffer, strToCopy));
    printf("    buffer string after function call: %s\n", buffer);
    printf("\n");

    // strlen
    printf("strlen:\n");
    char *s3 = "Programming";
    char *s4 = "Paradigms";
    printf("    s3: %s len is %zu\n", s3, strlen(s3));
    printf("    s4: %s len is %zu\n", s4, strlen(s4));
    printf("\n");

    // strcat
    printf("strcat:\n");
    char buffer2[50];
    strcpy(buffer2, "Start ");

    printf("    function returns: %s\n", strcat(buffer2, "First"));
    printf("    function returns: %s\n", strcat(buffer2, " Second"));
    printf("    function returns: %s\n", strcat(buffer2, " Third"));
    printf("    buffer2 after function calls: %s\n", buffer2);
    printf("\n");

    // strdup
    printf("strdup:\n");
    char *originStr = "Strdup First Example";
    char *newStr = strdup("Strdup First Example");
    printf("    newStr: %s\n", newStr);
    printf("    originStr value address is %p\n", (void *)originStr);
    printf("    newStr value address is %p\n", (void *)newStr);
    printf("\n");

    // memset
    printf("memset:\n");
    char memsetBuffer[50];
    memset((void *)memsetBuffer, 'A', 40);
    printf("    buffer after memset call: %s\n", memsetBuffer);
}