#include <stdio.h>
#include "numbers.h"

int main()
{
    while (1){
        printf("Enter a number and get it back in danish words: ");
        int number;
        scanf(" %d", &number);
        char result_string[255] = "";
        number_to_danish(number, result_string);
    }
    return 0;
}