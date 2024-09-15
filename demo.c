#include <stdio.h>
#include "numbers.h"
#include <string.h>

int main()
{
    run_tests();
    while (1){
        printf("Enter a number and get it back in danish words: ");
        
        int number;
        scanf(" %d", &number);
        char result_string[255] = "";
        //                             og    e     et
        struct NumberFormat format = {LAST, LAST, LAST};
        // int_to_danish_word(number, result_string);
        if (number == 0)
        {
            strcat(result_string, "nul");
            return 0;
        }
        else {
        number_to_danish(number, result_string, format);
        }
        printf("%d = %s\n", number, result_string);
    }
    return 0;
}

void run_tests(){
    // int corrects = 0;
    // int wrongs = 0;
    // [0] = wrongs, [1] = rights
    int wrongs_corrects[] = {0, 0};
    
    // int number = 1011;
    struct NumberFormat f_last = {LAST, LAST, LAST};
    struct NumberFormat f_never = {NEVER, NEVER, NEVER};
    struct NumberFormat f_every = {EVERY, EVERY, EVERY};
    // Runs the test and increments either the wrongs or the rights
    wrongs_corrects[run_test(1011, f_last, "et tusinde og elleve")]++;

    wrongs_corrects[run_test(1011, f_never, "tusind elleve")]++;

    wrongs_corrects[run_test(1011, f_every, "et tusinde og elleve")]++;

    wrongs_corrects[run_test(111111111, f_last, "tusind elleve")]++;

    wrongs_corrects[run_test(1011, f_never, "tusind elleve")]++;

    printf("\nWrongs: %d. Corrects: %d\n\n", wrongs_corrects[0], wrongs_corrects[1]);
}

int run_test(int number, struct NumberFormat format, char *expected)
{
    char result_string[255] = "";
    number_to_danish(number, result_string, format);
    int match = assert_equals(result_string, expected);
    if (!match)
    {
        printf("\nFail! Expected: %s. Actual: %s. Format: Og: %d. Et: %d. E: %d\n\n", expected, result_string, format.og, format.et, format.e);
    }
    return match;
}

int assert_equals(char *str1, char *str2){
    int match = strcmp(str1, str2) == 0 ? 1 : 0;
    return match;
}