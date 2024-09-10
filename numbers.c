#include <stdio.h>
#include <string.h>
void print_numbers();
void print_arrays();
void handle_tens();
void handle_hundreds();
void and_space();

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

int numbers[255];
int org_number = 1022;
int digits = 0;
char final[255] = "";
int max_digits;


int main() {
    // Array of Danish spellings for numbers 0 to 19
    // int test_number = 5;
    // Print the Danish spellings to verify
    // print_arrays();
    // if (test_number < 20)
    // {
    //     printf("Test number %d = %s\n", test_number, numbers_0_to_19[test_number]);
    // }
    int temp_number = org_number;
    while (temp_number)
    {
        numbers[digits] = temp_number % 10;
        temp_number = temp_number / 10;
        // printf("Number %d is %d\n", digits, numbers[digits]);
        digits++;
    }

    max_digits = digits;
    printf("Index 01: %d\n", numbers[01]);
    printf("Index 02: %d\n", numbers[02]);
    temp_number = org_number;
    
    int first_iteration = 1;
    do
     {
        print_numbers();
        printf("Temp number: %d\n", temp_number);
        printf("Digits: %d\n", digits);
        if (!first_iteration) {
            strcat(final, space);
        }

 
       
        if  (digits == 3) {
            handle_hundreds();
        // if  (digits % 3 == 0) {

            // strcat(final, space);
        }
        if (digits < 3) {
            handle_tens();
        }
        if (digits < 7 && digits > 3){
            printf("We are in the thousands\n");
            if (digits == 6) {
                // hundred thousands
                handle_hundreds();
                digits--;
                handle_tens();
                digits--;
            }
            else if (digits == 5) {
                // ten thousands
                handle_tens();
                digits--;
            }
            else {

            char *temp_digit = numbers_0_to_19[numbers[digits-1]];
            strcat(final, strcmp(temp_digit, "en") == 0 ? "et" : temp_digit);
            }
            strcat(final, space);
            strcat(final, "tusind");
            }
        else if (digits == 7){
            char *temp_digit = numbers_0_to_19[numbers[digits-1]];
            if ( strcmp(temp_digit, "nul") == 0) {
            strcat(final, temp_digit);
            strcat(final, space);
            }
            if (max_digits == 7 && strcmp(temp_digit, "en") == 0 ){
                strcat(final, "million");
            }
            else {
                strcat(final, "millioner");

            }
            }
        else if (digits == 10){
            char *temp_digit = numbers_0_to_19[numbers[digits-1]];
            strcat(final, temp_digit);
            strcat(final, space);
            strcat(final, strcmp(temp_digit, "en") == 0 ? "milliard" : "milliarder");
            }

        first_iteration = 0;
        digits--;
        temp_number = temp_number / 10;
     } while (digits > 0 && temp_number % 10 != 0);

    printf("Final: %s\n", final);
    return 0;
}

void handle_hundreds()
{
    printf("digits are dividable by 3 and are a sort of hundred\n");
    char *temp_single = numbers_0_to_19[numbers[digits-1]];
    if (strcmp(temp_single, "nul") == 0) {
        digits--;
        return;
    }
    strcat(final, strcmp(temp_single, "en") == 0 ? "et" : temp_single);
    // strcat(final, og);
    strcat(final, space);
    strcat(final, "hundrede");
    // if (temp_number % 100 == 0) {
    //     printf("Final: %s\n", final);
    //     return 0;
    // }
}

void handle_tens()
{
    int last = digits == 2 ? 1 : 0;
    if (last && max_digits > 2){
        and_space();
    }
    // We are dealing with numbers less than 100 - can be 88 thousand, but we only look at the "88" part here
    printf("digits are NOT dividable by 3\n");
    // Check if the number is less than 20, since they have special words
    if (numbers[digits-1] < 2) {
        int less_than_twenty = numbers[digits-1] * 10 + numbers[digits-2];
        printf("Word at %d is %s\n", less_than_twenty, numbers_0_to_19[less_than_twenty]);
        strcat(final, numbers_0_to_19[less_than_twenty]);
    }
    else {
        char *temp_tens = tens[numbers[digits-1]];
        char *temp_single = numbers_0_to_19[numbers[digits-2]];
        strcat(final, temp_single);
        strcat(final, og);
        strcat(final, temp_tens);
        printf("Final: %s\n", final);
    }
    if (last)
    {
        digits = 0;
    }
}

void and_space(){
        strcat(final, og);
        strcat(final, space);
}

void print_numbers(){
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