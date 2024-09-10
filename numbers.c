#include <stdio.h>
#include <string.h>
void print_numbers();
void print_arrays();

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
int org_number = 801;
int digits = 0;



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

    int max_digits = digits;
    
    temp_number = org_number;
    char final[255] = "";
    while (digits)
     {
        print_numbers();
        printf("Temp number: %d\n", temp_number);
        printf("Digits: %d\n", digits);

        if (digits == 4){
            char *temp_digit = numbers_0_to_19[numbers[digits-1]];
            strcat(final, temp_digit);
            strcat(final, space);
            strcat(final, "tusind");
            }
        else if (digits == 7){
            char *temp_digit = numbers_0_to_19[numbers[digits-1]];
            if (temp_digit != "nul") {
            strcat(final, temp_digit);
            strcat(final, space);
            }
            if (max_digits == 7 && temp_digit == "en" ){
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
            strcat(final, temp_digit == "en" ? "milliard" : "milliarder");
            }
       
        if (digits % 3 == 0) {
            printf("digits are dividable by 3 and are a sort of hundred\n");
            char *temp_single = numbers_0_to_19[numbers[digits-1]];
            strcat(final, temp_single);
            // strcat(final, og);
            strcat(final, space);
            strcat(final, "hundrede");
            if (temp_number % 100 == 0) {
                printf("Final: %s\n", final);
                return 0;
            }
            strcat(final, space);
        }
        else {
            printf("digits are NOT dividable by 3\n");
            if (temp_number < 20) {
                printf("Number is %s\n", numbers_0_to_19[org_number]);
                break;
            }
            else if (temp_number < 100){
                // char final[255] = tens[numbers[1]];
                char *temp_tens = tens[numbers[digits-1]];
                char *temp_single = numbers_0_to_19[numbers[digits-2]];
                strcat(final, temp_single);
                strcat(final, og);
                strcat(final, temp_tens);
                printf("Final: %s\n", final);
                break;
            }
        }

        

        
        
        digits--;
        temp_number = temp_number / 10;
     }

    return 0;
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