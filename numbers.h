#ifndef NUMBERS_H
#define NUMBERS_H

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

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

int number_to_danish(double number, char *buffer, struct NumberFormat format);
// int number_to_danish(int number, char *buffer, struct NumberFormat format);
void handle_tens(int number, char *buffer, int is_et);
void handle_formatting(char *buffer, struct NumberFormat format, int remaining_values, int remaining_values_over_99, char *num_type, char *one_type, int number, int remainder);
int values_remaining(int *val_arr, int size);
int str_match(char *str1, char *str2);

void print_options();
void run_tests();
int run_test(double number, struct NumberFormat format, char *expected);
int assert_equals(char *str1, char *str2);

int count_decimal_places(double value);
int is_effectively_int(double value);
void print_results(double org_val, char *result_string);

#endif
