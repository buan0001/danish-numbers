#include <stdio.h>
#include <string.h>
#include "numbers.h"
#include <math.h>
#include <limits.h>

char *ones[] = {
    "nul", "en", "to", "tre", "fire", "fem", "seks", "syv", "otte", "ni"};

char *teens[] = {"ti", "elleve", "tolv", "tretten", "fjorten", "femten", "seksten", "sytten", "atten", "nitten"};

char *first_twenty[] = {"", "en", "to", "tre", "fire", "fem", "seks", "syv", "otte", "ni", "ti", "elleve", "tolv", "tretten", "fjorten", "femten", "seksten", "sytten", "atten", "nitten"};

// Array of Danish spellings for multiples of 10 up to 100
char *tens[] = {"", "ti", "tyve", "tredive", "fyrre", "halvtreds", "tres", "halvfjerds", "firs", "halvfems"};

const char *og = "og";
const char *space = " ";

int number_to_danish(double decimals, char *buffer, struct NumberFormat format)
{
    // Might try decimals later. Rn they fuck up all the time
    // printf("number to convert as decimal: %lf\n", decimals);
    // double just_decimals = decimals - (int)decimals;
    int number = (int)decimals;
    // printf("number to convert after converting to, formatted as double: %lf\n", number);
    // printf("number to convert after converting to int, formatted as int: %d\n", number);
    if (number == 0)
    {
        strcat(buffer, "nul");
        return 0;
    }
    if (number < 0)
    {
        strcat(buffer, "minus ");
        number = -number;
    }
    // val_arr: Billions, millions, thousands, hundreds, tens
    int val_arr[5];
    int remainder = number;

    // Arrayify the amount of billions, millions, thousands, hundreds and tens for ease of use
    val_arr[0] = remainder / 1000000000;
    remainder = remainder % 1000000000;
    val_arr[1] = remainder / 1000000;
    remainder = remainder % 1000000;
    val_arr[2] = remainder / 1000;
    remainder = remainder % 1000;
    val_arr[3] = remainder / 100;
    val_arr[4] = remainder % 100;

    remainder = number;
    int remaining_values = values_remaining(val_arr, 5);
    int remaining_values_over_99 = values_remaining(val_arr, 4);



    if (val_arr[0])
    {
        handle_formatting(buffer, format, remaining_values, remaining_values_over_99, "milliard", "en", val_arr[0], remainder);
        remainder = remainder % 1000000000;
        remaining_values--;
        remaining_values_over_99--;
    }
    if (val_arr[1])
    {
        handle_formatting(buffer, format, remaining_values, remaining_values_over_99, "million", "en", val_arr[1], remainder);
        remainder = remainder % 1000000;
        remaining_values--;
        remaining_values_over_99--;
    }
    if (val_arr[2])
    {
        handle_formatting(buffer, format, remaining_values, remaining_values_over_99, "tusind", "et", val_arr[2], remainder);
        remainder = remainder % 1000;
        remaining_values--;
        remaining_values_over_99--;
    }
    if (val_arr[3])
    {
        handle_formatting(buffer, format, remaining_values, remaining_values_over_99, "hundred", "et", val_arr[3], remainder);
        remainder = remainder % 100;
        remaining_values--;
        remaining_values_over_99--;
    }
    if (val_arr[4])
    {
        handle_tens(val_arr[4], buffer, 0);
    }

    // Puh, forget about it. Decimals have too much imprecision

    // if (just_decimals > 0)
    // {
    //     printf("Decimals spotted\n");
    //     printf("Just decimals: %lf\n", just_decimals);
    //     strcat(buffer, " komma");
    //     int last_was_zero = 0;
    //     int counter = 0;
    //     int no_dec;
    //     // while (1)
    //     // {
    //     //     just_decimals *= 10;
    //     //     no_dec = (int)just_decimals;
    //     //     printf("No dec: %d\n", no_dec);
    //     //     int next_int = (int)no_dec % 10;
    //     //     printf("Next int: %d\n", next_int);
    //     //     if (next_int == 0)
    //     //     {
    //     //         if (last_was_zero)
    //     //         {
    //     //             // Keep going until two 0s in a row
    //     //             break;
    //     //         }
    //     //         last_was_zero = 1;
    //     //     }
    //     //     else
    //     //     {
    //     //         if (last_was_zero)
    //     //         {
    //     //             strcat(buffer, " nul");
    //     //         }
    //     //         strcat(buffer, " ");
    //     //         strcat(buffer, ones[next_int]);
    //     //         last_was_zero = 0;
    //     //     }
    //     //     // Just in case
    //     //     counter++;
    //     //     if (counter > 10)
    //     //     {
    //     //         break;
    //     //     }
    //     // }
    // }

    return 0;
}

void handle_tens(int number, char *buffer, int is_et)
{
    // printf("In handle tens: %d\n", number);

    if (number < 20)
    {
        // printf("Adding teen %d\n", number);
        strcat(buffer, first_twenty[number]);
    }
    else
    {
        int tens_digit = number / 10;
        int ones_digit = number % 10;
        // printf("Adding tens %d %d\n", tens_digit, ones_digit);
        if (ones_digit > 0 && tens_digit > 0)
        {
            strcat(buffer, ones[ones_digit]);
            strcat(buffer, og);
            strcat(buffer, tens[tens_digit]);
        }
        else
        {
            strcat(buffer, tens[tens_digit]);
        }
    }
}

void handle_formatting(char *buffer, struct NumberFormat format, int remaining_values, int remaining_values_over_99, char *num_type, char *one_type, int number, int remainder)
{
    // printf("One type: %s\n", one_type);
    // printf("Num type: %s\n\n", num_type);

    int current_is_last = remaining_values == 1 ? 1 : 0;
    int final_og = format.og == LAST && remaining_values == 2;
    int final_e = format.e == LAST && remaining_values_over_99 == 1;
    int final_et = format.et == LAST && remaining_values_over_99 == 1;

    // Get the amount of hundreds and tens, no matter if it's 2 million or 91
    int hundreds = number / 100;
    int tens = number % 100;
    printf("Hundreds: %d. Tens: %d\n", hundreds, tens);
    printf("remaining values: %d\n", remaining_values);

    if (hundreds > 0)
    {
        printf("In hundreds > 0\n");
        if (hundreds == 1 && (format.et == EVERY || final_et))
        {
            strcat(buffer, "et");
            strcat(buffer, space);
        }
        else if (hundreds > 1)
        {
            strcat(buffer, ones[hundreds]);
            strcat(buffer, space);
        }
        strcat(buffer, "hundred");
        if (format.e == EVERY || final_e)
        {
            strcat(buffer, "e");
        }
        strcat(buffer, space);
        // printf("Buffer AFTER In hundreds > 0: %s\n", buffer);
    }

    if (tens > 0)
    {
        // printf("Adding tens\n");
        if ((final_og || (format.og == EVERY && remaining_values > 1)) && hundreds > 0)
        {
            strcat(buffer, "og ");
        }
        if (tens == 1)
        {
            if (final_et || format.et == EVERY || str_match(one_type, "en"))
            {
                // printf("Adding one type\n");
                strcat(buffer, one_type);
                strcat(buffer, space);
            }
        }
        else
        {
            printf("Adding tens\n");
            handle_tens(tens, buffer, str_match(one_type, "et"));
            strcat(buffer, space);
        }
    }

    strcat(buffer, num_type);
    if ((format.e == EVERY || final_e) && str_match(one_type, "et"))
    {
        // printf("Adding e\n");
        strcat(buffer, "e");
    }

    // This triggers for millioner+. Add "er" if there's more than one
    else if ((hundreds > 0 || tens > 1) && str_match(one_type, "en"))
    {
        // printf("Adding er to %s\n", num_type);
        // printf("One type: %s matches 'en'\n", one_type);
        strcat(buffer, "er");
    }
    if (remaining_values > 1)
    {
        if ((format.og == EVERY || final_og || (format.og == LAST && remaining_values == 2)))
        {
            // printf("Adding og\n");
            strcat(buffer, " og");
        }
        strcat(buffer, space);
    }

    printf("\nBuffer: %s.\n\n", buffer);
}

int str_match(char *str1, char *str2)
{
    // printf("Comparing %s and %s\n", str1, str2);
    return strcmp(str1, str2) == 0;
    // return (strcmp(str1, str2) == 0 ? 1 : -1);
}

int values_remaining(int *val_arr, int size)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (val_arr[i])
        {
            count++;
        }
    }
    return count;
}