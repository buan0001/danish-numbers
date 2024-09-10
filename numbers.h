#if !defined NUMBERS_H
#define NUMBERS_H

void print_numbers(int* numbers, int digits);
void print_arrays();
int handle_tens(char* result, int* numbers, int* digits);
// void handle_tens(char* result, int* numbers, int digits);
int handle_hundreds(char* result, int* numbers, int* digits);
void and_space(char* result);
int number_to_danish(int number, char* result);
int is_null(char *input);
int is_final(int* numbers, int digits);
// void int_to_danish_word(int number, char* result);

#endif // MACRO
