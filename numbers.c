#include <stdio.h>
#include <string.h>
#include "numbers.h"
#include <math.h>
#include <limits.h>

char *ones[] = {
    "", "en", "to", "tre", "fire", "fem", "seks", "syv", "otte", "ni"};

char *teens[] = {"ti", "elleve", "tolv", "tretten", "fjorten", "femten", "seksten", "sytten", "atten", "nitten"};

char *first_twenty[] = {"", "en", "to", "tre", "fire", "fem", "seks", "syv", "otte", "ni", "ti", "elleve", "tolv", "tretten", "fjorten", "femten", "seksten", "sytten", "atten", "nitten"};

// Array of Danish spellings for multiples of 10 up to 100
char *tens[] = {"", "ti", "tyve", "tredive", "fyrre", "halvtreds", "tres", "halvfjerds", "firs", "halvfems"};

const char *og = "og";
const char *space = " ";

int is_final(int remainder)
{
    int billions = remainder / 1000000000;
    remainder = remainder % 1000000000;
    int millions = remainder / 1000000;
    remainder = remainder % 1000000;
    int thousands = remainder / 1000;
    remainder = remainder % 1000;
    int hundreds = remainder / 100;
    int tens = remainder % 100;
    if (billions || millions || thousands || hundreds || tens)
    {
        return 0;
    }
    return 1;
}

int values_remaining(int *val_arr, int size)
// int values_remaining(int remainder)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (val_arr[i])
        {
            count++;
        }
    }
    // Any billions left?
    // if (remainder / 1000000000)
    // {
    //     count++;
    // }
    // remainder = remainder % 1000000000;
    // // Any millions left?
    // if (remainder / 1000000)
    // {
    //     count++;
    // }
    // remainder = remainder % 1000000;
    // // Any thousands left?
    // if (remainder / 1000)
    // {
    //     count++;
    // }
    // remainder = remainder % 1000;
    // // Any hundreds left?
    // if (remainder / 100)
    // {
    //     count++;
    // }
    // // Any tens left?
    // if (remainder % 100)
    // {
    //     count++;
    // }
    return count;
}

int number_to_danish(int number, char *buffer, struct NumberFormat format)
{

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
    // int billions = remainder / 1000000000;
    // remainder = remainder % 1000000000;
    // int millions = remainder / 1000000;
    // remainder = remainder % 1000000;
    // int thousands = remainder / 1000;
    // remainder = remainder % 1000;
    // int hundreds = remainder / 100;
    // int tens = remainder % 100;
    // int tens = number % 100;
    // int hundreds = number / 100;
    // int thousands = number / 1000;

    remainder = number;
    int remaining_values = values_remaining(val_arr, 5);

    // printf("Values remaining: %d\n", remaining_values);

    if (number < 0)
    {
        strcat(buffer, "minus ");
        number = abs(number);
    }

    if (val_arr[0])
    // if (billions)
    {
        // printf("Billions: %d\n", val_arr[0]);
        // printf("Billions: %d\n", billions);
        handle_formatting(buffer, format, remaining_values, "milliard", "en", val_arr[0], remainder);
        remainder = remainder % 1000000000;
        number_to_danish(remainder, buffer, format);
    }
    else if (val_arr[1])
    // else if (millions)
    {
        // printf("Millions: %d\n", val_arr[1]);
        // printf("Millions: %d\n", millions);
        handle_formatting(buffer, format, remaining_values, "million", "en", val_arr[1], remainder);
        remainder = remainder % 1000000;
        number_to_danish(remainder, buffer, format);
    }
    else if (val_arr[2])
    // else if (thousands)
    {
        // printf("Thousands: %d\n", val_arr[2]);
        // printf("Thousands: %d\n", thousands);
        handle_formatting(buffer, format, remaining_values, "tusind", "et", val_arr[2], remainder);
        remainder = remainder % 1000;
        number_to_danish(remainder, buffer, format);
    }
    else if (val_arr[3])
    // else if (hundreds)
    {
        // printf("Hundreds: %d\n", val_arr[3]);
        // printf("Hundreds: %d\n", hundreds);
        handle_formatting(buffer, format, remaining_values, "hundred", "et", val_arr[3], remainder);
        remainder = remainder % 100;
        number_to_danish(remainder, buffer, format);
    }
    else if (val_arr[4])
    {
        // printf("Tens: %d\n", val_arr[4]);
        handle_tens(number, buffer, 0);
    }

    return 0;
}

void handle_tens(int number, char *buffer, int is_et)
{
    // printf("In handle tens: %d\n", number);
    if (is_et && number == 1)
    {
        strcat(buffer, "et");
        return;
    }
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

void handle_formatting(char *buffer, struct NumberFormat format, int remaining_values, char *num_type, char *one_type, int number, int remainder)
// void handle_formatting(char *buffer, struct NumberFormat format, int remaining_values, char *num_type, char *one_type, int number, int *all_values)
// void handle_formatting(char *buffer, struct NumberFormat format, int remaining_values, char *num_type, char *one_type, int number)
// void handle_formatting(char *buffer, struct NumberFormat format, int endFlag, char *num_type, char *one_type, int number)
// void handle_formatting(char *buffer, struct NumberFormat format, int endFlag, char *num_type, char *one_type, int first_amount, int second_amount)
// void handle_formatting(char *buffer, struct NumberFormat format, int endFlag, char *num_type, char *one_type, int f_amount)
{
    // Print all parameters
    int current_is_last = remaining_values == 1 ? 1 : 0;
    // printf("\nIn handle formatting\n");
    // // printf("buffer: %s\n", buffer);
    // printf("remaining_values: %d\n", remaining_values);
    // printf("endFlag: %d\n", endFlag);
    // printf("num_type: %s\n", num_type);
    // printf("one_type: %s\n", one_type);
    // printf("f_amount: %d\n", f_amount);
    // printf("s_amount: %d\n", s_amount);
    // Check if the final flag is set
    int final_e = format.e == LAST && current_is_last;
    int final_og = format.og == LAST && remaining_values == 2;
    int final_et = format.et == LAST && current_is_last;

    int hundreds = number / 100;
    int tens = number % 100;

    // printf("hundreds: %d\n", hundreds);
    // printf("tens: %d\n", tens);
    // printf("et type: %s\n", one_type);
    // printf("final_e: %d\n", final_e);
    // printf("final_og: %d\n", final_og);
    // printf("final_et: %d\n", final_et);

    if (hundreds > 0)
    {
        if (hundreds == 1 && (format.et == EVERY || final_et))
        {
            strcat(buffer, one_type);
            strcat(buffer, space);
        }
        else if (hundreds > 1)
        {
            strcat(buffer, ones[hundreds]);
            strcat(buffer, space);
        }
        strcat(buffer, "hundred");
        if (format.e == EVERY || final_e)
        // if ((format.e == EVERY || final_e) && strcmp(one_type, "et") == 0)
        {
            // printf("Adding e\n");
            strcat(buffer, "e");
        }
        strcat(buffer, space);
    }

    if (tens > 0)
    {
        // printf("Adding tens\n");
        if ((final_og || (format.og == EVERY && remaining_values > 1)) && hundreds > 0)
        {
            strcat(buffer, " og ");
        }
        handle_tens(tens, buffer, strcmp(one_type, "et") == 0);
        strcat(buffer, space);
    }
    strcat(buffer, num_type);
    if ((format.e == EVERY || final_e ||
    // This looks very convoluted thanks to all the string comparisons. BUT this allows "tusind" to have an ending "e", iff there's no more hundreds left. In that case, the hundred should get the "e"
    (format.e == LAST && ((strcmp(num_type, "hundred") == 0 || (strcmp(num_type, "tusind") == 0 && !hundreds_left(remainder))) && remaining_values == 2)))
    // Just make sure it can only add "e" to hundreds and thousands
    && strcmp(one_type, "et") == 0)
    // if ((format.e == EVERY || final_e || (format.e == LAST && (strcmp(num_type, "hundred") == 0 || (strcmp(num_type, "tusind") == 0 && hundreds_left())))) && strcmp(one_type, "et") == 0)
    {
        // printf("Adding e\n");
        strcat(buffer, "e");
    }
    // This triggers for millioner+. Add "er" if there's more than one
    else if ((hundreds > 0 || tens > 1 ) && strcmp(one_type, "en") == 0)
    {   strcat(buffer, "er");
    }
    if ((format.og == EVERY || final_og || (format.og == LAST && remaining_values == 2)) && remaining_values > 1)
    {
        // printf("Adding og\n");
        strcat(buffer, " og");
    }
    strcat(buffer, space);
    // printf("\nBuffer: %s\n\n", buffer);
}

// Assumes that the incoming number is 1000 < x < 1.000.000, or the operation will not make sense
int hundreds_left(int remainder)
{
    // printf("Remainder in hundreds left: %d\n", remainder);
    // printf("hundreds left? %d\n", (remainder % 1000 / 100));
    return (remainder % 1000 / 100);
}