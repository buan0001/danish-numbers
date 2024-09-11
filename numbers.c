#include <stdio.h>
#include <string.h>
#include "numbers.h"
#include <math.h>
#include <limits.h>

// char *basics[9];
// basics[0] = "en";
// char *basics[] = {"en", "to", "tre", "fire", "fem", "seks", "syv", "otte", "ni"};
// int main()
// {

//     return 0;
// }

typedef enum
{
    NEVER,
    EVERY,
    LAST
} occurence;

struct NumberFormat
{
    occurence og;
    occurence e;
    occurence et;
};

char *ones[] = {
    "", "en", "to", "tre", "fire", "fem", "seks", "syv", "otte", "ni"};

char *teens[] = {"ti", "elleve", "tolv", "tretten", "fjorten", "femten", "seksten", "sytten", "atten", "nitten"};

char *first_twenty[] = {"", "en", "to", "tre", "fire", "fem", "seks", "syv", "otte", "ni", "ti", "elleve", "tolv", "tretten", "fjorten", "femten", "seksten", "sytten", "atten", "nitten"};

// Array of Danish spellings for multiples of 10 up to 100
char *tens[] = {"", "ti", "tyve", "tredive", "fyrre", "halvtreds", "tres", "halvfjerds", "firs", "halvfems"};

const char *og = "og";
const char *space = " ";

int number_to_danish(int number, char *result)
{

    
    struct NumberFormat format = {LAST, EVERY, EVERY};
    int numbers[255];

    int digits = 0;
    printf("Converting: %d\n", number);

    if (number > INT_MAX)
    {
        strcat(result, "Number is too large");
        return 0;
    }
    else if (number == 0)
    {
        strcat(result, "nul");
        return 0;
    }
    else if (number < 0)
    {
        strcat(result, "minus ");
        number = abs(number);
    }
    int temp_number = number;
    while (temp_number)
    {
        numbers[digits] = temp_number % 10;
        temp_number = temp_number / 10;
        digits++;
    }

    printf("Digits: %d\n", digits);
    print_numbers(numbers, digits);

    int max_digits = digits;
    int values_left = 1;
    int remainder = number;
    for (int i = 0; i < max_digits; i++)
    {

        printf("Remainder: %d\n", remainder);
        printf("Digits: %d\n", digits);
        // There IS value in current iteration. Check if there's value after this one
        values_left = get_values_left(numbers, digits);
        printf("any_values_left: %d\n\n", values_left);
        // TENS
        if (digits % 3 == 2)
        {
            // printf("We are in the tens\n");
            // If the NEXT digit is less than two, we're in the range 0 - 19
            if (numbers[digits - 1] < 2)
            {
                printf("We are in the teens\n");
                
                // We have to treat the two cases differently: If there's only 2 digits left, there wont be a "special" digit afterwards
                // Where as in every other case, there is either a "thousand", "million" or "billion" after
                // Need to not be at max digits, or it crashes
                printf("Treating teens\n");
                int less_than_twenty  = numbers[digits - 1] * 10 + numbers[digits - 2];
                // }
                if (less_than_twenty != 0)
                {
                    char *temp_teen = first_twenty[less_than_twenty];
                    printf("Word at %d is %s\n", less_than_twenty, temp_teen);
                    // It must be "et tusind" rather than "en tusind", so check for 5 digits (the digit before thousands)
                    if (digits == 5 && less_than_twenty == 1)
                    {
                        strcat(result, "et");
                    }
                    else
                    {
                        strcat(result, first_twenty[less_than_twenty]);
                    }
                    if (digits != 2)
                    {
                        strcat(result, space);
                    }
                }
            }
            else
            {
                printf("We are in the tens\n");
                // printf("numbers[digits - 1] %d. numbers[digits - 2]: %d\n", numbers[digits - 1], numbers[digits - 2]);
                char *temp_tens = tens[numbers[digits - 1]];
                char *temp_single = ones[numbers[digits - 2]];
                // Only include the "one spot" if it's not 0
                if (numbers[digits - 2] != 0)
                {
                    printf("Temp single: %s\n", temp_single);
                    strcat(result, temp_single);
                    strcat(result, og);
                }
                // Only include the tens if it's not 0
                if (numbers[digits - 1] != 0)
                {
                    strcat(result, temp_tens);
                }
                printf("Adding space in tens\n");
                if (digits != 2)
                {
                    strcat(result, space);
                }
            }
            if (digits == 2)
            {
                break;
            }
        }
        // HUNDREDS
        else if (digits % 3 == 0)
        {
            printf("We are in hundreds\n");
            char *temp_single = ones[numbers[digits - 1]];
            if (numbers[digits - 1] != 0)
            {
                // Formatting for the first digit in the number
                if (numbers[digits - 1] == 1 && (format.et == EVERY || (format.et == LAST && values_left == 1)))
                {
                    printf("Adding et and space\n");
                    strcat(result, "et");
                    strcat(result, space);
                }
                // If the number is not 1, add the number to the result
                else if (numbers[digits - 1] != 1)
                {
                    printf("Adding temp single and space\n");
                    strcat(result, temp_single);
                    strcat(result, space);
                }
                strcat(result, "hundred");

                if (format.e == EVERY || (format.e == LAST && values_left == 1))
                {
                    strcat(result, "e");
                }
                // Only if it's the last, and last is set, OR if every is set and the next value is not 0
                if ((format.og == EVERY && (numbers[digits - 2] != 0 || numbers[digits - 3] != 0)) || (format.og == LAST && digits == 3 && values_left == 2))
                {
                    printf("Adding space and og\n");
                    strcat(result, space);
                    strcat(result, "og");
                }
                printf("any values left? %d\n", values_left);
                if (values_left)
                {
                    printf("adding space\n");
                    strcat(result, space);
                }
            }
        }

        else if (digits == 1)
        {
            printf("One digit left\n");
            char *temp_single = ones[numbers[digits - 1]];
            strcat(result, temp_single);
        }
        else if (digits == 4)
        {
            printf("We are in the thousands\n");
            if (max_digits == digits)
            {
                char *temp_single = ones[numbers[digits - 1]];
                printf("We are in the first thousands. Temp single: %s\n", temp_single);
                printf("numbers[digits - 1]] %d\n", numbers[digits - 1]);
                if (numbers[digits - 1] == 1 && (format.et == EVERY || (format.et == LAST && values_left == 1)))
                {
                    strcat(result, "et");
                }
                else if (numbers[digits - 1] != 1)
                {
                    strcat(result, temp_single);
                }
                printf("Adding space\n");
                strcat(result, space);
            }

            // We check if there's any values before the thousand spot. Only add thousand if there are
            // Also make sure that the digits we check for dont exceed the max digits
            printf(" numbers[digits + 1]: %d\n", numbers[digits + 1]);
            // if (numbers[digits] != 0 || (max_digits > 5 && numbers[digits] != 0) || (max_digits > 6 && numbers[digits + 1] != 0))
            if (numbers[digits] != 0 || (max_digits > 5 && numbers[digits + 1] != 0) || (max_digits > 6 && numbers[digits + 2] != 0))
            {
                strcat(result, "tusind");
                if (format.e == EVERY || (format.e == LAST && values_left == 1))
                {
                    strcat(result, "e");
                }
                if (format.og == EVERY || (format.og == LAST && values_left == 1))
                // if (format.og == EVERY || (format.og == LAST && values_left <= 2))
                {
                    printf("Adding og and space\n");
                    strcat(result, space);
                    strcat(result, "og");
                }
                if (values_left > 0)
                {
                    strcat(result, space);
                }
                else
                {
                    printf("No values left from thousands\n");
                    break;
                }
            }
            else
            {
                printf("No values IN thousands:\n");
                printf("numbers[digits + 1]: %d. numbers[digits + 2]: %d\n", numbers[digits + 1], numbers[digits + 2]);
            }
        }

        else if (digits == 7)
        {
            printf("We are in the millions\n");
            if (max_digits == digits || numbers[digits] != 0 || (max_digits > 8 && numbers[digits + 1] != 0))
            {
                if (max_digits == digits)
                {
                    char *temp_single = ones[numbers[digits - 1]];
                    printf("We are in the first millions. Temp single: %s\n", temp_single);
                    printf("numbers[digits - 1]] %d\n", numbers[digits - 1]);
                    if (numbers[digits - 1] == 1)
                    {
                        strcat(result, "en million");
                    }
                    else if (numbers[digits - 1] != 1)
                    {
                        strcat(result, temp_single);
                        strcat(result, "millioner");
                    }
                }
                else
                {
                    strcat(result, "millioner");
                }
                if (format.og == EVERY || (format.og == LAST && values_left == 2))
                {
                    printf("Adding space and og\n");
                    strcat(result, " og");
                }
                if (values_left > 1)
                {
                    strcat(result, space);
                }
                else
                {
                    printf("No values left from millions\n");
                    break;
                }
            }

            // We check if there's any values before the million spot. Only add million if there are
            // Also make sure that the digits we check for dont exceed the max digits

            // if (numbers[digits] != 0 || (max_digits > 8 && numbers[digits+1] != 0) || (max_digits > 9 && numbers[digits+2] != 0))
        }

        else if (digits == 10)
        {
            printf("We are in the billions\n");

            if (max_digits == digits || numbers[digits] != 0 || (max_digits > 11 && numbers[digits + 1] != 0))
            {
                if (max_digits == digits)
                {
                    char *temp_single = ones[numbers[digits - 1]];
                    printf("We are in the first billions. Temp single: %s\n", temp_single);
                    printf("numbers[digits - 1]] %d\n", numbers[digits - 1]);
                    if (numbers[digits - 1] == 1)
                    {
                        strcat(result, "en milliard");
                    }
                    else if (numbers[digits - 1] != 1)
                    {
                        strcat(result, temp_single);
                        strcat(result, "milliarder");
                    }
                }
                else
                {
                    strcat(result, "milliarder");
                }
                if (format.og == EVERY || (format.og == LAST && values_left == 2))
                {
                    printf("Adding space and og\n");
                    strcat(result, " og");
                }
                if (values_left > 1)
                {
                    strcat(result, space);
                }
                else
                {
                    printf("No values left from billions\n");
                    break;
                }
            }

        }

        printf("Currently in the buffer at index %d: %s\n", i, result);
        digits--;
        remainder = remainder % 10;
    }

    return 0;
}

int handle_hundreds(char *result, int *numbers, int *digits)
{
    printf("\nWe are in hundreds\n");
    int made_change = 0;
    char *temp_single = ones[numbers[*digits - 1]];
    if (!is_null(temp_single))
    {
        strcat(result, strcmp(temp_single, "en") == 0 ? "et" : temp_single);
        strcat(result, space);
        strcat(result, "hundrede");
        strcat(result, space);
        made_change = 1;
    }
    (*digits)--;
    if (made_change && get_values_left(numbers, *digits - 1))
    {
        printf("Is final\n");
        strcat(result, space);
        strcat(result, "og");
        strcat(result, space);
    }
    printf("\nLeaving handle 100 with %d digits left\n\n", *digits);
    return made_change;
}

int handle_tens(char *result, int *numbers, int *digits)
{
    printf("\nWe are in tens with %d digits\n", *digits);
    int made_change = 0;
    if (*digits == 1)
    {
        printf("We are in the ones\n");
        printf("*digits %% 2 == 1: %d\n", *digits % 2 == 1);
        char *temp_single = ones[numbers[*digits - 1]];
        if (!is_null(temp_single))
        {
            strcat(result, temp_single);
            strcat(result, space);
            made_change = 1;
        }
        else
        {
            printf("value was NULL in handle tens\n");
        }
    }
    // Check if the number is less than 20, since they have special words
    else if (numbers[*digits - 1] < 2)
    {
        // combine the two digits to get a number between 1 and 19 (there should be 0 check elsewhere)
        printf("numbers[*digits]: %d. numbers[*digits-1]: %d.   numbers[*digits-2]: %d\n", numbers[*digits], numbers[*digits - 1], numbers[*digits - 2]);

        int teen_number;
        if (*digits == 2)
        {
            teen_number = numbers[*digits - 1] * 10 + numbers[*digits - 2];
        }
        else
        {
            teen_number = numbers[*digits] * 10 + numbers[*digits - 1];
        }
        // int less_than_twenty = numbers[*digits] * 10 + numbers[*digits-1];
        char *temp_teen = first_twenty[teen_number];
        printf("Word at %d is %s\n", teen_number, temp_teen);
        if (!is_null(temp_teen))
        {
            strcat(result, ones[teen_number]);
            strcat(result, space);
            made_change = 1;
        }
        else
        {
            printf("value was NULL in handle tens\n");
        }
    }
    else
    {
        printf("We are in the tens\n");
        char *temp_tens = tens[numbers[*digits - 1]];
        char *temp_single = ones[numbers[*digits - 2]];
        strcat(result, temp_single);
        strcat(result, og);
        strcat(result, temp_tens);
        strcat(result, space);
        made_change = 1;
    }
    // printf("Digits-1 %d. *digits-1 %d\n", digits-1, *digits-1);
    (*digits) -= 1;
    if (made_change && get_values_left(numbers, *digits - 1))
    {
        printf("Is final\n");
        strcat(result, "og");
    }
    printf("Leaving handle tens with %d digits left\n", *digits);
    return made_change;
}

int is_null(char *input)
{
    return (strcmp(input, "nul") == 0);
}

void and_space(char *result)
{
    strcat(result, og);
    strcat(result, space);
}

void print_numbers(int *numbers, int digits)
{
    for (int i = 0; i < digits; i++)
    {
        printf("Index %d: %d\n", i, numbers[i]);
    }
}

int get_values_left(int *numbers, int digits)
{
    printf("Get values left\n");
    printf("Digits: %d\n", digits);
    // print_numbers(numbers, digits);
    int value_left = 0;
    for (int i = 0; i < digits; i++)
    {
        // printf("Numbers[i] at index %d: %d\n", i, numbers[i]);
        // Lowest values come first in the array.
        // Numbers[i+2 % 3] is the value on the 10 spot. IF it has a value, we should ignore numbers[0], since they both make up the same number
        // And instead increment the index by 1
        // ... not enough though
        // printf("i + 2 %% 3 == 2 %d\n", i + 2 % 3 == 0);
        if (i + 2 % 3 == 2 && numbers[i + 1] != 0)
        {
            // if (numbers[1] != 0) {
            printf("Incrementing value left\n");
            value_left++;
            i++;
            continue;
        }
        // Otherwise we just see if there's a value in the current index and count it
        else if (numbers[i] != 0)
        {
            value_left += 1;
        }
    }
    return value_left;
}