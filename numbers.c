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

int number_to_danish(int number, char *buffer, struct NumberFormat format)
{
    int is_tens = number < 100;
    int is_hundreds = number < 1000;
    int is_thousands = number < 1000000;
    int is_millions = number < 1000000000;
    int is_billions = number < 1000000000000;

    if (number == 0)
    {
        strcat(buffer, "nul");
        return 0;
    }
    else if (number < 0)
    {
        strcat(buffer, "minus ");
        number = abs(number);
    }
    else if (is_tens)
    {
        handle_tens(number, buffer);
    }
    else if (is_hundreds)
    {
        handle_hundreds(number, buffer, format, 1);
    }
    else if (is_thousands)
    {
        int thousands = number / 1000;
        int hundreds = number % 1000;
        if (thousands < 100)
        {
            handle_tens(thousands, buffer);
        }
        else
        {
            handle_hundreds(thousands, buffer, format, 0);
        }
        strcat(buffer, "tusind");
        if (hundreds > 0)
        {
            handle_hundreds(thousands, buffer, format, 0);
        }
    }
    else if (is_millions)
    {
    }
    else if (is_billions)
    {
    }

    return 0;
}

void handle_tens(int number, char *buffer)
{
    if (number < 20)
    {
        strcat(buffer, first_twenty[number]);
    }
    else
    {
        int tens_digit = number / 10;
        int ones_digit = number % 10;
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

void handle_hundreds(int number, char *buffer, struct NumberFormat format, int endFlag)
{
    // int final_e = format.e == LAST && endFlag;
    // int final_og = format.og == LAST && endFlag;
    // int final_et = format.et == LAST && endFlag;

    int hundreds = number / 100;
    int tens = number % 100;

    handle_formatting(buffer, format, endFlag, "hundred", "et", hundreds, tens);

    // if (hundreds > 0)
    // {
    //     if (hundreds == 1 && (format.et == EVERY || final_et))
    //     {
    //         strcat(buffer, "et hundred");
    //     }
    //     else
    //     {
    //         if (hundreds > 1){
    //         strcat(buffer, ones[hundreds]);
    //         strcat(buffer, space);
    //         }
    //         strcat(buffer, "hundred");
    //         if (format.e == EVERY || final_e)
    //         {
    //             strcat(buffer, "e");
    //         }
    //     }
    //     strcat(buffer, space);
    // }
    if (tens > 0)
    {
        // if (final_og || format.og == EVERY)
        // {
        //     strcat(buffer, "og ");
        // }
        handle_tens(tens, buffer);
    }
}

void handle_formatting(char *buffer, struct NumberFormat format, int endFlag, char *num_type, char *one_type, int f_amount, int s_amount)
{
    // Print all parameters
    printf("In handle formatting\n");
    // printf("buffer: %s\n", buffer);
    printf("endFlag: %d\n", endFlag);
    printf("num_type: %s\n", num_type);
    printf("one_type: %s\n", one_type);
    printf("f_amount: %d\n", f_amount);
    printf("s_amount: %d\n", s_amount);
    // Check if the final flag is set
    int final_e = format.e == LAST && endFlag;
    int final_og = format.og == LAST && endFlag;
    int final_et = format.et == LAST && endFlag;

    printf("final_e: %d\n", final_e);
    printf("final_og: %d\n", final_og);
    printf("final_et: %d\n", final_et);

    if (f_amount > 0)
    {
        if (f_amount == 1 && (format.et == EVERY || final_et))
        {
            strcat(buffer, one_type);
            strcat(buffer, space);
        }
        else if (f_amount > 1)
        {
            strcat(buffer, ones[f_amount]);
            strcat(buffer, space);
        }
        strcat(buffer, num_type);
        if ((format.e == EVERY || final_e) && strcmp(one_type, "et") == 0)
        {
            printf("Adding e\n");
            strcat(buffer, "e");
        }

        strcat(buffer, space);
    }
    if (s_amount > 0)
    {
        if (final_og || format.og == EVERY)
        {
            strcat(buffer, "og ");
        }
    }
}