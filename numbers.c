#include <stdio.h>
#include <string.h>
#include "numbers.h"
#include <math.h>

// char *basics[9];
// basics[0] = "en";
// char *basics[] = {"en", "to", "tre", "fire", "fem", "seks", "syv", "otte", "ni"};
// int main()
// {

//     return 0;
// }

#include <stdio.h>

char *numbers_0_to_19[] = {
    "nul", "en", "to", "tre", "fire", "fem", "seks", "syv", "otte", "ni",
    "ti", "elleve", "tolv", "tretten", "fjorten", "femten", "seksten", "sytten", "atten", "nitten"
};

// Array of Danish spellings for multiples of 10 up to 100
char *tens[] = {"", "ti", "tyve", "tredive", "fyrre", "halvtreds", "tres", "halvfjerds", "firs", "halvfems", "hundrede"};

const char *og = "og";
const char *space = " ";

int number_to_danish(int number, char* result) {
    int numbers[255];
    int max_digits;
    int digits = 0;
    printf("Converting: %d\n", number);

    int temp_number = number;
    while (temp_number)
    {
        numbers[digits] = temp_number % 10;
        temp_number = temp_number / 10;
        digits++;
    }
    max_digits = digits;
    printf("Digits: %d\n", digits);
    print_numbers(numbers, digits);
    int recent_change = 0;
    int is_first = 1;
    int is_last = 0;
    while (digits > 0){
        switch (digits)
        {
            case 12:
            case 9:
            case 6:
                printf("Digits BEFORE handle_hundreds: %d\n", digits);
                recent_change = handle_hundreds(result, numbers, &digits);
                printf("Digits AFTER handle_hundreds: %d\n", digits);
                break;
            case 11:
            case 8:
            case 5:
                printf("Final BEFORE handle_tens: %s\n", result);
                int temp_change = handle_tens(result, numbers, &digits);
                if (!recent_change && temp_change) {
                    recent_change = 1;
                }
                printf("Final AFTER handle_tens: %s\n", result);
                break;
            default:
                printf("Digits when reaching thousand/mill/bil: %d\n", digits);
                char *temp_digit = numbers_0_to_19[numbers[digits-1]];
                int is_en = 0;
                if (!is_null(temp_digit)){
                // convert en to et if it's a thousand coming up, otherwise leave it at en
                    
                    if ((strcmp(temp_digit, "en") == 0) && digits < 6) {
                        temp_digit = (strcmp(temp_digit, "en") == 0) ? "et" : temp_digit;
                    }

                    if (digits == max_digits || (numbers[digits] == 0 && numbers[digits+1] == 0))
                    {
                        is_en = (strcmp(temp_digit, "en") == 0);
                        recent_change = 1;
                        printf("Is en: %d\n", is_en);
                        printf("Final before adding 'en' loop: %s\n", result);
                        printf("(numbers[digits]: %d. numbers[digits+1]: %d\n", numbers[digits], numbers[digits+1]);
                        // printf("Temp digit in bill/mill/thousand: %s\n", temp_digit);
                        strcat(result, temp_digit);
                        strcat(result, space);
                    }
                }
                else {
                    printf("The temp digit is null at position %d\n", digits-1);
                }
                printf("Made recent change: %d\n", recent_change);
                if (digits > 9 && recent_change) {
                    printf("We are in the billions\n");
                    strcat(result, "milliard");
                }
                else if (digits > 6 && recent_change) {
                    printf("We are in the millions\n");
                    strcat(result, "million");
                }
                else if (digits > 3 && recent_change) {
                    printf("We are in the thousands\n");
                    strcat(result, "tusind");
                }
                if (digits > 6 && !is_en) {
                    strcat(result, "er");
                }

                digits--;
                if (!is_final(numbers, digits)){
                    printf("Is not final\n");
                    if (recent_change)
                    {
                        strcat(result, space);
                    }
                 }
                else { 
                    printf("Is final\n");
                    strcat(result, space);
                    strcat(result, "og");
                    strcat(result, space);
                }      
                recent_change = 0;
                printf("Final in the loop: %s\n", result);
            }
            if (digits == 3) {
                handle_hundreds(result, numbers, &digits);
            }
            if (digits == 1 || digits == 2) {
                handle_tens(result, numbers, &digits);
            }
        }
 

    // printf("Final: %s\n", result);
    return 0;
}
// int check_for_final(int* numbers, int digits)
// {
// if (!is_final(numbers, digits-1)){
//     printf("Is not final\n");
//     if (recent_change)
//     {
//         strcat(result, space);
//     }
// }
// else { 
//     printf("Is final\n");
//     strcat(result, space);
//     strcat(result, "og");
//     strcat(result, space);
// }





int handle_hundreds(char* result, int* numbers, int* digits)
{
    printf("\nWe are in hundreds\n");
    int made_change = 0;
    char *temp_single = numbers_0_to_19[numbers[*digits-1]];
    if (!is_null(temp_single)) {
        strcat(result, strcmp(temp_single, "en") == 0 ? "et" : temp_single);
        strcat(result, space);
        strcat(result, "hundrede");
        strcat(result, space);
        made_change = 1;
    }
    (*digits)--;
    if (made_change && is_final(numbers, *digits-1)){
        printf("Is final\n");
        strcat(result, space);
        strcat(result, "og");
        strcat(result, space);
    }
    printf("\nLeaving handle 100 with %d digits left\n\n", *digits);
    return made_change;
}



int handle_tens(char* result, int* numbers, int* digits)
{
    printf("\nWe are in tens with %d digits\n", *digits);
    int made_change = 0;
    if (*digits == 1)
    {
        printf("We are in the ones\n");
        printf("*digits %% 2 == 1: %d\n", *digits % 2 == 1);
        char *temp_single = numbers_0_to_19[numbers[*digits-1]];
        if (!is_null(temp_single)) {
            strcat(result, temp_single);
            strcat(result, space);
            made_change = 1;
        }
        else {
            printf("value was NULL in handle tens\n");
        }
    }
    // Check if the number is less than 20, since they have special words
    else if (numbers[*digits-1] < 2) {
        // combine the two digits to get a number between 1 and 19 (there should be 0 check elsewhere)
        printf("numbers[*digits]: %d. numbers[*digits-1]: %d.   numbers[*digits-2]: %d\n", numbers[*digits], numbers[*digits-1], numbers[*digits-2]);
        
        int less_than_twenty;
        if (*digits == 2) {
        less_than_twenty = numbers[*digits-1] * 10 + numbers[*digits-2];
        }
        else {
            less_than_twenty = numbers[*digits] * 10 + numbers[*digits-1];
        }
        // int less_than_twenty = numbers[*digits] * 10 + numbers[*digits-1];
        char *temp_teen = numbers_0_to_19[less_than_twenty];
        printf("Word at %d is %s\n", less_than_twenty, temp_teen);
        if (!is_null(temp_teen)) {
            strcat(result, numbers_0_to_19[less_than_twenty]);
            strcat(result, space);
            made_change = 1;
        }
        else {
            printf("value was NULL in handle tens\n");
        }
    }
    else {
        printf("We are in the tens\n");
        char *temp_tens = tens[numbers[*digits-1]];
        char *temp_single = numbers_0_to_19[numbers[*digits-2]];
        strcat(result, temp_single);
        strcat(result, og);
        strcat(result, temp_tens);
        strcat(result, space);
        made_change = 1;
    }
    // printf("Digits-1 %d. *digits-1 %d\n", digits-1, *digits-1);
    (*digits) -= 1;
    if (made_change && is_final(numbers, *digits-1)){
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

void and_space(char* result){
        strcat(result, og);
        strcat(result, space);
}

void print_numbers(int* numbers, int digits){
    for (int i = 0; i < digits; i++)
    {
        printf("Index %d: %d\n", i, numbers[i]);
    }
}

void print_arrays(){
        printf("Numbers 0 to 19:\n");
    for (int i = 0; i < 20; i++) {
        printf("%d: %s\n", i, numbers_0_to_19[i]);
    }

    printf("\nMultiples of 10:\n");
    for (int i = 1; i <= 10; i++) {
        printf("%d: %s\n", i * 10, tens[i]);
    }
}

int is_final(int* numbers, int digits)
{
    int remaining_value = 0;
    for (int i = 0; i < digits; i++)
    {
        if (i > 0){
            remaining_value += pow(numbers[i], i);
        }
        else {
            remaining_value += numbers[i];
        }
    }
    remaining_value = remaining_value % 10;
    int final = remaining_value == 0 ? 1 : 0;
    printf("digits: %d\n", digits);
    if (digits < 3){final = 1;}
    return final;
}

