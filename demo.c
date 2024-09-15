#include <stdio.h>
#include "numbers.h"
#include <string.h>

int main()
{
    run_tests();
    while (1)
    {
        printf("Enter a number and get it back in danish words: ");
        int number;
        scanf(" %d", &number);

        print_options();
        char format_choice;
        scanf(" %c", &format_choice);

        struct NumberFormat format;
        switch (format_choice)
        {
        case 'l':
            format.et = LAST;
            format.og = LAST;
            format.e = LAST;
            break;
        case 'n':
            format.et = NEVER;
            format.og = NEVER;
            format.e = NEVER;
            break;
        case 'e':
            format.et = EVERY;
            format.og = EVERY;
            format.e = EVERY;
            break;
        }
        printf("Using the format: Og: %d. Et: %d. E: %d\n", format.og, format.et, format.e);

        char result_string[255] = "";

     
            number_to_danish(number, result_string, format);
        
        printf("%d = %s\n", number, result_string);
    }
    return 0;
}

void print_options(){
    printf("Choose a format for the occurence of:\n'et' before hundreds / thousands\n'e' after hundreds / thousands\n'og' between numbers\n");
    printf("(l): Last number\n");
    printf("(n): Never\n");
    printf("(e): Every number\n");
}

void run_tests()
{
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

    wrongs_corrects[run_test(111111111, f_last, "hundred elleve millioner hundred elleve tusind et hundrede og elleve")]++;

    wrongs_corrects[run_test(111111111, f_never, "hundred elleve millioner hundred elleve tusind hundred elleve")]++;

    wrongs_corrects[run_test(111111111, f_every, "et hundrede og elleve millioner og et hundrede og elleve tusinde og et hundrede og elleve")]++;

    wrongs_corrects[run_test(1100001000, f_every, "en milliard og et hundrede millioner og et tusinde")]++;

    wrongs_corrects[run_test(1100001000, f_never, "en milliard hundred millioner tusind")]++;

    wrongs_corrects[run_test(1100001000, f_last, "en milliard hundred millioner og et tusinde")]++;

    // printf(CYAN "\nRan %d tests", (wrongs_corrects[0] + wrongs_corrects[1]), RESET, RED "Failed: %d.", wrongs_corrects[0], RESET, GREEN "Passed: %d\n\n", wrongs_corrects[1], RESET);
    printf(CYAN "\nRan %d tests:\n" RESET, (wrongs_corrects[0] + wrongs_corrects[1]));
    printf(GREEN "Passed: %d\n" RESET, wrongs_corrects[1]);
    printf(RED "Failed: %d\n." RESET, wrongs_corrects[0]);
    printf("=======================\n");
}

int run_test(int number, struct NumberFormat format, char *expected)
{
    char result_string[255] = "";
    number_to_danish(number, result_string, format);
    int match = assert_equals(result_string, expected);
    if (!match)
    {
        printf(RED "\nTets failed! Expected: %s.\n" RESET, expected);
        printf(MAGENTA "Actual: %s.\n" RESET, result_string);
        printf(YELLOW "Format: Og: %d. Et: %d. E: %d\n\n" RESET, format.og, format.et, format.e);
        // printf(RED "\nFail! Expected: %s. Actual: %s. Format: Og: %d. Et: %d. E: %d\n\n" RESET, expected, result_string, format.og, format.et, format.e);
        // printf("\nFail! Expected: %s. Actual: %s. Format: Og: %d. Et: %d. E: %d\n\n", expected, result_string, format.og, format.et, format.e);
    }
    return match;
}

int assert_equals(char *str1, char *str2)
{
    int match = strcmp(str1, str2) == 0;
    return match;
}