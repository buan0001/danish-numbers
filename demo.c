#include <stdio.h>
#include "numbers.h"
#include <string.h>
#include <math.h>

int main()
{
    run_tests();
    while (1)
    {
        printf("Enter a number and get it back in danish words: ");
        double number;
        scanf(" %lf", &number);

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

        printf("Result: %s\n", result_string);
        // print_results(number, result_string);
    }
    return 0;
}

void print_results(double org_val, char *result_string)
{
    int amount_of_decimals = count_decimal_places(org_val);
    char format[512];
    sprintf(format, "\n%%.%dlf = %s\n", amount_of_decimals, result_string);
    printf("______________________________________\n");
    printf(format, org_val, result_string);
    printf("______________________________________\n\n");
}

int count_decimal_places(double value)
{
    int count = 0;
    // move the decimal one time to the right as long as the float to int conversion is lossy
    while (!is_effectively_int(value))
    {
        printf("Value: %lf\n", value);
        value *= 10;
        count++;
    }
    printf("DECIMAL Count: %d\n", count);
    return count;
}

int is_effectively_int(double value)
{
    // checks if the float's 0's change the value of the number or not
    return (floor(value) == value);
}

void print_options()
{
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
    wrongs_corrects[run_test(0, f_last, "nul")]++;

    wrongs_corrects[run_test(-123, f_last, "minus et hundrede og treogtyve")]++;

    wrongs_corrects[run_test(1011, f_last, "et tusinde og elleve")]++;

    wrongs_corrects[run_test(1011, f_never, "tusind elleve")]++;

    wrongs_corrects[run_test(1011, f_every, "et tusinde og elleve")]++;

    wrongs_corrects[run_test(111111111, f_last, "hundred elleve millioner hundred elleve tusind et hundrede og elleve")]++;

    wrongs_corrects[run_test(111111111, f_never, "hundred elleve millioner hundred elleve tusind hundred elleve")]++;

    wrongs_corrects[run_test(111111111, f_every, "et hundrede og elleve millioner og et hundrede og elleve tusinde og et hundrede og elleve")]++;

    wrongs_corrects[run_test(1100001000, f_every, "en milliard og et hundrede millioner og et tusinde")]++;

    wrongs_corrects[run_test(1100001000, f_never, "en milliard hundred millioner tusind")]++;

    wrongs_corrects[run_test(1100001000, f_last, "en milliard hundred millioner og et tusinde")]++;
    
    printf(CYAN "\nRan %d tests:\n" RESET, (wrongs_corrects[0] + wrongs_corrects[1]));
    printf(GREEN "Passed: %d\n" RESET, wrongs_corrects[1]);
    printf(RED "Failed: %d\n." RESET, wrongs_corrects[0]);
    printf("=======================\n");
}

int run_test(double number, struct NumberFormat format, char *expected)
{
    char result_string[1024] = "";
    number_to_danish(number, result_string, format);
    print_results(number, result_string);
    int match = assert_equals(result_string, expected);
    if (!match)
    {
        printf(RED "\nTets failed! Expected: %s.\n" RESET, expected);
        printf(MAGENTA "Actual: %s.\n" RESET, result_string);
        printf(YELLOW "Format: Og: %d. Et: %d. E: %d\n\n" RESET, format.og, format.et, format.e);

    }
    return match;
}

int assert_equals(char *str1, char *str2)
{
    int match = strcmp(str1, str2) == 0;
    return match;
}