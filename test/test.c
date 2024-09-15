#include <stdio.h>
#include <math.h>
#include <string.h>

int main()
{

    double decimals = 123.456;
    int no_dec = (int)decimals;
    double just_decimals = decimals - no_dec;
    printf("int value: %d\n", no_dec);
    printf("int == decimals?: %d\n", decimals == no_dec);
    printf("just the decimals: %f\n", just_decimals);
    char *tal_til_10[] = {"nul", "en", "to", "tre", "fire", "fem", "seks", "syv", "otte", "ni", "ti"};
    int counter = 0;
    no_dec = (int)just_decimals;
    const double epsilon = 1e-6;
    // while (fabs(just_decimals - (int)just_decimals) > epsilon)
    char buffer[1024] = "komma";
    // int last_was_zero = 0;
    char temp_buffer[50];
    snprintf(buffer, sizeof(buffer), "%.15f", decimals); // Convert to string with up to 15 decimal places

    // Find the decimal point
    char *decimal_point = strchr(temp_buffer, '.');
    if (decimal_point != NULL)
    {
        decimal_point++; // Move past the decimal point
        while (*decimal_point != '\0')
        {
            if (*decimal_point >= '0' && *decimal_point <= '9')
            {
                int next_int = *decimal_point - '0'; // Convert char to int
                printf("Next int: %d\n", next_int);
                strcat(buffer, " ");
                strcat(buffer, tal_til_10[next_int]);
            }
            decimal_point++;
        }
    }
    // while (1)
    // {
    //     just_decimals *= 10;
    //     no_dec = (int)just_decimals;
    //     int next_int = (int)just_decimals % 10;
    //     if (next_int == 0)
    //     {
    //         if (last_was_zero)
    //         {
    //             // Keep going until two 0s in a row
    //             break;
    //         }
    //         last_was_zero = 1;
    //     }
    //     else
    //     {
    //         if (last_was_zero)
    //         {
    //             strcat(buffer, " nul");
    //         }
    //         strcat(buffer, " ");
    //         strcat(buffer, tal_til_10[next_int]);
    //         last_was_zero = 0;
    //     }
        // Just in case
    //     counter++;
    //     if (counter > 10)
    //     {
    //         break;
    //     }
    // }
    printf("decimals in string: %s\n", buffer);
    return 0;
}