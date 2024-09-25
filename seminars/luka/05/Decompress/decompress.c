#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// 0100 0111
// 00000100


// 1111 0000
// 1111 1111

// 0-9
// a b c d e f


// 0x0
int read_first_4_bits(char byte) {
    return (byte >> 4) & 0x0f;
}

int read_last_4_bits(char byte) {
    return byte & 0x0F;
}
// ptr      |pr | ptr + 2


// compressed_string_ptr + 1 + 0
//                      
// 00010010 | a | 00100011 | b | c | 00010001 | x = "aabcbcbcx"




// 0001 = 1
// 
// 00000000 | 00010001 | x = "x" 

void Decompress(char **data) {
    char *compressed_string_ptr = *data;

    int bytes_needed = 0;

    while (*compressed_string_ptr) {
        char marker_byte = *compressed_string_ptr;

        int bytes_to_read = read_first_4_bits(marker_byte);

        int bytes_to_repeat = read_last_4_bits(marker_byte);

        bytes_needed += bytes_to_read * bytes_to_repeat;

        compressed_string_ptr += bytes_to_read + 1;
    }

    char *decompressed_string = malloc(bytes_needed + 1);

    char *current_char = decompressed_string; 

    compressed_string_ptr = *data;

    while (*compressed_string_ptr) {
        char marker_byte = *compressed_string_ptr;

        int bytes_to_read = read_first_4_bits(marker_byte);

        int bytes_to_repeat = read_last_4_bits(marker_byte);


        for (int i = 0; i < bytes_to_repeat; i++) {
            for (int j = 0; j < bytes_to_read; j++) {
                *current_char = *(compressed_string_ptr + j + 1);
                current_char++;
            }
        }

        // ეს გვეწერა compressed_string_ptr += bytes_to_read * bytes_to_repeat + 1;
        // ეგ არასწორია იმიტოპმ რომ რეალურად მარკერ ბაიტებს შორის დაშორება არის bytes_to_read, აქ კი ვუმატებდით საბოლოო სტრინგში რამდენიც ჩავწერეთ მაგ რიცხვს.
        // ეს უნდა იყოს
        compressed_string_ptr += bytes_to_read + 1;
    }
    
    *current_char = 0;

    *data = decompressed_string;
}

void Test1()
{
    printf("Test1: ");
    char *expectValue = "aabcbcbcx";
    char *data = malloc(8);
    char *ptr = data;

    // 00010010|a|00100011|b|c|00010001|x
    *ptr = (1 << 4) + (1 << 1); // 00010010
    ptr++;
    *ptr = 'a';
    ptr++;
    *ptr = (1 << 5) + (1 << 1) + 1; // 00100011
    ptr++;
    *ptr = 'b';
    ptr++;
    *ptr = 'c';
    ptr++;
    *ptr = (1 << 4) + 1; // 00010001
    ptr++;
    *ptr = 'x';
    ptr++;
    *ptr = '\0';

    Decompress(&data);

    if (strcmp(expectValue, data) == 0)
    {
        printf("PASSED\n");
    }
    else
    {
        printf("FAILED after decompress: %s expected: %s\n", data, expectValue);
    }
    free(data);
}

void Test2()
{
    printf("Test2: ");
    char *expectValue = "yfoofoobar";
    char *data = malloc(11);
    char *ptr = data;

    // 00010001|y|00110010|f|o|o|00110001|b|a|r
    *ptr = (1 << 4) + 1; // 00010001
    ptr++;
    *ptr = 'y';
    ptr++;
    *ptr = (1 << 5) + (1 << 4) + (1 << 1); // 00110010
    ptr++;
    *ptr = 'f';
    ptr++;
    *ptr = 'o';
    ptr++;
    *ptr = 'o';
    ptr++;
    *ptr = (1 << 5) + (1 << 4) + 1; // 00110001
    ptr++;
    *ptr = 'b';
    ptr++;
    *ptr = 'a';
    ptr++;
    *ptr = 'r';
    ptr++;
    *ptr = '\0';

    Decompress(&data);

    if (strcmp(expectValue, data) == 0)
    {
        printf("PASSED\n");
    }
    else
    {
        printf("FAILED after decompress: %s expected: %s\n", data, expectValue);
    }
    free(data);
}

void Test3()
{
    printf("Test3: ");
    char *expectValue = "abcdefghfoofoo";
    char *data = malloc(14);
    char *ptr = data;

    // 10000001|a|b|c|d|e|f|g|h|00110010|f|o|o
    *ptr = (1 << 7) + 1; // 10000001
    ptr++;
    *ptr = 'a';
    ptr++;
    *ptr = 'b';
    ptr++;
    *ptr = 'c';
    ptr++;
    *ptr = 'd';
    ptr++;
    *ptr = 'e';
    ptr++;
    *ptr = 'f';
    ptr++;
    *ptr = 'g';
    ptr++;
    *ptr = 'h';
    ptr++;
    *ptr = (1 << 5) + (1 << 4) + (1 << 1); // 00110010
    ptr++;
    *ptr = 'f';
    ptr++;
    *ptr = 'o';
    ptr++;
    *ptr = 'o';
    ptr++;
    *ptr = '\0';

    Decompress(&data);

    if (strcmp(expectValue, data) == 0)
    {
        printf("PASSED\n");
    }
    else
    {
        printf("FAILED after decompress: %s expected: %s\n", data, expectValue);
    }
    free(data);
}

int main()
{
    Test1();
    Test2();
    Test3();
    return 0;
}
