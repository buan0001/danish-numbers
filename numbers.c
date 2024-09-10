#include <stdio.h>
#include <string.h>
#include "numbers.h"

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
    // Array of Danish spellings for numbers 0 to 19
    // int test_number = 5;
    // Print the Danish spellings to verify
    // print_arrays();
    // if (test_number < 20)
    // {
    //     printf("Test number %d = %s\n", test_number, numbers_0_to_19[test_number]);
    // }
    int temp_number = number;
    while (temp_number)
    {
        numbers[digits] = temp_number % 10;
        temp_number = temp_number / 10;
        // printf("Number %d is %d\n", digits, numbers[digits]);
        digits++;
        printf("One more digit added: %d\n", digits);   
    }

    max_digits = digits;
    temp_number = number;
    
    int first_iteration = 1;
    do
     {
        print_numbers(numbers, digits);
        printf("Temp number: %d\n", temp_number);
        printf("Digits: %d\n", digits);
        if (!first_iteration) {
            strcat(result, space);
        }

 
       
        if  (digits == 3) {
            handle_hundreds(result, numbers, digits);
        // if  (digits % 3 == 0) {

            // strcat(final, space);
        }
        if (digits < 3) {
            if (max_digits > 2 && digits == 2){
            and_space(result);
          }
           handle_tens(result, numbers, &digits);
        }
        if (digits < 7 && digits > 3){
            printf("We are in the thousands\n");
            if (digits == 6) {
                // hundred thousands
                handle_hundreds(result, numbers, digits);
                digits--;
                handle_tens(result, numbers, &digits);
                digits--;
            }
            else if (digits == 5) {
                // ten thousands
                handle_tens(result, numbers, &digits);
                digits--;
            }
            else {

            char *temp_digit = numbers_0_to_19[numbers[digits-1]];
            strcat(result, strcmp(temp_digit, "en") == 0 ? "et" : temp_digit);
            }
            strcat(result, space);
            strcat(result, "tusind");
            }
        else if (digits == 7){
            char *temp_digit = numbers_0_to_19[numbers[digits-1]];
            if ( strcmp(temp_digit, "nul") == 0) {
            strcat(result, temp_digit);
            strcat(result, space);
            }
            if (max_digits == 7 && strcmp(temp_digit, "en") == 0 ){
                strcat(result, "million");
            }
            else {
                strcat(result, "millioner");

            }
            }
        else if (digits == 10){
            char *temp_digit = numbers_0_to_19[numbers[digits-1]];
            strcat(result, temp_digit);
            strcat(result, space);
            strcat(result, strcmp(temp_digit, "en") == 0 ? "milliard" : "milliarder");
            }

        first_iteration = 0;
        digits--;
        temp_number = temp_number / 10;
        printf("AFTER temp number: %d. AFTER digits: %d\n", temp_number, digits);
     } while (digits > 0 && temp_number % 100 != 0);

    printf("Final: %s\n", result);
    result = "";
    return 0;
}

void handle_hundreds(char* result, int* numbers, int digits)
{
    printf("digits are dividable by 3 and are a sort of hundred\n");
    char *temp_single = numbers_0_to_19[numbers[digits-1]];
    // Skip if there's no hundred
    if (strcmp(temp_single, "nul") == 0) {
        digits--;
        return;
    }
    strcat(result, strcmp(temp_single, "en") == 0 ? "et" : temp_single);
    strcat(result, space);
    strcat(result, "hundrede");
}

void handle_tens(char* result, int* numbers, int* digits)
{
    printf("Digits in handle tens: %d\n", *digits);
    int is_last_ten =  (*digits == 2) ? 1 : 0;
    printf("is_last_ten: %d\n",is_last_ten);

    // We are dealing with numbers less than 100 - can be 88 thousand, but we only look at the "88" part here
    printf("digits are NOT dividable by 3\n");
    // Check if the number is less than 20, since they have special words
    printf("numbers[digits-1]: %d\n", numbers[*digits-1] );
    if (*digits == 1)
    {
        char *temp_single = numbers_0_to_19[numbers[*digits-1]];
        strcat(result, temp_single);
    }
    else if (numbers[*digits-1] < 2) {
        // combine the two *digits to get a number between 1 and 19 (there should be 0 check elsewhere)
        int less_than_twenty = numbers[*digits-1] * 10 + numbers[*digits-2];
        printf("Word at %d is %s\n", less_than_twenty, numbers_0_to_19[less_than_twenty]);
        strcat(result, numbers_0_to_19[less_than_twenty]);
    }
    else {
        char *temp_tens = tens[numbers[*digits-1]];
        char *temp_single = numbers_0_to_19[numbers[*digits-2]];
        strcat(result, temp_single);
        strcat(result, og);
        strcat(result, temp_tens);
        // printf("Final: %s\n", result);
    }
    if (is_last_ten)
    {
        printf("LAST ten\n");
        *digits = 0;
    }
    else {
        printf("NOT last ten\n");
    }
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